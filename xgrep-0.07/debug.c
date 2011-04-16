/********************************COPYRIGHT*************************************
  
    This file is part of the source for XGrep, a grep-like utility for 
    XML files. XGrep is distributed under the terms of the GNU General 
    Public License, a copy of which is included in the distribution.

    Copyright (C) 2003 Brendt Wohlberg  <software@wohlberg.net>

********************************COPYRIGHT*************************************/


#include <string.h>

#include "debug.h"
#include "treex.h"

static const char* NodeTypes[] = {"InvalidType", "XML_ELEMENT_NODE", 
			     "XML_ATTRIBUTE_NODE", "XML_TEXT_NODE",
			     "XML_CDATA_SECTION_NODE","XML_ENTITY_REF_NODE",
			     "XML_ENTITY_NODE","XML_PI_NODE",
			     "XML_COMMENT_NODE","XML_DOCUMENT_NODE",
			     "XML_DOCUMENT_TYPE_NODE","XML_DOCUMENT_FRAG_NODE",
			     "XML_NOTATION_NODE","XML_HTML_DOCUMENT_NODE",
			     "XML_DTD_NODE","XML_ELEMENT_DECL",
			     "XML_ATTRIBUTE_DECL","XML_ENTITY_DECL",
			     "XML_NAMESPACE_DECL","XML_XINCLUDE_START",
			     "XML_XINCLUDE_END","XML_DOCB_DOCUMENT_NODE",
                             "InvalidType"};


void printnode(FILE* fp, xmlNodePtr node) {
  if (node) {
  fprintf(fp, "Node with name \"%s\" and type %s at %p\n", node->name, 
	  NodeTypes[node->type], (void*)node);
  fprintf(fp, "Document: %p  Parent: %s  Children: %s  Last: %s  "
	  "Prev: %s  Next: %s\n", (void*)node->doc,
	  (node->parent)?((char*)node->parent->name):"null",
	  (node->children)?((char*)node->children->name):"null",
	  (node->last)?((char*)node->last->name):"null",
	  (node->prev)?((char*)node->prev->name):"null",
	  (node->next)?((char*)node->next->name):"null");
  } else
    fprintf(fp, "Node pointer is null\n");
}



void printtree(FILE* fp, xmlNodePtr node, int indent, int extflag) {
  xmlNodePtr child = 0;
  xmlChar *indentchar = 0, *content = 0, *newline = 0;
  xmlAttrPtr xat = 0;

  indentchar = (xmlChar*)((indent>0)?" ":"");
  if (node) {

    content = xmlNodeGetContent(node);
    if (!content || xmlCountElementChildren(node) > 0)
      content = (xmlChar*)"";
    while ((newline = (xmlChar*)strchr((char *)content, '\n'))) {
      *newline = '#';
    }
    if (node->type == XML_ELEMENT_NODE)
      fprintf(fp, "%*s%s\t%s\n", 2*indent, indentchar, node->name, content);
    else {
      if (extflag)
	fprintf(fp, "%*s[%s]\t%s\n", 2*indent, indentchar, 
		node->name, content);
    }
    if (extflag) {
      child = node->children;
      if (xmlCountChildren(node) == 1 && child->type == XML_TEXT_NODE)
	return;
    }
    else
      child = xmlGetFirstChildElement(node);

    if (extflag) {
      xat = node->properties;
      while (xat) {
	fprintf(fp, "%*s(%s)\t%s\n", 2*(indent+1), indentchar, xat->name, 
		xmlGetProp(node, xat->name));
	xat = xat->next;
      }
    }

    while (child) {
      printtree(fp, child, indent+1, extflag);
      if (extflag)
	child = child->next;
      else
	child = xmlGetNextElementNode(child);
    }
  }
}
