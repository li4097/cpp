/*
 * utility.cpp
 * Copyright (C) 2019/04/09 LQ 
 *
 * Distributed under terms of the MIT license.
 */

#include "utility.h"


void getTime(uint64_t& sec,uint64_t& msec)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	sec = tv.tv_sec;
	msec = tv.tv_usec / 1000 + sec * 1000;
}
void printTime()
{
	uint64_t sec,msec;
	getTime(sec,msec);

	cout << "sec: " << sec << ",  msec: "
		<< msec << endl;

	return;
}
uint64_t getTime()
{
	uint64_t sec,msec;
	getTime(sec,msec);

	return msec;
}
