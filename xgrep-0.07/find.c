/********************************COPYRIGHT*************************************
  
    This file is part of the source for XGrep, a grep-like utility for 
    XML files. XGrep is distributed under the terms of the GNU General 
    Public License, a copy of which is included in the distribution.

    Copyright (C) 2003,2008 Brendt Wohlberg  <software@wohlberg.net>

********************************COPYRIGHT*************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <assert.h>

#include "find.h"
#include "treex.h"
#include "debug.h"


/* Determine whether a string is only whitespace */
static int StrIsSpace(const char* str);

/* Apply appropriate regex match function */
static int RegexMatch(ElementRegexPairPtr erpair, const char* str);

/* Return copy of str from beginning until token is reached, and set
   *toknxt to point to the first char of str after the token */
static char* NewCopyStrToToken(const char* str, char token, 
			       const char** toknxt);

/* Copy str, split it into null-terminated sections matched by regex,
   set *nmatch to the number of regex matches, and *unmatched to the
   remaining unmatched part of str */
static char* NewCopyRegexSplitStr(const char* str, const char* regex, 
				  int* nmatch, const char** unmatched);

/* Recursive part of SubtreeRegexNodeSet */
static void SubtreeRegexNodeSetRecursive(xmlNodePtr node, SubtreeRegexPtr stre,
					 xmlNodeSetPtr nodeset);

/* Determine whether all matchflags are non-zero */
static int MatchFlagsAllMatch(char* matchflags, int size);


/* Recursive part of SubtreeRegexMatch */
static int SubtreeRegexMatchRecursive(xmlNodePtr node, SubtreeRegexPtr stre, 
				      char* matchflags);


int StrIsSpace(const char* str) {
  if (str) {
    while (*str != '\0') {
      if (!isspace(*str))
	return 0;
      str++;
    }
    return 1;
  } else
    return 0;
}


int RegexMatch(ElementRegexPairPtr erpair, const char* str) {
  if (erpair) {
    if (erpair->rt == RegexPCRE) {
#if USE_PCRE
      return pcre_exec(erpair->cre.pcreg, 0, str, strlen(str), 0, 0, 0, 0);
#else
      return 0;
#endif
    } else {
      regmatch_t pmatch[1];
      
      return regexec(&(erpair->cre.creg), str, 1, pmatch, 0);
    }
  }
  return 0;
}


char* NewCopyStrToToken(const char* str, char token, const char** toknxt) {
  char *cp = 0, *newstr = 0;

  cp = strchr(str, token);
  if (cp) {
    *toknxt = cp+1;
    if ((newstr = malloc(cp-str+1))) {
      strncpy(newstr, str, cp-str);
      newstr[cp-str] = '\0';
    }
  }
  return newstr;
}


char* NewCopyRegexSplitStr(const char* str, const char* regex, 
			   int* nmatch, const char** unmatched) {
  regex_t preg;
  regmatch_t pmatch[1];
  char *cp = 0, *newstr = 0;

  if (regcomp(&preg, regex, REG_EXTENDED) == 0) {
    if ((newstr = malloc(strlen(str)+2))) {
      strcpy(newstr, str);
      newstr[strlen(newstr)+1] = '\0';
      newstr[strlen(newstr)] = ' ';
      *nmatch = 0;
      cp = newstr;

      while (regexec(&preg, cp, 1, pmatch, 0) == 0) {
	cp = cp+pmatch->rm_eo-1;
	*cp = '\0';
	cp++;
	(*nmatch)++;
      }
      *unmatched = cp;
    }
    regfree(&preg);
  }
  return newstr;
}


int CreateElementRegexPair(ElementRegexPairPtr erpair, const char* element, 
			   const char* regex, RegexType rt){
  if (erpair) {
    erpair->element = 0;
    erpair->regex = 0;
    erpair->element = malloc(strlen(element)+strlen(regex)+2);
    if (!erpair->element)
      return 0;
    erpair->regex = erpair->element+strlen(element)+1;
    strcpy(erpair->element, element);
    strcpy(erpair->regex, regex);
  
    if (rt == RegexPCRE) {
#if USE_PCRE
      const char *err = 0;
      int erroff = 0;

      erpair->rt = RegexPCRE;

      if (!(erpair->cre.pcreg = pcre_compile(erpair->regex, 0, 
					     &err, &erroff, 0))) {
	free(erpair->element);
	return 0;
      }
      return 1;
#else
      free(erpair->element);
      return 0;
#endif
    } else {
      erpair->rt = RegexExtended;
      if (regcomp(&(erpair->cre.creg), erpair->regex, REG_EXTENDED) != 0) {
	free(erpair->element);
	return 0;
      }
      return 1;
    }
  }
  return 0;
}


void DestroyElementRegexPair(ElementRegexPairPtr erpair) {
  if (erpair) {
    free(erpair->element);
    if (erpair->rt == RegexPCRE) {
#if USE_PCRE
      pcre_free(erpair->cre.pcreg);
#endif
     } else
      regfree(&(erpair->cre.creg));
  }
}


SubtreeRegexPtr NewSubtreeRegex(const char* str, RegexType rt) {
  SubtreeRegexPtr stre = 0;
  const char *unmatched = 0, *regex = 
    "^[^/ ]+/([^/\\]|([\\]+[^/\\])|(([\\]{2})*[\\][/]))+([\\]{2})*/[, ]?";
  char *tmpstr = 0, *ep = 0, *rp = 0;
  int k = 0, nmatch = 0, incr = 0;

  if (!(stre = malloc(sizeof(SubtreeRegex))))
    return 0;

  stre->rootelement = NewCopyStrToToken(str, ':', &str);
  if (!stre->rootelement) {
    free(stre);
    return 0;
  }

  if (!(tmpstr = NewCopyRegexSplitStr(str, regex, &nmatch, &unmatched))) {
    free(stre);
    return 0;
  }

  if (!StrIsSpace(unmatched)) {
    free(stre);
    return 0;
  }

  stre->npairs = nmatch;
  if (!(stre->erpairs = malloc(sizeof(ElementRegexPair)*nmatch))) {
    free(stre);
    free(tmpstr);
    return 0;
  }

  ep = tmpstr;
  for (k = 0; k < nmatch; k++) {

    rp = strchr(ep, '/');
    assert( rp != 0 );
    *rp = '\0';
    rp++;

    if (rp[strlen(rp)-1] == ',') {
      incr = 2;
      rp[strlen(rp)-1] = '\0';
    } else {
      incr = 2;
    }
    rp[strlen(rp)-1] = '\0';

    if (!(CreateElementRegexPair(&(stre->erpairs[k]), ep, rp, rt))) {
      free(tmpstr);
      free(stre->erpairs);
      free(stre);
      return 0;
    }
    ep = rp + strlen(rp) + incr;
  }

  free(tmpstr);
  
  return stre;
}


void FreeSubtreeRegex(SubtreeRegexPtr stre) {
  int k;

  if (stre) {
    free(stre->rootelement);
    for (k = 0; k < stre->npairs; k++)
      DestroyElementRegexPair(&(stre->erpairs[k]));
    free(stre->erpairs);
    free(stre);
  }
}


void PrintSubtreeRegex(FILE* fp, SubtreeRegexPtr stre) {
 int k;

 if (stre) {
   fprintf(fp, "Subtree root element: %s\nElement/Regex pairs:\n", 
	   stre->rootelement);
   for (k = 0; k < stre->npairs; k++)
     fprintf(fp,"%-20s   %s\n", stre->erpairs[k].element,
	     stre->erpairs[k].regex);
 }
}


xmlNodeSetPtr SubtreeRegexNodeSet(xmlDocPtr doc, SubtreeRegexPtr stre) {
  xmlNodeSetPtr nodeset = 0;
  
  if (doc) {
    if ((nodeset = malloc(sizeof(xmlNodeSet)))) {
      nodeset->nodeNr = 0;
      nodeset->nodeMax = 0;
      nodeset->nodeTab = 0;
      SubtreeRegexNodeSetRecursive(xmlDocGetRootElement(doc), stre, nodeset);  
    }
  }
  
  return nodeset;
}


void SubtreeRegexNodeSetRecursive(xmlNodePtr node, SubtreeRegexPtr stre,
				 xmlNodeSetPtr nodeset) {
  xmlNodePtr cur = 0;

  if (node && stre && nodeset) {
    cur = xmlGetFirstChildElement(node);
    while (cur) {
      if (SubtreeRegexMatch(cur, stre))
	AppendToNodeSet(nodeset, cur);
      else
	SubtreeRegexNodeSetRecursive(cur, stre, nodeset);

      cur = xmlGetNextElementNode(cur);
    }
  }
}


int SubtreeRegexMatch(xmlNodePtr node, SubtreeRegexPtr stre) {
  int ret = 0;

  if (node && stre && !xmlStrcmp((xmlChar*)stre->rootelement, node->name)) {
    char* matchflags = 0;

    if (!(matchflags = calloc(stre->npairs, sizeof(char))))
      return 0;

    SubtreeRegexMatchRecursive(node, stre, matchflags);
    ret = MatchFlagsAllMatch(matchflags, stre->npairs);

    free(matchflags);
  } 

  return ret;
}


int SubtreeRegexMatchRecursive(xmlNodePtr node, SubtreeRegexPtr stre, 
			       char* matchflags) {
  xmlNodePtr cur = 0;
  xmlChar *c;
  int k;

#if defined(XGDEBUG) && XGDEBUG > 2
  printf("===== SubtreeRegexMatchRecursive =====\n");
  printf("node %s\n", node->name);
  {
    int k;
    for (k = 0; k < stre->npairs; k++)
      printf("matchflag %d is %d\n", k, matchflags[k]);
  }
  printf("======================================\n");
#endif

  if (node && stre && matchflags) {
    cur = xmlGetFirstChildElement(node);

    while (cur) {

#if defined(XGDEBUG) && XGDEBUG > 3
    printf("current node: %s\n", cur->name);
#endif 

      for (k = 0; k < stre->npairs; k++) {
	c = xmlNodeGetContent(cur);
	if (!matchflags[k] &&
	    !xmlStrcmp((xmlChar*)stre->erpairs[k].element, cur->name) &&
	    RegexMatch(&(stre->erpairs[k]), (char*)c) == 0) {

#if defined(XGDEBUG) && XGDEBUG > 3
	  printf("Match succeeded for element %s with content \"%s\"\n",
		 cur->name, (char*)xmlNodeGetContent(cur));
#endif

	  matchflags[k] = 1;
	}
	xmlFree(c);
      }

      if (SubtreeRegexMatchRecursive(cur, stre, matchflags))
	return 1;
      
      cur = xmlGetNextElementNode(cur);
    }
    return MatchFlagsAllMatch(matchflags, stre->npairs);
  }
  return 0;
}


int MatchFlagsAllMatch(char* matchflags, int size) {
  int k;

  for (k = 0; k < size; k++)
    if (matchflags[k] == 0)
      return 0;
  return 1;
}


int AppendToNodeSet(xmlNodeSetPtr nodeset, xmlNodePtr node) {
 
#if defined(XGDEBUG) && XGDEBUG > 2
  printf("===== AppendToNodeSet =====\n");
  printf("===========================\n");
#endif

  if (!nodeset || !node)
    return 0;

  if (nodeset->nodeNr >= nodeset->nodeMax) {
    xmlNodePtr* newtab = 0;
    int newmax = 0;
    
    newmax = (nodeset->nodeMax > 0)?(nodeset->nodeMax*2):32;
    if ((newtab = realloc(nodeset->nodeTab, sizeof(xmlNodePtr)*newmax))) {
      nodeset->nodeMax = newmax;
      nodeset->nodeTab = newtab;
    } else
      return 0;
  }
  
  nodeset->nodeTab[nodeset->nodeNr++] = node;

#if defined(XGDEBUG) && XGDEBUG > 3
  printf("Appended node to nodelist:\n");
  printnode(stdout, node);
  printtree(stdout, node, 0 , 1);
#endif
  
  return 1;
}


int PrintXPathNodes(xmlDocPtr doc, xmlChar* xpathtxt) {
  xmlXPathContextPtr xpcntxt = 0;
  xmlXPathObjectPtr xpobj = 0;
  xmlNodeSetPtr nodeset = 0;
  int ret = 1;
  char note[512];

  if (doc && xpathtxt) {
    if ((xpcntxt = xmlXPathNewContext(doc))) {
      if ((xpobj = xmlXPathEvalExpression(xpathtxt, xpcntxt))) {
	nodeset = xpobj->nodesetval;
	sprintf(note, "(XPath: %.500s)", xpathtxt);
	PrintNodeSet(nodeset, note);
	xmlXPathFreeObject(xpobj);
      } else
	ret = 0;
      xmlXPathFreeContext(xpcntxt);
    } else
      ret = 0;
  }

  return ret;
}


int PrintSearchStrNodes(xmlDocPtr doc, char* srchstr, RegexType rt) {
  xmlNodeSetPtr nodeset = 0;
  SubtreeRegexPtr stre = 0;
  char note[512];

  if (!(stre = NewSubtreeRegex(srchstr, rt)))
    return 0;
  nodeset = SubtreeRegexNodeSet(doc, stre);
  sprintf(note, "(Search: %.500s)", srchstr);
  PrintNodeSet(nodeset, note);
  xmlXPathFreeNodeSet(nodeset);
  FreeSubtreeRegex(stre);

  return 1;
}


void PrintNodeSet(xmlNodeSetPtr nodeset, char* note) {
  xmlNodePtr node = 0;
  xmlBufferPtr buffer = 0;
  xmlChar* c;
  int k;

  if (nodeset) {
    
    if (!note)
      note = "";
    
    if (xmlXPathNodeSetGetLength(nodeset) > 0)
      printf("<!--         Start of node set %s                 -->\n", note);
    
    for (k = 0;k < xmlXPathNodeSetGetLength(nodeset); k++) {
      node = xmlXPathNodeSetItem(nodeset, k);
      printf("<!--         Node %3d in node set               -->\n", k);
      
      if (node->prev && xmlNodeIsText(node->prev)) {
	c = xmlNodeGetContent(node->prev);
	printf("%s", c);
	xmlFree(c);
      }
      
      buffer = xmlBufferCreate();
      xmlNodeDump(buffer, node->doc, node, 0, 1);
      xmlBufferDump(stdout, buffer);
      printf("\n\n");
      xmlBufferFree(buffer);
    }
    
    if (xmlXPathNodeSetGetLength(nodeset) > 0)
      printf("<!--         End of node set                    -->\n");
  }
}
