#ifndef CORRECT_H
#define CORRECT_H 

#include <iostream>

char binary_to_ascii(const char *binary);
void ascii_to_binary(char ch, char *binary);
void text_to_binary(const char* str, char* binary);
void binary_to_text(const char* str, char* text);
void add_error_correction(const char* str, char* correct);
void flip(char& a);
int decode(const char* rec, char* decoded);

#endif
