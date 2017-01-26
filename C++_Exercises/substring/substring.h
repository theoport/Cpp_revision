#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <iostream>
#include <string>

int substring_position(const std::string& sub, const std::string& string);
bool is_prefix(const std::string& sub, const std::string& string, int& count);
#endif
