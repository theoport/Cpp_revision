#ifndef BRAILLE_H
#define BRAILLE_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

bool member(const char letter, const char* list);
int encode_character(const char ch, char* braille);
void encode(const char* sentence, char* braille);
void print_braille(const char* sentence, std::ostream& out);

#endif











