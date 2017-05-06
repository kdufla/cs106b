/*
 * file: LZ77_Types.h
 *
 * A file containing the types used by the LZ77
 * encoding program.
 */

#ifndef LZ_Types
#define LZ_Types

//for ascii
const int CHAR_LEN=8;

const int SEARCH_LEN=12;
const int SEARCH_SIZE=2^SEARCH_LEN;

const int AHAED_LEN=6;
const int AHEAD_SIZE=2^AHAED_LEN;

struct LZ_out {
	int position;
	int length;
	char next;
};


#endif