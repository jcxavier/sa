/********************************COPYRIGHT*************************************
  
    This file is part of the source for XGrep, a grep-like utility for 
    XML files. XGrep is distributed under the terms of the GNU General 
    Public License, a copy of which is included in the distribution.

    Copyright (C) 2003 Brendt Wohlberg  <software@wohlberg.net>

********************************COPYRIGHT*************************************/


#ifndef _DEBUG_H
#define _DEBUG_H

#include <libxml/tree.h>

void printnode(FILE* fp, xmlNodePtr node);

void printtree(FILE* fp, xmlNodePtr node, int indent, int extflag);

#endif
