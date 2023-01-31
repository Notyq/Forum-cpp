#include <iostream>
#include "Topic.h"
#include <vector>
using namespace std;

Topic::Topic(string t) : title(t) { }

void Topic::setTitle(string t) { title = t; }

string Topic::getTitle() { return title; }

//void Topic::setDesc(string d) { desc = d; }

//string Topic::getDesc() { return desc; 