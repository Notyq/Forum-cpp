#pragma once
#include <iostream>
#include <string>

using namespace std;

class Topic {

protected:
	string title;
	//string desc;

public:
	Topic() {};
	Topic(string);

	void setTitle(string);
	string getTitle();

	//void setDesc(string);
	//string getDesc();
};