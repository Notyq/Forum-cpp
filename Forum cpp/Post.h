#pragma once
#include <string>
using namespace std;
class Post
{
public:
	string user;
	string id;
	string content;
	string title;

	Post(string User, string Id, string Content, string Title) {
		user = User;
		id = Id;
		content = Content;
		title = Title;
	}
};

