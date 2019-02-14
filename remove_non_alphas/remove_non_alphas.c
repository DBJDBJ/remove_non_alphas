
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "dbj_sll.h"
/*
task: remove all non alpha chars from a given string
*/
/*
set vbuf signature

	_Success_(return == 0)
	_Check_return_opt_
	_ACRTIMP int __cdecl setvbuf(
		_Inout_                      FILE*  _Stream,
		_Inout_updates_opt_(_Size)   char*  _Buffer,
		_In_                         int    _Mode,
		_In_                         size_t _Size
		);

tmpfile signature

	_Check_return_ _CRT_INSECURE_DEPRECATE(tmpfile_s)

	_ACRTIMP FILE* __cdecl tmpfile(void);
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
			bool verbosity = true;
			int retval = load_words_to_sll(tmp_file_, &sll_, verbosity);

			if (fclose(tmp_file_)) {
				perror("tmp file closing failed");
			}

			printf("\nThe SLL current content");
			dbj_sll_foreach(sll_, dbj_sll_node_dump_visitor);
			printf("\n");

			// erase the sll + the head 
			dbj_sll_erase_with_head(sll_);

			return retval;
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
