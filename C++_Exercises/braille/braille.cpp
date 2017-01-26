#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include "braille.h"

#define MAX_SIZE 512

using namespace std;

bool member(const char letter, const char* list){
	for (size_t i=0;i<strlen(list);i++){
		if (letter==list[i])
			return true;
	}
	return false;
}
int encode_character(const char ch, char* braille){
	int counter(0);
	char ch_copy=ch;
	braille[0]='\0';
	if (isdigit(ch_copy)){
		strncat(braille,"..0000",19);
		counter=6;
		if (ch_copy=='0')
			ch_copy+='j';
		else
			ch_copy+='a';
	}
	if (isupper(ch_copy)){
		strncat(braille,".....0",19);
		counter=6;
		ch_copy=tolower(ch_copy);
	}
	if (member(ch_copy,"abcdefghklmnopqruvxyz"))
		braille[counter++]='0';
	else 
		braille[counter++]='.';
	if (member(ch_copy,"bfghijlpqrstvw.,;!?()"))
		braille[counter++]='0';
	else
		braille[counter++]='.';
	if (member(ch_copy,"klmnopqrstuvxyz;-!?()"))
		braille[counter++]='0';
	else
		braille[counter++]='.';
	if (member(ch_copy,"cdfgijmnpqstwxy"))
		braille[counter++]='0';
	else
		braille[counter++]='.';
	if (member(ch_copy,"deghjnoqrtwyz.!()"))
		braille[counter++]='0';
	else
		braille[counter++]='.';
	if (member(ch_copy,"uvwxyz.-?()"))
		braille[counter++]='0';
	else
		braille[counter++]='.';
	braille[counter]='\0';
	return counter;
}	
void encode(const char* sentence, char* braille){
	if (*sentence=='\0')
		return;
	braille+=encode_character(*sentence,braille);
	sentence++;
	encode(sentence,braille);
	return;
}
void print_braille(const char* sentence, ostream& out){
	char braille[MAX_SIZE];
	encode(sentence,braille);
	for (size_t i=0;i<(strlen(braille)/6);i++){
		out<<braille[i*6];
		out<<braille[(i*6)+3];
		out<<' ';
	}
	out<<endl;
	for (size_t i=0;i<(strlen(braille)/6);i++){
		out<<braille[(i*6)+1];
		out<<braille[(i*6)+4];
		out<<' ';
	}
	out<<endl;
	for (size_t i=0;i<(strlen(braille)/6);i++){
		out<<braille[(i*6)+2];
		out<<braille[(i*6)+5];
		out<<' ';
	}
	out<<endl;
	for (size_t i=0;i<(strlen(sentence));i++){
		if (isupper(sentence[i])||isdigit(sentence[i]))
			out<<"   ";
		out<<sentence[i]<<"  ";
	}
	out<<endl;
}
			
	
