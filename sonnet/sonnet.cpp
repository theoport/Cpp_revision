#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

/* START WRITING YOUR FUNCTION BODIES HERE */
int count_words(const char* str){
	int count(0);
	char* str_p;
	char copy[512];
	strncpy(copy,str,511);
	str_p=strtok(copy," ,.-;:!?");
	while (str_p!=NULL){
		count++;
		str_p=strtok(NULL," ,.-;:!?");
	}
	return count;
}
bool find_phonetic_ending(const char* word, char* phonetic_ending){
	char line[256];
	if (find_word(word,line)){
		make_phonetic_ending(line,phonetic_ending);
		return true;
	}
	else
		return false;
}	
bool make_phonetic_ending(char* str, char* ending){
	char temp[256];
	if (exists_vowel(str)){
		int count(last_phoneme_vowel(str));
		int count2(0);
		while (str[count]!='\0'){
			if (isspace(str[count]))
				count++;
			else 
				temp[count2++]=str[count++];
		}
		temp[count2]='\0';
		strcpy(ending,temp);
		return true;
	}
	else
		return false;
}
int last_phoneme_vowel(char* str){
	for (size_t i=0;i<strlen(str);i++){
		if (is_vowel(str[(strlen(str)-1)-i])){	
			while (!isspace(str[(strlen(str)-1)-i]))
				i++;
			return (strlen(str)-i);
		}
	}
	return -1;
}
bool is_vowel(char a){
	switch(a){
		case 'A':
		case 'a':
		case 'E':
		case 'e':
		case 'O':
		case 'o':
		case 'i':
		case 'I':
		case 'U':
		case 'u':
			return true;
		default:
			return false;
	}
}

bool exists_vowel(char* word){
	for (size_t i=0;i<strlen(word);i++){
		if (is_vowel(word[i]))
			return true;
	}
	return false;
}	

bool find_word(const char* word, char* line_copy){
	ifstream in("dictionary.txt");
	char line[256];
	char* temp;
	do{
		in.getline(line,256);
		strcpy(line_copy,line);
		temp=strtok(line," ");
	}while((strcmp (temp,word)!=0)&&!in.eof());	
	if (in.eof()){
		in.close();
		return false;
	}
	in.close();
	return true;
}	

bool find_rhyme_scheme(const char* filename, char* scheme){
	rhyming_letter(RESET);
	char line[256];
	char ending[256];
	char last[256];
	last[0]='\0';
	int i(0);
	ifstream input(filename);
	if (!input)
		return false;
	input.getline(line,256);
	while (!input.eof()){
		last_word(line,last);
		find_phonetic_ending(last,ending);
		scheme[i++]=rhyming_letter(ending);
		input.getline(line,256);
	}
	scheme[i]='\0';
	input.close();
}
	

		

void last_word(char* str, char* ending){
	char temp[256];
	temp[0]='\0';
	char* start;
	int end;
	int i(strlen(str)-1);
	while(!isalpha(str[i]))
		i--;
	end=i;
	while(!isspace(str[i]))
		i--;
	start=&str[i+1];
	strncpy(temp,start,(end-i));
	temp[end-i]='\0';
	for (size_t n=0;temp[n]!='\0';n++)
		temp[n]=toupper(temp[n]);
	strcpy(ending,temp);
}	

const char* identify_sonnet(const char* filename){
	char scheme[512];
	find_rhyme_scheme(filename,scheme);
	if (strcmp("ababcdcdefefgg",scheme)==0)
		return "Shakesperian";
	else if (strcmp("abbaabbacdcdcd",scheme)==0)
		return "Petrarchan";
	else if  (strcmp("ababbcbccdcdee",scheme)==0)
		return "Spenserian";
	else
		return "Unknown";
}

