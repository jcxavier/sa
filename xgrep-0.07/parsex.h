/********************************COPYRIGHT*************************************
  
    This file is part of the source for XGrep, a grep-like utility for 
    XML files. XGrep is distributed under the terms of the GNU General 
    Public License, a copy of which is included in the distribution.

    Copyright (C) 2003 Brendt Wohlberg  <software@wohlberg.net>

********************************COPYRIGHT*************************************/


#ifndef _PARSEX_H
#define _PARSEX_H

#include <stdlib.h>

#include <libxml/tree.h>

/* Parse the XML in the open file fp - the filename is only provided
   for error reporting/comment printing purposes, and may be null */
xmlDocPtr ParseStream(FILE* fp, char* filename);

#endif

