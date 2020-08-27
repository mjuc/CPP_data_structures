#pragma once
#include<ctime>
#include<iostream>

class timeCnt
{
public:
	timeCnt();
	~timeCnt();
	void Tic();
	void Toc();
private:
	clock_t prevtim;
};

