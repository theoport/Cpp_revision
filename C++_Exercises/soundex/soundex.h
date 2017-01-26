#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <cstring>
#include "soundex.h"

using namespace std;

bool member(char a, const string& b);
void encode(const char* word, char* code);
int compare(const char* a, const char* b);
int count(const char* word, const char* a);

#endif
