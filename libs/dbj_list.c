
#include "dbj_list.h"
#include <string.h>
#include <assert.h>

static unsigned dbj_list_max_size = 0xFFFF;

static const char dbj_list_sentinel_char = '\033'; // ESC aka ((char)127);

typedef char dbj_list_value_type;

static const dbj_list_value_type * dbj_list_sentinel_		
	= (dbj_list_value_type *)(&dbj_list_sentinel_char);

dbj_list_type dbj_list_new()
{
	dbj_list_type empty_ = 0;
	empty_ = (dbj_list_type)malloc(sizeof(empty_));
	assert(empty_);
	assert(*empty_);
	*empty_ = (char*)dbj_list_sentinel_;

	return empty_;
}

// return the pointer to the sentinel element
static dbj_list_type dbj_list_sentinel_ptr(dbj_list_type head_)
{
	dbj_list_type walker_ = head_;
	unsigned counter = 0;
	while (1 == 1) {
		if (*walker_ == dbj_list_sentinel_) break;
		walker_++;
		assert(counter++ < dbj_list_max_size);
	}
	return (walker_);
}

dbj_list_type dbj_list_append
(dbj_list_type head_, 
	const dbj_list_value_type * str_)
{
	assert(str_);
	dbj_list_type end_ = dbj_list_sentinel_ptr(head_);

	// check if we have the overflow
	size_t current_count_ = (end_ - head_);
	assert(current_count_ < dbj_list_max_size);

	// we expand +2
	// one for the new payload and one for the sentinel
	dbj_list_type tmp
		= (dbj_list_type)realloc(head_, (current_count_ + 2) * sizeof(tmp));

	assert(tmp);
	// point to resized block just after it is OK
	head_ = tmp;

	// attention: count and index are not the same
	head_[current_count_ + 0] = _strdup(str_);
	// removing the constness
	head_[current_count_ + 1] 
		= (dbj_list_value_type *)dbj_list_sentinel_;

	return head_;
}


void dbj_list_free(dbj_list_type head_)
{
	// not empty?
	if (dbj_list_sentinel_ != *head_) {
		// 
		dbj_list_type end_ = dbj_list_sentinel_ptr(head_);
		char * last_word_ = 0;
		// we skip over the sentinel
		// as the space for it was not allocated
		end_ -= 1;
		while (end_ != head_) {
			last_word_ = *end_;
			free(last_word_);
			last_word_ = *end_ = 0;
			end_ -= 1;
		};
	}
	if ( head_) {
		free(head_);
		head_ = 0  ;
	}
	// free(head_);
}

dbj_list_type dbj_list_reset(dbj_list_type head_)
{
	dbj_list_free(head_);
	return dbj_list_new();
}

