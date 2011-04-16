/********************************COPYRIGHT*************************************
  
    This file is part of the source for XGrep, a grep-like utility for 
    XML files. XGrep is distributed under the terms of the GNU General 
    Public License, a copy of which is included in the distribution.

    Copyright (C) 2003,2008 Brendt Wohlberg  <software@wohlberg.net>

********************************COPYRIGHT*************************************/


#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

#include <libxml/tree.h>
#include <libxml/catalog.h>
#include <libxml/xpath.h>

#include "treex.h"
#include "parsex.h"
#include "find.h"

int main (int argc, char* argv[]) {
  xmlDocPtr doc = 0;
  FILE* fp = 0;
  char *infile = 0, *xpathtxt = 0;
  char **srchstrlist = 0;
  int slistsz = 32, nsrchstr = 0, k;
  int retval = 0;
  const char* catalog = 0;
  RegexType rt = RegexExtended;
  const char* usagestr = 
    "usage: xgrep [-h] [-v] [-p] [-x xpath] [-s regex] ... [-s regex] "
    "[-c catalog] [infile] [infile] ...\n"
    "       -x xpath to desired elements\n"
    "       -s element search string\n"
    "       -h display usage information\n"
    "       -v display version information\n"
    "       -p use perl regular expressions (when supported)\n"
    "       -c path to catalog file\n";
  

  /* Allocate memory for list of search strings */
  if (!(srchstrlist = malloc(sizeof(char*)*slistsz))) {
    fprintf(stderr,"xgrep: error allocating search string list\n");
    exit(1);
  }

  /* Parse command line */
  opterr = 0;
  while ((k = getopt (argc, argv, "x:s:hvpc:")) != -1)
    switch (k) {
    case 'c': catalog = optarg;
      break;
    case 'x': xpathtxt = optarg;
      break;
    case 's': 
      if (nsrchstr == slistsz) {
	char** rp = 0;
	slistsz *= 2;
	if (!(rp = realloc(srchstrlist, sizeof(char*)*slistsz))) {
	  free(srchstrlist);
	  fprintf(stderr,"xgrep: error reallocating search string list\n");
	  exit(1);
	}
	srchstrlist = rp;
      }
      srchstrlist[nsrchstr++] = optarg;
      break;
    case 'h': fprintf(stderr, "%s", usagestr);
      exit(0);
#if USE_PCRE
    case 'v': printf("xgrep %s (libxml2,pcre)\n", XGREPVERSION);
#else
    case 'v': printf("xgrep %s (libxml2)\n", XGREPVERSION);
#endif
      exit(0);
    case 'p':
#if USE_PCRE
      rt = RegexPCRE;
      break;
#else
      fprintf(stderr, "xgrep: perl regular expressions not supported - "
	      "not linked to pcre library\n");
      exit(1);
#endif
    case '?': fprintf(stderr, "xgrep: unknown command line flag\n");
      fprintf(stderr, "%s", usagestr);
      exit(1);
    default:
      exit(1);
    }

  /* Ensure some form of element selection specified */
  if (!xpathtxt && !nsrchstr) {
    fprintf(stderr, "xgrep: no xpath or search string specified\n");
    exit(1);
  }

  /* Load catalog for external entities */
  if (catalog) {
    if (xmlLoadCatalog(catalog)) {
      fprintf(stderr, "xgrep: error loading catalog file %s\n",
	      catalog);
      exit(1);
  }
    xmlDoValidityCheckingDefaultValue = 1;
    xmlLoadExtDtdDefaultValue |= XML_DETECT_IDS;
  }

  /* Work through input files */
  do {
    if (optind < argc)
      infile = argv[optind++];

    /* Set file pointer to current input file, or stdin if no input 
       files specified */
    if (infile) {
      if (!(fp = fopen(infile, "r"))) {
	fprintf(stderr, "xgrep: error opening input %s\n", infile);
	exit(1);
      } 
    } else
      fp = stdin;

    /* Parse current input file */
    if (!(doc = ParseStream(fp, infile))) {
      if (infile)
	fclose(fp);
      fprintf(stderr, "xgrep: error parsing file %s\n", infile);
      exit(1);
    }
    
    /* Close the file pointer if was not set to stdin */
    if (infile)
      fclose(fp);

    /* Print matching nodes if an XPath string was specified */
    if (xpathtxt)
      if (!PrintXPathNodes(doc, (xmlChar*)xpathtxt)) {
	fprintf(stderr, "xgrep: error evaluating xpath expression \"%s\"\n",
		xpathtxt);
	retval = 2;
      }

    /* Print matching nodes for each regex string specified */
    for (k = 0; k < nsrchstr; k++) {
      if (!PrintSearchStrNodes(doc, srchstrlist[k], rt)) {
	fprintf(stderr, "xgrep: error compiling regex in search string"
		        " \"%s\"\n", srchstrlist[k]);
	retval = 2;
      }
    }
   
    /* Free current document */
    xmlFreeDoc(doc);

  } while (optind < argc);

  /* Clean up */
  free(srchstrlist);
  xmlCatalogCleanup();
  xmlCleanupParser();

  return retval;
}
