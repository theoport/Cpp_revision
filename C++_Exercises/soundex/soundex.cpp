#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <cstring>
#include "soundex.h"

using namespace std;

bool member(char a, const string& b){
	for (size_t i=0;i<b.size();i++){
		if (a==b[i])
			return true;
	}
	return false;
}	

void encode(const char* word, char* code){
	for (int i=0;i<4;i++)
		code[i]='0';
	code[4]='\0';
	code[0]=toupper(word[0]);
	int counter(1);
	for (int i=1;i<strlen(word)&&counter<4;i++){
		if (member(word[i],"bfpv")&&!member(word[i-1],"bfpv")){
			code[counter]='1';
			counter++;
		}
		else if (member(word[i],"cgjkqsxz")&&!member(word[i-1],"cgjkqsxz")){
			code[counter]='2';
			counter++;
		}
		else if (member(word[i],"dt")&&!member(word[i-1],"dt")){
			code[counter]='3';
			counter++;
		}
		else if (member(word[i],"l")&&!member(word[i-1],"l")){
			code[counter]='4';
			counter++;
		}
		else if (member(word[i],"mn")&&!member(word[i-1],"mn")){
			code[counter]='5';
			counter++;
		}
		else if (member(word[i],"r")&&!member(word[i-1],"r")){
			code[counter]='6';
			counter++;
		}
	}
}
/*bool compare(const char* a,const char* b)				
{
	c=a.str();
	d=b.str();
	if(c==d)
		return true;
	else
		return false
}
*/
int compare(const char* a, const char* b){
	if (*a=='\0')
		return 1;
	else if (*a!=*b)
		return 0;
	else if (*a==*b){
		a++;
		b++;
		return compare(a,b);
	}
}	
int count(const char* word, const char* str){
	char copy[512], soundex[5], soundex2[5];
	char* pch;
	int count(0);
	strncpy(copy, str, 511);
	pch=strtok(copy," ,.-");
	encode(word,soundex);
	while (pch!=NULL){
		encode(pch,soundex2);
		if (strcmp(soundex,soundex2)==0)
			count++;
		pch=strtok(NULL," ,.-");
	}
	return count;	
}
