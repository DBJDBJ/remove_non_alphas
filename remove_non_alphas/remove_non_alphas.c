
/*
(c) Copyright 2018-2019 by dbj@dbj.org

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
http ://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "dbj_sll.h"
/*
task: remove all non alpha chars from a given string, coming from a command line

design: 

parse and save to a temporary file
load the list of words from a file to a singly linked list

note: 

 This is C learning excersize. 
 Onlookers are wellcome to suggest how to clean it and/or simplify it. 
 There is always a scope for that. But do not forget the keyword number one:

  Feasibility

*/

const char * TEST_INPUT = "0abra123ka456dabra789and345also678some123456jabra";

int process_and_save(FILE *, const char *);
int show_file(FILE *);
int create_tmp_file(FILE ** );
int load_words_to_sll(FILE * fp, dbj_sll_node **, bool);

int main(const int argc, const char * argv[])
{
	(void)(&argc); (void)argv; // remove the no use warning

	const char * to_parse =
		( argc < 2 ? TEST_INPUT : argv[1] );

	FILE * tmp_file_ = NULL;
		
	if (EXIT_SUCCESS == create_tmp_file(&tmp_file_))
	{
		if (EXIT_SUCCESS == process_and_save(tmp_file_, to_parse))
		{
			dbj_sll_node * sll_;
			bool verbosity = false;
			if (EXIT_SUCCESS != load_words_to_sll(tmp_file_, &sll_, verbosity))
			{
				perror("load_words_to_sll() failed");
				return EXIT_FAILURE;
			}

			if (fclose(tmp_file_)) {
				perror("tmp file closing failed");
				return EXIT_FAILURE;
			}

			printf("\nThe SLL content");
			dbj_sll_foreach(sll_, dbj_sll_node_dump_visitor);
			printf("\n");

			// erase the sll + the head 
			dbj_sll_erase_with_head(sll_);

			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

int process_and_save(FILE * fp, const char * input)
{
	// int input_len = strlen(to_parse) ;
	char * walker = (char *)(input);
	while (*walker++)
	{
		if (!*walker) break;
		if (isalpha(*walker)) {
			fprintf(fp, "%c", *walker);
			// I am alpha but next one is not
			// so write an "word end" aka "\n", next
			// one line is one word
			if (!isalpha(*(walker + 1)))
				fprintf(fp, "\n");
		}
	}

	return EXIT_SUCCESS; // aka 0
}

int show_file(FILE* fp)
{
	// important, since we are 
	// already at EOF
	rewind(fp); 
	int c; // note: int, not char!
	while ((c = fgetc(fp)) != EOF) { 
		putchar(c);
	}

	if (ferror(fp))
		puts("\n\nI/O error when reading");
	else if (feof(fp))
		puts("\n\nEnd of file reached successfully");

	return EXIT_SUCCESS; // aka 0
}

int create_tmp_file ( FILE ** fp_fp ) 
{
	*fp_fp = tmpfile();

	if ( NULL == *fp_fp) {
		perror("TMP File opening failed");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS; // aka 0
}

int load_words_to_sll(FILE * fp, dbj_sll_node ** sll_head_, bool verbose )
{
	dbj_sll_node * sll_ = dbj_sll_make_head();
	// do not forget to rewind
	// to the top
	rewind(fp); 
	const size_t LINE_MAX = 0xFF;
	char line[LINE_MAX] = {0};
	size_t word_size = 0;

	while (fgets(line, LINE_MAX, fp)) 
	{
		// fgets takes '\n' as the part of the string
		// so let's replace it with '\0' first
		word_size = strlen(line);
		line[word_size-1] = '\0';
		// print second but only if in a verbose mode
		if (verbose) printf("'%s'", line);

		// internal line is copied 
		// when erasing the whole sll
		//it will be freed to
		dbj_sll_append(sll_, line);
	}

	// the result
	*sll_head_ = sll_;

	// the error handling
	return (EXIT_SUCCESS);
}
