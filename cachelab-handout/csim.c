#define _GNU_SOURCE
#define debug

#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cachelab.h"

#define FILENAMELEN 40
#define TRACESIZE 30

typedef struct{
	int is_valid;
	int tag;
	int access_timestamp;
}line;

static int hits = 0;
static int misses = 0;
static int evictions = 0;

int power(int x, int y)
{
	int temp = 0;
	if(y == 0)
		return 1;
	temp = power(x, y/2);
	if(y%2 == 0)
		return temp*temp;
	else
		return x*temp*temp;
}

int main(int argc, char** argv)
{
	extern char *optarg;
	extern int optind;
	int retval;
	int num_sets = 0, num_lines = 0, num_blocks = 0;
	char trace_file[FILENAMELEN];
	line* cache = NULL;
	FILE* fd = NULL;
	char* trace_line = NULL;
	size_t line_size, len = 0;

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
#ifdef debug
	printf("s=%d\tE=%d\tb=%d\ttrace_file=%s\n",num_sets,num_lines,num_blocks,\
		trace_file);
#endif

	cache = calloc( power(2, num_sets)*num_lines, sizeof(line));
#ifdef debug
	printf("Cache allocated of size %d sets and %d lines. \
			Block Size = %d Cache Pointer = %p \n",\
			power(2, num_sets), num_lines, num_blocks, cache);
#endif

	fd = fopen(trace_file, "r");
	if(fd == NULL)
		exit(EXIT_FAILURE);

	while((line_size = getline(&trace_line, &len, fd)) != -1)
	{
		printf("Line: %s\n",trace_line);
	}

	printSummary(hits, misses, evictions);
	return 0;
}
