#include <iostream>
#include <string>
#include "substring.h"

using namespace std;

int substring_position(const string& sub, const string& string){
	if (sub.size()>string.size())
		return -1;
	if (sub.size()==0)
		return 0;
	for (size_t i=0;i<string.size();i++){
		int temp(i);
		if (is_prefix(sub,string,temp))
			return i;
	}
	return -1;
}

bool is_prefix(const string& sub, const string& string, int& count){
	if (sub[count]=='\0')
		return true;
	else if (sub[count]==string[count]){
		count++;
		return is_prefix(sub, string, count);
	}
	else 
		return false;
}
