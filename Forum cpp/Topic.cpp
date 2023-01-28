#include <iostream>
#include "Topic.h"
#include <vector>
using namespace std;

Topic::Topic(string t, string d) { title = t, desc = d; }

void Topic::setTitle(string t) { title = t; }

string Topic::getTitle() { return title; }

void Topic::setDesc(string d) { desc = d; }

string Topic::getDesc() { return desc; }