//
// Created by 30205 on 2023/3/11.
//
#include <iostream>

using namespace std;

const int func()
{
	const int value = 1;
	return value;
}

int func()
{
	int value = 1;
	return value;
}

int main()
{
	return 0;
}