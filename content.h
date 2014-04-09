/**
 * Contains the definitions of the words.
 *
 * !!! IMPORTANT !!!
 * The order of the fields must match the order of the word
 * sequence!
 */

// Change this number to match the number of words you have!
#define NUMBER_OF_FLASH_CARDS  (5)

// Enum for the cards
enum card_t {
	// Insert words (do not include spaces) here:
  word1 = 0,
  word2,
  word3,
  word4,
  word5,
};

// Card Front
char const * const aa_front_line_one[] = {
	// Insert words with quotations around them here (spaces are fine if necessary):	
  "word 1",
  "word 2",
  "word 3",
  "word 4",
  "word 5",
};

// Card Back
char const * const aa_back_line_one[] = {
	// Insert definitions with quotations around them here:
	// ORDER OF DEFINITIONS IN LIST MUST MATCH ORDER OF WORDS!!
  "definition 1",
  "definition 2",
  "definition 3",
  "definition 4",
  "definition 5",
};
