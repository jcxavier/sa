/********************************COPYRIGHT*************************************
  
    This file is part of the source for XGrep, a grep-like utility for 
    XML files. XGrep is distributed under the terms of the GNU General 
    Public License, a copy of which is included in the distribution.

    Copyright (C) 2003 Brendt Wohlberg  <software@wohlberg.net>

********************************COPYRIGHT*************************************/


#include <libxml/parser.h>

#include "treex.h"

int xmlHasChildWithName(xmlNodePtr parent, const xmlChar* name) {
  xmlNodePtr child = 0;

  child = xmlGetFirstChild(parent);
  while (child) {
    if (!xmlStrcmp(name, child->name))
      return 1; 
    child = child->next;
  }
  return 0;
}


xmlNodePtr xmlNameGetChild(xmlNodePtr parent, const xmlChar* name) {
  xmlNodePtr child = 0;

  child = xmlGetFirstChild(parent);
  while (child) {
    if (!xmlStrcmp(name, child->name))
      return child;
    child = child->next;
  }
  return NULL;
}


xmlNodePtr xmlNameGetPrevNode(xmlNodePtr node, const xmlChar* name) {
  node = xmlGetPrevNode(node);
  while (node) {
    if (!xmlStrcmp(name, node->name))
      return node;
    node = node->prev;
  }
  return NULL;
}


xmlNodePtr xmlNameGetNextNode(xmlNodePtr node, const xmlChar* name) {
  node = xmlGetNextNode(node);
  while (node) {
    if (!xmlStrcmp(name, node->name))
      return node;
    node = node->next;
  }
  return NULL;
}


xmlNodePtr xmlGetPrevElementNode(xmlNodePtr node) {
  node = xmlGetPrevNode(node);
  while (node && node->type != XML_ELEMENT_NODE)
    node = node->prev;
  return node;
}

 
xmlNodePtr xmlGetNextElementNode(xmlNodePtr node) {
  node = xmlGetNextNode(node);
  while (node && node->type != XML_ELEMENT_NODE)
    node = node->next;
  return node;
}


xmlNodePtr xmlGetFirstChildElement(xmlNodePtr node) {
  node = xmlGetFirstChild(node);
  while (node && node->type != XML_ELEMENT_NODE)
    node = node->next;
  return node;
}


xmlNodePtr xmlGetLastChildElement(xmlNodePtr node) {
  node = xmlGetLastChild(node);
  while (node && node->type != XML_ELEMENT_NODE)
    node = node->prev;
  return node;
}


int xmlHasElementChildWithName(xmlNodePtr parent, const xmlChar* name) {
  xmlNodePtr child = 0;

#if defined(XGDEBUG) && XGDEBUG > 1
  printf("===== xmlHasElementChildWithName =====\n");
  printf("<-------------- parent -------------->\n");
  printtree(stdout, parent, 0, 1);
  printf("<----------------------------------->\n");
  printf("name: %s\n", name);
  printf("=====================================\n");
#endif

  child = xmlGetFirstChildElement(parent);
  while (child) {
    if (!xmlStrcmp(name, child->name))
      return 1; 
    child = xmlGetNextElementNode(child);
  }
  return 0;
}


xmlNodePtr xmlNameGetChildElement(xmlNodePtr parent, const xmlChar* name) {
  xmlNodePtr child = 0;

  child = xmlGetFirstChildElement(parent);
  while (child) {
    if (!xmlStrcmp(name, child->name))
      return child;
    child = xmlGetNextElementNode(child);
  }
  return NULL;
}


xmlNodePtr xmlNameGetPrevElementNode(xmlNodePtr node, const xmlChar* name) {
  node = xmlGetPrevElementNode(node);
  while (node) {
    if (!xmlStrcmp(name, node->name))
      return node;
    node = xmlGetPrevElementNode(node);
  }
  return NULL;
}



xmlNodePtr xmlNameGetNextElementNode(xmlNodePtr node, const xmlChar* name) {
  node = xmlGetNextElementNode(node);
  while (node) {
    if (!xmlStrcmp(name, node->name))
      return node;
    node = xmlGetNextElementNode(node);
  }
  return NULL;
}




int xmlCountChildren(xmlNodePtr parent) {
  xmlNodePtr child = 0;
  int N = 0;

  child = xmlGetFirstChild(parent);
  while (child) {
    N++;
    child = child->next;
  }
  return N;
}


int xmlCountElementChildren(xmlNodePtr parent) {
  xmlNodePtr child = 0;
  int N = 0;

  child = xmlGetFirstChildElement(parent);
  while (child) {
      N++;
      child = xmlGetNextElementNode(child);
  }
  return N;
}


const xmlChar* NodeDocPublicID(xmlNodePtr node) {
  xmlDocPtr doc = 0;
  xmlDtdPtr dtd = 0;

  doc = xmlGetNodeDoc(node);
  if (doc && (dtd = doc->intSubset))
    return dtd->ExternalID;
  else
    return 0;
}


const xmlChar* NodeDocSystemID(xmlNodePtr node) {
  xmlDocPtr doc = 0;
  xmlDtdPtr dtd = 0;

  doc = xmlGetNodeDoc(node);
  if (doc && (dtd = doc->intSubset))
    return dtd->SystemID;
  else
    return 0;
}


const xmlChar* NodeDocRootElement(xmlNodePtr node) {
  xmlDocPtr doc = 0;
  xmlNodePtr root = 0;

  doc = xmlGetNodeDoc(node);
  if (doc && (root = xmlDocGetRootElement(doc)))
    return root->name;
  else
    return 0;
}
