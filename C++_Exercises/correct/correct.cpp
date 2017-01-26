#include <iostream>
#include <cstring>
#include "correct.h"

using namespace std;

void ascii_to_binary(char ch, char *binary){
	for (int n=128;n;n>>=1)
		*binary++=(ch&n)?'1':'0';
	*binary='\0';
}
char binary_to_ascii(const char *binary){
	int ch=0;
	for (int n=0,slide=128;n<8;n++,slide>>=1){
		if (binary[n]=='1')
			ch=ch|slide;
	}	
	return ch;
}
void text_to_binary(const char* str, char* binary){
	if (*str=='\0'){
		*binary='\0';
		return;
	}
	ascii_to_binary(*str,binary);
	str++;
	binary+=8;
	text_to_binary(str, binary);
	return;
}

void binary_to_text(const char* str,char* text){
	if (*str=='\0'){
		*text='\0';
		return;
	}
	*text=binary_to_ascii(str);
	binary_to_text(str+8, text+1);
	return;
}
void add_error_correction(const char* str, char* correct){
	if (*str=='\0'){
		*correct='\0';
		return;
	}
	correct[2]=str[0];
	correct[4]=str[1];
	correct[5]=str[2];
	correct[6]=str[3];
	correct[0]=((str[0]+str[1]+str[3])%2)?'1':'0';
	correct[1]=((str[0]+str[2]+str[3])%2)?'1':'0';
	correct[3]=((str[1]+str[2]+str[3])%2)?'1':'0';
	add_error_correction(str+4,correct+7);
	return;
}	
	
int decode(const char* rec, char* decoded){
	if (*rec=='\0'){
		*decoded='\0';
		return 0;
	}
	char copy[8];
	strncpy(copy,rec,7);
	copy[8]='\0';
	int p1,p2,p3;
	p1=((rec[3]+rec[4]+rec[5]+rec[6])%2);
	p2=((rec[1]+rec[2]+rec[5]+rec[6])%2);
	p3=((rec[0]+rec[2]+rec[4]+rec[6])%2);
	int b=(4*p1)+(2*p2)+p3;
	if (b)
		flip(copy[b-1]);
	decoded[0]=copy[2];
	decoded[1]=copy[4];
	decoded[2]=copy[5];
	decoded[3]=copy[6];
	return (b)?(1+decode(rec+7,decoded+4)):decode(rec+7,decoded+4);
}
void flip(char& a){
	if (a=='1')
		a='0';
	else
		a='1';
}
		
				
