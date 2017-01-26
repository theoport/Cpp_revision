#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <fstream>
#include "piglatin.h"

using namespace std;

int findFirstVowel(const char* word){
	for (size_t i=0;i<strlen(word);i++){
		if (isVowel(word,i))
			return i;
	}
	return -1;
}		
bool isVowel(const char* str, int i){
	switch(str[i]){
		case 'a':
		case 'A':
		case 'e':
		case 'E':
		case 'I':
		case 'i':
		case 'o':
		case 'O':
		case 'u':
		case 'U':
			return true;
		case 'y':
		case 'Y':
			if (i==0||i==(strlen(str)-1))
				return false;
			return true;
		default:
			return false;
	}
}
void translateWord(const char* str_c,char* pigl_c){
	string str(str_c);
	string pigl;
	bool capital(false);
	for (size_t i=0;i<str.size();i++){
		if (isupper(str[i])){
			str[i]=tolower(str[i]);
			if(i==0)
				capital=true;
		}
	}
	int pos=findFirstVowel(str_c);
	if (isdigit(str[0]))
		pigl=str;
	else if (pos==0){
		pigl=str+"way";
		if (capital)
			pigl[0]=toupper(str[0]);
	}
	else if(pos==-1){
		pigl=str+"ay";
		if(capital)
			pigl[0]=toupper(str[0]);
	}
	else{ 
		string sub1,sub2;
		sub1=str.substr(0,pos);
		sub2=str.substr(pos);
		pigl=sub2+sub1+"ay";
		if (capital)
			pigl[0]=toupper(pigl[0]);
	}
	const char* copy=pigl.c_str();
	strncpy(pigl_c,copy,99);
}
/*
void translateStream(istream& in, ostream& out){
	char word[64];
	char pigl[100];
	char ch;
	while(!in.eof()){
		in.get(ch);
		if (isalnum(ch)){
			int i(0);
			word[i]=ch;
			while(isalnum(word[i])){
				i++;
				in.get(ch);
				word[i]=ch;
			}
			in.putback(ch);
			word[i]='\0';
			translateWord(word,pigl);
			out<<pigl;
			word[0]='\0';
		}
		else
			out.put(ch);
	}
}
*/
void translateStream(istream& in, ostream& out){
	if (in.eof())
		return;
	char word[64];
	char pigl[100];
	char ch;
	in.get(ch);
	if (isalnum(ch)){
		int i(0);
		word[i]=ch;
		while(isalnum(word[i])){
			i++;
			in.get(ch);
			word[i]=ch;
		}
		in.putback(ch);
		word[i]='\0';
		translateWord(word,pigl);
		out<<pigl;
		translateStream(in,out);
		return;
	}
	else{ 
		out.put(ch);
		translateStream(in,out);
		return;
	}	
}
