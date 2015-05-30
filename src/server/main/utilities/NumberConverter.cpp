#include "NumberConverter.h"
#include <string>
#include <sstream>

bool NumberConverter::isNumber(const std::string& str){
	for (unsigned int i = 0; i < str.size(); ++i){
		char curChar = str.at(i);
		if ((curChar < '0' || curChar > '9') && curChar != '.'){
			return false;
		}
	}
	return true;
}

int NumberConverter::getNumber(const std::string& str){
	std::stringstream ss(str);
	int result;
	ss >> result;
	return result;
}

std::string NumberConverter::getString(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}
