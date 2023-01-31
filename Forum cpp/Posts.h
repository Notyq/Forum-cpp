#pragma once
#include <iostream>
#include <string>

using namespace std;

#include "Topic.h"

class Posts : public Topic {

protected:
	string content;

public:
	Posts() {};
	Posts(string, string);

	void setContent(string);
	string getContent();
};