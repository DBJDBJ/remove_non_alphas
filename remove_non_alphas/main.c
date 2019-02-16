
#include "remove_non_alphas.h"
#include "../libs/dbj_list.h"

const char * TEST_INPUT = "0abra123ka456dabra789and345also678some123456jabra";


int main(const int argc, const char * argv[])
{
#ifdef TEST_DBJ_DYNAMIC
	dbj_list_test();
#endif

	(void)(&argc); // remove the no use warning

	const char * to_parse =
		(argc < 2 ? TEST_INPUT : argv[1]);

	dbj_sll_node *  sll_ = 0 ;

	if (EXIT_SUCCESS == remove_non_alphas(to_parse, & sll_ )) 
	{
		assert(sll_);
		printf("\nThe Output\n");
		dbj_sll_foreach(sll_, dbj_sll_node_dump_visitor);
		printf("\n");
		// erase the sll + the head 
		dbj_sll_erase_with_head(sll_);
	}

}
