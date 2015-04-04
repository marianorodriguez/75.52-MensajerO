#ifndef TIME_H_
#define TIME_H_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>

using namespace std;

class Time {
public:
	Time();
	virtual ~Time();
	static string getTime();
};

#endif /* TIME_H_ */
