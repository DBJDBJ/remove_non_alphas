#pragma once

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
#include "../libs/dbj_sll.h"

#ifdef __cplucplus
extern "C" {
#endif

	// every program should have limits established 
	// on the data it is processing
	static const size_t MAX_WORD_LEN = BUFSIZ;
	// one letter word
	static const size_t MIN_WORD_LEN = 1;
	static const size_t MAX_INPUT_LEN = 0xFFFF;
	// one letter input
	static const size_t MIN_INPUT_LEN = 1;
	
	int remove_non_alphas(const char * to_parse, dbj_sll_node **);


#ifdef __cplucplus
} // extern "C" 
#endif

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