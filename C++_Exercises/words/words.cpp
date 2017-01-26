#include <iostream>
#include <cctype>
#include <cstring>
#include "words.h"
using namespace std;

void reverse(const char* str1, char* str2){
	for (size_t i=0;i<strlen(str1);i++)
		str2[i]=str1[strlen(str1)-(i+1)];	
	str2[strlen(str1)]='\0';
}

int compare(const char* str1, const char* str2){
	while(!isalnum(*str1)&&*str1!='\0')
		str1++;
	while(!isalnum(*str2)&&*str2!='\0')
		str2++;
	if (*str1=='\0'&&*str2=='\0')
		return 1;
	if (same_letter(*str1,*str2)){
		str1++;
		str2++;
		return compare(str1,str2);
	}
	else 
		return 0;	
}
bool same_letter(char a,char b){
	if (isupper(a))
		a=tolower(a);
	if (isupper(b))
		b=tolower(b);
	return a==b?true:false;
}
int palindrome(const char* sentence){
	char copy[500];
	reverse(sentence,copy);
	if (compare(sentence,copy))
		return 1;
	else
		return 0;
}

int anagram(const char* a, const char* b){
	char a_copy[500];
	char b_copy[500];
	sort_string(a_copy,a);
	sort_string(b_copy,b);
	if (compare(a_copy,b_copy))
		return 1;
	else
		return 0;
}

void 	sort_string(char* sorted, const char* sentence){
	int counter(0);
	for (size_t i=0;i<strlen(sentence);i++){
		if (isalnum(sentence[i])){
			sorted[counter]=sentence[i];
			if (isupper(sorted[counter]))
				sorted[counter]=tolower(sorted[counter]);
			counter++;
		}
	}
	sorted[counter]='\0';
	for (size_t i=0;i<strlen(sorted);i++){
		swap(sorted[i],sorted[smallest(i,sorted)]);
	}
}
int smallest(int i, const char* sorted){
	int count= i;
	char temp=sorted[i];
	for (i+1;i<strlen(sorted);i++){
		if (sorted[i]<temp){
			temp=sorted[i];
			count=i;
		}
	}
	return temp;
}
void swap(char& a, char& b){
	char temp;
	temp=a;
	a=b;
	b=temp;
}
		
	
