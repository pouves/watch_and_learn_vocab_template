Watch & Learn Vocab Template
==============================

Add your own vocabulary words to the Watch&Learn Pebble Watchapp!

→ Are you a programmer familiar with C? Wonderful…do whatever you want to do and change this app to add your own content!

→ Are you a non-programmer or unfamiliar with C? Cool! I wrote my first line of code about 6 months ago (thanks www.codecademy.com)! My buddy Alvin and I wrote this program together, and he helped me a lot to understand what it does and how to make it awesome. I’ll help you to do the same (and hopefully spark an interest in programming by introducing you to some neat resources)!

1) Download the .zip of this app (in the lower right hand corner of this page)

2) Go to https://cloudpebble.net/ide/ and sign in
(Never had the chance to check out CloudPebble? It’s amazing! Create an account so you can make this app and other Pebble apps…also check out these great tutorials if you want to learn more about developing apps for Pebble: http://ninedof.wordpress.com/pebble-sdk-tutorial/ )

3) Import the project: click “Import Project”, name your project, and upload the .zip
(Alternatively, you could upload the project directly from GitHub)

4) The main changes you want to make are to the file “content.h” so open that file by clicking its link on the lefthand side of the screen.

  Change this file by placing your vocab words and definitions in the code where prompted.

  If you have only a few words, you can insert them manually. Just substitute your words and definitions for the placeholder words and definitions under the prompts.
  

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

// POSTION OF DEFINITIONS IN LIST MUST MATCH POSTION OF WORDS!!

  "definition 1",
  
  "definition 2",
  
  "definition 3",
  
  "definition 4",
  
  "definition 5",
  
};


*If you have a lot of words, you can use Excel to easily make a longer list like this:*

Copy and paste the following into the given cells:

A1: 	  "

B1: 	",

C1: 	word 1

D1: 	=A1&C1&B1

E1: 	definition 1

F1: 	=A1&E1&B1


Your Excel file should now look like this:

1 |   "             | ",            | word 1    | "word 1", | definition 1 | "definition 1", |

Insert your word list and definition list into columns C and E. Drag the other columns down to fill the rest of the rows. 
*See what we’re doing here? Every word and definition must be surrounded by quotations and end with a comma. That’s the only way the program will recognize them.


Your Excel spreadsheet should now look like this:

1 |   "             | ",            | word 1    | "word 1", | definition 1 | "definition 1", |

2 |   "             | ",            | word 2    | "word 2", | definition 2 | "definition 2", |

3 |   "             | ",            | word 3    | "word 3", | definition 3 | "definition 3", |

:

:

x |   "             | ",            | word x     | "word x", | definition x  | "definition x", |


Now, copy and paste column C into:

// Enum for the cards

enum card_t {

// Insert the words (do not include spaces) here:

  C1 = 0,
  
  C2,
  
  C3,
  
  Etc…
  
};

*Note that you must go back and change the first word to say = 0 before the comma!!


Now, copy and paste column D into:

// Card Back - Line 1

char const * const aa_back_line_one[] = {

// Insert the words with quotations around them here (spaces are fine if necessary):  

  D1
  
  D2
  
  D3
  
  Etc…
  
};


Then, copy and paste column F into:

// Card Back - Line 1

char const * const aa_back_line_one[] = {

// Insert the definitions with quotations around them here:

// POSTION OF DEFINITIONS IN LIST MUST MATCH POSITION OF WORDS!!

  F1
  
  F2
  
  F3
  
  Etc…
  
};


5) Now that you have the content, change the number of cards at the top of the file to be the same number of vocab words you just inserted.

if 100 words…
define NUMBER_OF_FLASH_CARDS  (100)

if 5 words…
define NUMBER_OF_FLASH_CARDS  (5)

…You get the idea!

*We’re almost done…only a few more “housekeeping” tasks…

6) If you want to make and save different “decks” of flashcards, each one must have a different UUID. This is just a random number that is easy to generate and allows your Pebble to see your app as unique! Open the “Settings” option on the left.
Then go here:
http://www.guidgenerator.com/online-guid-generator.aspx
and click “Generate some GUIDs!”
copy the results (you only need one per app), and paste the string of numbers and letters in “Settings” “App UUID.”

7) Modify anything else you would like to in “Settings.” Maybe change your short or long app name to suit your app?

8) Go to “Compilation” and “Run build!”

*Success? Hooray!

*Fail? Hmm… There may be some bugs for different reasons. Most will probably have to do with the “content.h” file that you just modified. 

-Make sure that you have each word in the quotation marks and that you either typed those quotation marks directly into CloudPebble or you copied and pasted from this page (do not derive the quotation marks in a Word document). 

-Make sure that the number of cards in #define NUMBER_OF_FLASH_CARDS  () equals the number of words you have.

-Make sure every definition is at the same place in the definitions list as its corresponding word.

-Remember that the watch face has a limited amount of room. If a word or definition is too long, it may not fit in the given dimensions.

-Also, make sure that a comma follows each vocab word and definition AND that the words and definitions are surrounded by curly brackets { … };

9) Once you have compiled your app, you can download it to your computer, send it to your phone, and open in Pebble…or, you can turn on the developer setting on your phone (iOS Settings, Pebble, Developer Mode ON), then just Install & Run.

10) Try out your new customized flashcard app on your Pebble! If you have any problems or would like to know how to customize something else about it, send me an email, and I’ll try to get back to you or add the answer to another tutorial. Thanks for using Watch & Learn!

Liz

pebble.watchandlearn@gmail.com

*And remember, this app is to be used ONLY for studying, NOT for cheating!

