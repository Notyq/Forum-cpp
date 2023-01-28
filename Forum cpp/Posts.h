#pragma once
#include <iostream>
#include <string>

using namespace std;

class Posts {

private:
	string content;

public:
	Posts() {};
	Posts(string);

	void setContent(string);
	string getContent();
};