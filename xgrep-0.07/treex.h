/********************************COPYRIGHT*************************************
  
    This file is part of the source for XGrep, a grep-like utility for 
    XML files. XGrep is distributed under the terms of the GNU General 
    Public License, a copy of which is included in the distribution.

    Copyright (C) 2003 Brendt Wohlberg  <software@wohlberg.net>

********************************COPYRIGHT*************************************/


#ifndef _TREEX_H
#define _TREEX_H

#include <libxml/tree.h>


/* Safe node access */

#define xmlGetPrevNode(node) ((node)?(node->prev):NULL)
#define xmlGetNextNode(node) ((node)?(node->next):NULL)
#define xmlGetFirstChild(node) ((node)?(node->children):NULL)
#define xmlGetNodeDoc(node) ((node)?(node->doc):NULL)
#define xmlGetNodeName(node) ((node)?(node->name):NULL)
#define xmlGetNodeType(node) ((node)?(node->type):0)


/* Node access by name */

int xmlHasChildWithName(xmlNodePtr parent, const xmlChar* name);
xmlNodePtr xmlNameGetChild(xmlNodePtr parent, const xmlChar* name);
xmlNodePtr xmlNameGetPrevNode(xmlNodePtr node, const xmlChar* name);
xmlNodePtr xmlNameGetNextNode(xmlNodePtr node, const xmlChar* name);



/* Access specific to element nodes */

#define xmlIsElementNode(node) (node && node->type == XML_ELEMENT_NODE)

xmlNodePtr xmlGetPrevElementNode(xmlNodePtr node);
xmlNodePtr xmlGetNextElementNode(xmlNodePtr node);
xmlNodePtr xmlGetFirstChildElement(xmlNodePtr parent);
xmlNodePtr xmlGetLastChildElement(xmlNodePtr parent);


/* Element node access by name */

int xmlHasElementChildWithName(xmlNodePtr parent, const xmlChar* name);
xmlNodePtr xmlNameGetChildElement(xmlNodePtr parent, const xmlChar* name);
xmlNodePtr xmlNameGetPrevElementNode(xmlNodePtr node, const xmlChar* name);
xmlNodePtr xmlNameGetNextElementNode(xmlNodePtr node, const xmlChar* name);


/* Count children */

int xmlCountChildren(xmlNodePtr parent);
int xmlCountElementChildren(xmlNodePtr parent);


/* DTD access */

const xmlChar* NodeDocPublicID(xmlNodePtr node);
const xmlChar* NodeDocSystemID(xmlNodePtr node);
const xmlChar* NodeDocRootElement(xmlNodePtr node);

#endif
