#include <iostream>
#include "Posts.h"
#include <vector>
using namespace std;

Posts::Posts(string c) { content = c; }

void Posts::setContent(string c) { content = c; }

string Posts::getContent() { return content; }