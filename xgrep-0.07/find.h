/********************************COPYRIGHT*************************************
  
    This file is part of the source for XGrep, a grep-like utility for 
    XML files. XGrep is distributed under the terms of the GNU General 
    Public License, a copy of which is included in the distribution.

    Copyright (C) 2003,2008 Brendt Wohlberg  <software@wohlberg.net>

********************************COPYRIGHT*************************************/


#ifndef _FIND_H
#define _FIND_H

#ifndef USE_PCRE
#define USE_PCRE 0
#endif

#include <stdlib.h>
#include <regex.h>

#if USE_PCRE
#include <pcre.h>
#endif


#include <libxml/tree.h>
#include <libxml/xpath.h> /* Required for xmlNodeSet definition */

typedef enum { RegexExtended, RegexPCRE } RegexType; 

/* An element name and a regex on its content */
typedef struct {
  char* element;
  char* regex;
  RegexType rt;
  union {
    regex_t creg;
#if USE_PCRE
    pcre*  pcreg;
#endif
  } cre;
} ElementRegexPair;

typedef ElementRegexPair* ElementRegexPairPtr;

/* A subtree root element name and a list of element/regex pairs */
typedef struct {
  char* rootelement;
  ElementRegexPairPtr erpairs;
  int npairs;
} SubtreeRegex;

typedef SubtreeRegex* SubtreeRegexPtr;


/* Create an element/regex pair with the specified element and regex
   at the position pointed to by erpair (which must allready have been
   allocated */
int CreateElementRegexPair(ElementRegexPairPtr erpair, const char* element, 
			   const char* regex, RegexType rt);
/* Free the memory allocated by CreateElementRegexPair, but do not
   free the memory pointed to by erpair itself */
void DestroyElementRegexPair(ElementRegexPairPtr erpair);


/* Allocate memory for a new SubtreeRegex object and construct it
   based on the content of str */
SubtreeRegexPtr NewSubtreeRegex(const char* str, RegexType rt);

/* Free the SubtreeRegex object */
void FreeSubtreeRegex(SubtreeRegexPtr stre);

/* Print a representation of the parsed search string */
void PrintSubtreeRegex(FILE* fp, SubtreeRegexPtr stre);


/* Return a node set of nodes in doc matched by the search string stre */
xmlNodeSetPtr SubtreeRegexNodeSet(xmlDocPtr doc, SubtreeRegexPtr stre);

/* Determine whether a node matches the search string stre */
int SubtreeRegexMatch(xmlNodePtr node, SubtreeRegexPtr stre);

/* Append node to nodeset */
int AppendToNodeSet(xmlNodeSetPtr nodeset, xmlNodePtr node);


/* Print subtrees from doc selected by the XPath xpathtxt */
int PrintXPathNodes(xmlDocPtr doc, xmlChar* xpathtxt);

/* Print subtrees from doc selected by the search string srchstr */
int PrintSearchStrNodes(xmlDocPtr doc, char* srchstr, RegexType rt);

/* Print nodes in nodeset */
void PrintNodeSet(xmlNodeSetPtr nodeset, char* note);

#endif

