#ifndef WORDS_H
#define WORDS_H

#include <iostream>
#include <cctype>
#include <cstring>

void reverse(const char* str1, char* str2);
int compare(const char* str1, const char* str2);
bool same_letter(char a,char b);
int palindrome(const char* sentence);
int anagram(const char* a, const char* b);
void sort_string(char* sorted, const char* sentence);
int smallest(int i, const char* sorted);
void swap(char& a, char& b);


#endif
