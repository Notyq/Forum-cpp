#pragma once
#include <iostream>
#include <string>

using namespace std;

class Topic {

private:
	string title;
	string desc;

public:
	Topic() {};
	Topic(string, string);

	void setTitle(string);
	string getTitle();

	void setDesc(string);
	string getDesc();
};