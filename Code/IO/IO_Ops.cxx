#include "assert.h"
#include <cctype>

#include "IO_Ops.hxx"



std::string IO::read_line_after(std::ifstream & File,
                                const char* Word,
                                bool Case_Sensitive) {
  /* Read in the file line by line until one is found that contains the
  word (or the end of file is reached)

  The optional Case_Sensitive argument specifies if this function ignores
  case in Word/Buffer. (see Index_After_Word description).  */
  assert(File.is_open() == true);


  unsigned Buffer_Size = 265;
  char Line_Buffer[Buffer_Size];
  int index;
  while(true) {
    /* Check if we're at the end of the file. If so then the requested
    word could not be found in the File. Abort. */
    if(File.eof() == true) {
      std::printf("Bad Read: Thrown by IO::read_line_after.\n"
                  "You tried to find the word \"%s\" in a file. However, we couldn't find\n"
                  "it (it may have been located in part of the file that we already read)\n",
                  Word);
      abort();
    } // if(File.eof() == true) {

    // If we're not at the end of the file, then there is more to read... so
    // read away!
    File.getline(Line_Buffer, Buffer_Size);

    // Check if this line is a comment. If so, then skip it.
    if(Line_Buffer[0] == '#') { continue; }

    // Make sure that Line_Buffer is a null-terminated string.
    Line_Buffer[Buffer_Size-1] = '\0';

    // Seach for the word in this line.
    index = IO::String_Ops::Index_After_Word(Line_Buffer, Word, Case_Sensitive);

    /* If Word is not in the Line then index will be equal to -1. If not, then
    index specifies the index (in the Line) of first character of Word. */
    if(index != -1) { break; }
  } // while(true) {

  /* If we are here then Line_Buffer stores a line of the File that contains
  the Word. Moreover, index stores the index of the first character in
  Line_Buffer after the end of the word. We can now construct the string (to
  return) from this */
  std::string Trimmed_Line;
  for(unsigned k = index; Line_Buffer[k] != '\0'; k++) { Trimmed_Line += Line_Buffer[k]; }
  return Trimmed_Line;
} // std::string IO::read_line_after(std::ifstream & File, const char* Word, bool Case_Sensitive) {



bool IO::String_Ops::Contains(const char* Buffer,
                              const char* Word,
                              bool Case_Sensitive,
                              unsigned Start_At) {
  /* Function description:
  This function determines if Word is contained in Buffer.

  The optional Case_Sensitive argument specifies if this function ignores
  case in Word/Buffer. Thus, Contains("tHe WoRd","wOrD", false) would
  return true while Contains("tHe WoRd","wOrD", false) would return false.

  The optional Start_At argument can be used to only search through part of the
  string. If, for example, Start_At = 5, then this function will only search for
  matches that begin at index 5 (or later) of Buffer. */

  if(IO::String_Ops::Index_After_Word(Buffer, Word, Case_Sensitive, Start_At) == -1) { return false; }
  else { return true; }
} // bool IO::String_Ops::Contains(const char* Buffer, const char* Word, bool Case_Sensitive, unsigned Start_At) {



int IO::String_Ops::Index_After_Word(const char* Buffer, const char* Word, bool Case_Sensitive, unsigned Start_At) {
  /* Function description:
  This function attempts to find Word in Buffer. If Word is in Buffer, then this
  function will return the index of the first character in Buffer past the
  end of the Word. If Word is not contained in Buffer, then this function returns
  -1.

  The optional Case_Sensitive argument specifies if this function ignores
  case in Word/Buffer. Thus, Index_After_Word("tHe WoRd","wOrD", false) would
  return true while Index_After_Word("tHe WoRd","wOrD", false) would return false.

  The optional Start_At argument tells the function to only search through
  the string after the Start_At'th character. If, for example, Start_At = 5
  then this function will only search for Word in Buffer after the 5th
  character of Buffer. */

  /* Assumptions:
  This function assumes that both Buffer and Word are NULL TERMINATED strings.
  That is, I assume that both end with the \0 character. */

  /* First, check if Buffer has fewer than Start_At characters (which happens
  if there is a \0 in a index whose value is less than Start_At). If not, return
  -1 (Word can't be in Buffer) */
  for(unsigned i = 0; i < Start_At; i++) {
    if(Buffer[i] == '\0') { return -1; }
  } // for(unsigned i = 0; i < Start_At; i++) {


  // Loop through the characters of Buffer.
  unsigned i = Start_At;
  unsigned j;
  while(Buffer[i] != '\0') {
    // At each one, see if Word starts at that character.
    j = 0;
    while(true) {
      // Check if i+jth letter of Buffer mathces jth letter of Word. If not,
      // then break.
      if(Case_Sensitive == true && Buffer[i+j] != Word[j]) { break; }
      else if(Case_Sensitive == false && tolower(Buffer[i+j]) != tolower(Word[j])) { break; }

      // Increment j
      j++;

      /* If we've reached the end of "Word" then we've found a match!
      i+j is the index of the first character beyond the end of Word in Buffer. */
      if(Word[j] == '\0') { return i+j; }

      /* If we haven't reached the end of Word but we have reached the end of
      Buffer, then Buffer does not contain Word. Return -1 */
      if(Buffer[i+j] == '\0') { return -1; }
    } // while(true) {
    i++;
  } // while(Buffer[i] != '\0') {

  /* If we get here then we cycled through Buffer without finding a match.
  Thus, buffer does not contain Word. Return -1 */
  return -1;
} // int IO::String_Ops::Index_After_Word(const char* Buffer, const char* Word, bool Case_Sensitive, unsigned Start_At) {
