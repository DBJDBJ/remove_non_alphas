
#include "remove_non_alphas.h"
#include "../libs/dbj_list.h"

const char * TEST_INPUT = "0abra123ka456dabra789and345also678some123456jabra";

static dbj_sll_node * dbj_sll_head = 0;

static int dbj_sll_append_callback(const char * line)
{
	assert(line);
	assert(dbj_sll_head);
	(void)dbj_sll_append(dbj_sll_head, line);
	// must return this in order to proceed
	return EXIT_SUCCESS;
}

int main(const int argc, const char * argv[])
{
#ifdef TEST_DBJ_DYNAMIC
	dbj_list_test();
#endif

	(void)(&argc); // remove the no use warning

	const char * to_parse =
		(argc < 2 ? TEST_INPUT : argv[1]);

	dbj_sll_head = dbj_sll_make_head();

	if (EXIT_SUCCESS == remove_non_alphas(to_parse, dbj_sll_append_callback))
	{
		assert(dbj_sll_head);
		printf("\n\n\nThe Output\n");
		dbj_sll_foreach(dbj_sll_head, dbj_sll_node_dump_visitor);
		printf("\n");
		// erase the sll + the head 
		dbj_sll_erase_with_head(dbj_sll_head);
	}
}

