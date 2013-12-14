#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cachelab.h"

#define FILENAMELEN 20

static int hits = 0;
static int misses = 0;
static int evictions = 0;


int main(int argc, char** argv)
{
	extern char *optarg;
	extern int optind;
	int retval;
	int num_sets = 0, num_lines = 0, num_blocks = 0;
	char trace_file[FILENAMELEN];

	while((retval = getopt(argc, argv, "s:E:b:t:"))!= -1){
		switch(retval){
			case 's':
				num_sets = atoi(optarg);
				break;
			case 'E':
				num_lines = atoi(optarg);
				break;
			case 'b':
				num_blocks = atoi(optarg);
				break;
			case 't':
				strcpy(trace_file, optarg);
				break;
		}
	}
	printf("s=%d\tE=%d\tb=%d\ttrace_file=%s\n",num_sets,num_lines,num_blocks,\
		trace_file);


	printSummary(hits, misses, evictions);
	return 0;
}
