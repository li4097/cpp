/*
 * utility.h
 * Copyright (C) 2019 LQ <LQ@localhost.localdomain>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef UTILITY_H
#define UTILITY_H

#include<iostream>
#include<stdio.h>
#include<stdint.h>
#include<memory.h>
#include<sys/time.h>
#include<stdlib.h>
//#include<time.h>


using namespace std;

void getTime(uint64_t& sec,uint64_t& msec);
void printTime();
uint64_t getTime();

template<class T>
class Stack{
public:
	Stack()
		:size(10),
		index(0)
	{
		array = new T[size];
		memset(array,0,sizeof(T) * size);
	}
	~Stack()
	{
		delete []array;
	}
	bool Push(T data)
	{
		if(size <= index)
		{
			T* tmp = new T[size * 2];
			if(nullptr == tmp)
			{
				return false;
			}
			memcpy(tmp,array,sizeof(T) * size);
			delete []array;
			array = tmp;
			size *= 2;
		}
		array[index] = data;
		index++;

		return true;
	}
	T Pop()
	{
		if(0 >= index)
		{
			return nullptr;
		}
		return array[--index];
	}
	bool Empty()
	{
		return index <= 0;
	}
private:
	uint32_t size;
	int index;

	T* array;

};

#endif /* !UTILITY_H */
