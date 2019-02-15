#pragma once
#include <string.h>
#include <stdlib.h>
#include <assert.h>
/*
(c) 2019 by dbj@dbj.prg -- Licence: GPLv3

manage the 'char **' structure
it is said to be "self contained" because of the NULL sentinel
i.e. it does not need a structure above to keep it's 
size for example

  empty:

  char  ** --------->[ char * ] ----------> 0

  populated:

  char  ** --------->[ char * ] ----------> "ABRA"
					 [ char * ] ----------> "KA"
					 [ char * ] ----------> "DABRA"
					 [ char * ] ----------> 0
*/
#ifdef __cplucplus
extern "C" {
#endif

	unsigned dbj_dynamic_sentinel_max_size = 0xFFFF;
	char * dbj_dynamic_sentinel_ = (char *)(0);
	typedef char **dbj_dynamic;

	inline dbj_dynamic dbj_dynamic_new() {
		char ** empty_ = 0;
		static char * p = 0;
		empty_ = (char **)malloc(sizeof(empty_));
		*empty_ = 0;
		return empty_;
	}

	// return the pointer to the back+1 element
	// aka "end"
	inline char ** dbj_dynamic_end(dbj_dynamic head_) {
		char ** walker_ = head_;
		unsigned counter = 0;
		while (1 == 1) {
			if (*walker_ == dbj_dynamic_sentinel_) break;
			walker_++;
			assert(counter++ < dbj_dynamic_sentinel_max_size);
		}
		return (walker_);
	}

	inline dbj_dynamic dbj_dynamic_append(dbj_dynamic head_, const char * str_)
	{
		assert(str_);
		// empty?
		if (dbj_dynamic_sentinel_ == *head_) {
			*head_ = _strdup(str_);
			*(1 + head_) = dbj_dynamic_sentinel_;
		}
		else {
			// not empty
			char ** end_ = dbj_dynamic_end(head_);
			//
			size_t current_count_ = (end_ - head_);
			assert(current_count_ < dbj_dynamic_sentinel_max_size);

			// expand
			char ** tmp
				= (char**)realloc(head_, (current_count_ + 1) * sizeof(tmp));
			assert(tmp);
			head_ = tmp;

			// pay attention: count and index are not the same
			head_[current_count_ + 0] = _strdup(str_);
			head_[current_count_ + 1] = 0;
		}
		return head_;
	}

	/*
	erase and return the head
	(which has to be freed manualy)
	*/
	inline dbj_dynamic dbj_dynamic_reset(dbj_dynamic head_)
	{
		// empty?
		if (dbj_dynamic_sentinel_ == *head_) {
			return head_;
		}
		// not empty
		char ** end_ = dbj_dynamic_end(head_);
		char * was_end_ = 0;
		end_ -= 1;
		while (end_ != head_) {
			was_end_ = *end_;
			free(was_end_);
			end_ -= 1;
		};
		free(*head_);
		*head_ = 0;
		return head_;
	}

#ifdef TEST_DBJ_DYNAMIC

	static void dbj_dynamic_test()
	{
		char **  head_ = dbj_dynamic_new();

		head_ = dbj_dynamic_append(head_, "ABRA");
		head_ = dbj_dynamic_append(head_, "KA");
		head_ = dbj_dynamic_append(head_, "DABRA");
		head_ = dbj_dynamic_reset(head_);
		// reset is not free head_ is valid here 
		free(head_);
		// or proceed using it
	}

#endif // ! TEST_DBJ_DYNAMIC

#ifdef __cplucplus
}
#endif