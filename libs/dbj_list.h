#pragma once
/*
(c) 2019 by dbj@dbj.prg -- Licence: GPLv3

manage the 'char **' structure
it is said to be "self contained" because of the sentinel
at the end, it does not need a structure above it,
to keep it's size for example
instead we compute the size

  empty:

  char  ** --------->[ char * ] ----------> SENTINEL

  populated:

  char  ** --------->[ char * ] ----------> "ABRA"
					 [ char * ] ----------> "KA"
					 [ char * ] ----------> "DABRA"
					 [ char * ] ----------> SENTINEL
*/

#include <stdlib.h>

#ifdef __cplucplus
extern "C" {
#endif
	typedef char ** dbj_list_type;

	/* 
	returns the empty list
	*/
	 dbj_list_type dbj_list_new();

	 dbj_list_type dbj_list_append(dbj_list_type , const char * );

	/*
	reset the list and return the head
	head must be freed manually when no longer needed
	*/
	 dbj_list_type dbj_list_reset(dbj_list_type );

	 void dbj_list_free(dbj_list_type);



#define TEST_DBJ_DYNAMIC
#ifdef TEST_DBJ_DYNAMIC

	inline void dbj_list_test()
	{
		dbj_list_type head_ = dbj_list_new();

		head_ = dbj_list_append(head_, "ABRA");
		head_ = dbj_list_append(head_, "KA");
		head_ = dbj_list_append(head_, "DABRA");
		head_ = dbj_list_reset(head_);
		// "reset" is not "free" head_ is valid here 
		// but now it is not
		dbj_list_free(head_);
	}

#endif // ! TEST_DBJ_DYNAMIC

#ifdef __cplucplus
}
#endif