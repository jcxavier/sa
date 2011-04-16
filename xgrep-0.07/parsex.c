/********************************COPYRIGHT*************************************
  
    This file is part of the source for XGrep, a grep-like utility for 
    XML files. XGrep is distributed under the terms of the GNU General 
    Public License, a copy of which is included in the distribution.

    Copyright (C) 2003 Brendt Wohlberg  <software@wohlberg.net>

********************************COPYRIGHT*************************************/


#include <stdlib.h>

#include <libxml/parser.h>

#include "parsex.h"

xmlDocPtr ParseStream(FILE* fp, char* filename) {
  static char buffer[2048];
  const int bufsize = 2048;
  int readsize, errflag = 0;
  xmlDocPtr doc = 0;
  xmlParserCtxtPtr ctxt = 0;
      
  if (fp && (readsize = fread(buffer, 1, 4, fp)) > 0) { 
    ctxt = xmlCreatePushParserCtxt(0, 0, buffer, readsize, filename);
    while ((readsize = fread(buffer, 1, bufsize, fp)) > 0)
      if(xmlParseChunk(ctxt, buffer, readsize, 0) != 0)
	errflag = 1;
    if(xmlParseChunk(ctxt, buffer, 0, 1) != 0)
      errflag = 1;
    if (errflag)
      xmlFreeDoc(ctxt->myDoc);
    else
      doc = ctxt->myDoc;
    xmlFreeParserCtxt(ctxt);
  }
  return doc;
}
