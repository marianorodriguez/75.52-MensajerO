#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>

using namespace std;

class Date {
public:
	Date();
	virtual ~Date();
	static string getDate();
};

#endif /* DATE_H_ */
