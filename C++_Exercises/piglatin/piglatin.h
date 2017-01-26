#ifndef PIGLATIN_H
#define PIGLATIN_H

#include <iostream>
#include <cctype>
#include <cstring> 
#include <string>
#include <fstream>

void translateWord(const char* str_c,char* pigl_c);
int findFirstVowel(const char* word);
bool isVowel(const char* str, int i);
void translateStream(std::istream& in, std::ostream& out);

#endif

