// Jason Heo Jung S10222947
// Tang Yong Qi S10221789
// Group 6

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>
#include <time.h>
#include <stdint.h>
#include <windows.h>
#include <vector>

#include "Dictionary.h"
#include "TopicList.h"
#include "PostList.h"
#include "ReplyList.h"

using namespace std;

// Login & SignUp Options for user authentication
string logIn(Dictionary profilesTable)
{
    string username;
    string password;
    DicItemType hPass;
    string choice;
    fstream userProfiles;
    bool authenticated = false;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Retrieve User Profiles and put in a hash table
    userProfiles.open("profiles.txt");
    while (userProfiles >> username >> password) {
        int Hpass = stoi(password);
        profilesTable.add(username, Hpass);
        if (userProfiles.eof()) {
            userProfiles.clear();
            userProfiles.seekg(0);
            break;
        }
    }
    userProfiles.close();

    // While not logged in
    while (authenticated == false)
    {
        cout << "\033[2J\033[H";
        cout << "=====Login/Signup=====" << endl;
        cout << "[1] Login" << endl;
        cout << "[2] Sign Up" << endl;
        cout << "[0] Exit" << endl;
        cout << "======================" << endl;
        cout << "Choice: ";
        cin >> choice;
        // Log In
        if (choice == "1")
        {
            userProfiles.open("profiles.txt");
            while (!authenticated) {   //checking whether the file is open
                bool nameFound = false;
                string profile;
                string name;
                while (!nameFound) {
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "[Enter '0' to Exit]" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                    cout << "Enter Username: ";
                    cin >> username;
                    if (username == "0") {
                        return "";
                    }
                    while (!nameFound) {
                        getline(userProfiles, profile);
                        name = profile.substr(0, profile.find(" "));
                        if (name == username) {
                            nameFound = true;
                        }
                        else if (userProfiles.eof()) {
                            cout << "Username is Not Found" << endl;
                            userProfiles.clear();
                            userProfiles.seekg(0);
                            break;
                        }
                    }
                }
                bool passRight = false;
                int pass;
                while (!passRight) {
                    cout << "Enter Password: ";
                    cin >> password;
                    pass = profilesTable.hash(password);
                    DicItemType check = profilesTable.get(username);
                    if (pass == check) {
                        authenticated = true;
                        break;
                    }
                    else {
                        cout << "Password is Incorrect" << endl;
                    }
                }
                userProfiles.close();
                return username;
            }
        }
        // Sign Up
        else if (choice == "2")
        {
            userProfiles.open("profiles.txt", fstream::app);
            bool nameConf = false;
            bool passConf = false;
            string confirm;
            // New Username
            while (!nameConf) {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "[Enter '0' to Exit]" << endl;
                SetConsoleTextAttribute(hConsole, 15);
                cout << "Enter a New Username: ";
                cin >> username;
                if (username == "0") {
                    return "";
                }
                nameConf = profilesTable.add(username, 12345); // Check if Username Taken
                if (!nameConf){
                    continue;
                }
            }
            // New Password
            while (!passConf) {
                cout << "Enter a New Password: ";
                cin >> password;
                cout << "Confirm?(Y/N): ";
                cin >> confirm;
                if (confirm == "y") {
                    profilesTable.remove(username);
                    hPass = profilesTable.hash(password);
                    profilesTable.add(username, hPass);
                    passConf = true;
                }
                else {
                    continue;
                }
            }
            // open file for writing of profile
            userProfiles << username + " " + to_string(hPass) + "\n";
            userProfiles.close();
            authenticated = true;
            
            return username;
        }
        else if (choice == "0") {
            exit(0);
        }
        else {
            cout << "Please Enter a Valid Option" << endl;
        }
    }
}
// Load Topics from Text File
TopicList loadTopic(TopicList topicList) {
    // Loading of saved topics
    fstream file;
    string topic;
    file.open("topics.txt");
    while (!file.eof()) {
        getline(file, topic);
        if (!topic.empty()) {
            topicList.add(topic);
        }
        if (file.eof()) {
            file.clear();
            file.seekg(0);
            break;
        }
    }
    file.close();
    return topicList;
}
// Load Posts from Text File
PostList loadPost(PostList postList) {
    fstream file;
    string Post;
    string delimiter = "-+-";
    int track = 0;
    string PostContent;
    string PostTopic;
    string postId;
    string PostUsername;
    string PostLikes;
    file.open("posts.txt");
    while (!file.eof()) {
        getline(file, Post);
        track = 0;
        size_t pos = 0;
        std::string token;
        while ((pos = Post.find(delimiter)) != std::string::npos) {
            token = Post.substr(0, pos);
            Post.erase(0, pos + delimiter.length());
            if (track == 0) {
                PostContent = token;
                track++;
            }
            else if (track == 1) {
                PostTopic = token;
                track++;
            }
            else if (track == 2) {
                postId = token;
                track++;
            }
            else if (track == 3) {
                PostUsername = token;
                track++;
            }
        }
        if (track == 4) {
            PostLikes = Post;
            track++;
        }
        if (file.eof()) {
            file.clear();
            file.seekg(0);
            break;
        }
        if (!PostContent.empty()) {
            postList.add(PostContent, PostTopic, postId, PostUsername, PostLikes);
        }
    }
    file.close();
    return postList;
}
// Load Replies from Text File
ReplyList loadReply(ReplyList replyList) {
    fstream file;
    string ReplyList;
    string delimiter = "-+-";
    int track;
    string ReplyUsername;
    string ReplyContent;
    string ReplyPost;

    file.open("replies.txt");
    while (!file.eof()) {
        getline(file, ReplyList);
        track = 0;
        size_t pos = 0;
        std::string token;
        while ((pos = ReplyList.find(delimiter)) != std::string::npos) {
            token = ReplyList.substr(0, pos);
            ReplyList.erase(0, pos + delimiter.length());
            if (track == 0) {
                ReplyContent = token;
                track++;
            }
            else if (track == 1) {
                ReplyPost = token;
                track++;
            }
        }
        if (track == 2) {
            ReplyUsername = ReplyList;
            track++;
        }
        if (file.eof()) {
            file.clear();
            file.seekg(0);
            break;
        }
        if (!ReplyContent.empty()) {
            replyList.add(ReplyContent, ReplyUsername, ReplyPost);
        }
    }
    file.close();
    return replyList;
}
// Save Posts into Text File from PostList
void savePost(PostList postList) {
    fstream file;
    string id;
    string user;
    string content;
    string title;
    string likes;

    file.open("posts.txt");
    for (int i = 0; i < postList.getLength(); i++) {
        id = postList.getID(i);
        user = postList.getUser(i);
        content = postList.getPost(i);
        title = postList.getTitle(i);
        likes = postList.getLikes(i);
        file << content + "-+-" + title + "-+-" + id + "-+-" + user + "-+-" +  likes + "\n";
    }
    file.close();
}
// Save Replies into Text File from ReplyList
void saveReply(ReplyList replyList) {
    fstream file;
    string content;
    string id;
    string user;
    file.open("replies.txt");
    for (int i = 0; i < replyList.getLength(); i++) {
        id = replyList.getID(i);
        user = replyList.getUser(i);
        content = replyList.get(i);
        file << content + "-+-" + id + "-+-" + user + "\n";
    }
    file.close();
}
// Input of Topic
string createTopic(string& topicName)
{
    cout << "New topic title: ";
    getline(cin >> ws, topicName);

    return topicName;
}
// Input of Post
string createPost(string& postContent) {

    cout << "Create Posts: \n";
    getline(cin >> ws, postContent);

    return postContent;
}
// Input of Reply
string replyPost(string& reply) {

    cout << "Reply to post: \n";
    getline(cin >> ws, reply);

    return reply;
}
// Display Main Menu
string MainMenu(string username) {
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "Current User: ";
    SetConsoleTextAttribute(hConsole, 10);
    cout << username << endl;
    string choice;
    SetConsoleTextAttribute(hConsole, 15);
    cout << "===========Forums===========" << endl;
    cout << "[1] View Topics" << endl;
    cout << "[2] Create Topics" << endl;
    cout << "[3] View Your Posts and Replies" << endl;
    cout << "[0] Exit" << endl;
    cout << "============================" << endl;
    cout << "Choice: ";
    cin >> choice;
    return choice;
}
// Display post & options for post
bool DisplayPost(int index, PostList postList, ReplyList replyList) {
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string id;
    string content;
    string user;
    string topic;
    string likes;
    for (int i = 0; i < postList.getLength(); i++) {
        if (index == stoi(postList.getID(i))) {
            id = postList.getID(i);
            content = postList.getPost(i);
            user = postList.getUser(i);
            topic = postList.getTitle(i);
            likes = postList.getLikes(i);
        }
    }
    if (id.empty()) {
        cout << "\033[2J\033[H";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Invalid Option" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return false;
    }
    SetConsoleTextAttribute(hConsole, 14);
    cout << "[" + topic + "]" << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << "[" << id << "] ";
    SetConsoleTextAttribute(hConsole, 9);
    cout << content << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << "    by ";
    SetConsoleTextAttribute(hConsole, 10);
    cout << user << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Likes: ";
    SetConsoleTextAttribute(hConsole, 12);
    cout << likes << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Replies: " << endl;
    for (int n = 0; n < replyList.getLength(); n++) {
        if (replyList.getID(n) == to_string(index + 1)) {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "[" + replyList.getUser(n) + "]";
            SetConsoleTextAttribute(hConsole, 15);
            cout << " - " << replyList.get(n) + "\n" << endl;
        }
        else
        {
            continue;
        }
    }
    return true;
}
// Reply to a post
void replyToPost(string postID, string username, PostList postList, ReplyList replyList) {
    string reply;
    for (int j = 0; j < postList.getLength(); j++) {
        if (postID == postList.getID(j)) {
            replyPost(reply);
            replyList.add(reply, username, postID);
            saveReply(replyList);
            cout << "\033[2J\033[H";
            cout << "Reply posted!\n";
        }
    }
}

void ViewPost(string username, PostList postList, ReplyList replyList) {
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string reply;
    string postID;
    cout << "Select Post id: ";
    cin >> postID;
    // check if there is post in topic
    if (stoi(postID) > postList.getLength() || stoi(postID) < 1) {
        cout << "\033[2J\033[H";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Invalid option!" << endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
    else {
        while (true)
        {
            cout << "\033[2J\033[H";
            bool displayed = DisplayPost(stoi(postID), postList, replyList);
            if (!displayed) {
                cout << "\033[2J\033[H";
                SetConsoleTextAttribute(hConsole, 12);
                cout << "Invalid Option" << endl;
                SetConsoleTextAttribute(hConsole, 15);
                break;
            }
            else {
                cout << "\n===========Options===========" << endl;
                cout << "[1] Reply" << endl;
                cout << "[2] Like" << endl;
                cout << "[0] Back to Menu" << endl;
                cout << "=============================" << endl;
                cout << "Option: ";
                string input;
                cin >> input;
                if (input == "1") {
                    replyToPost(postID, username, postList, replyList);
                }
                else if (input == "2") {
                    postList.giveLike(stoi(postID));
                    savePost(postList);
                    cout << "\033[2J\033[H";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "Post Liked!\n";
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else if (input == "0") {
                    cout << "\033[2J\033[H";
                    break;
                }
                else {
                    cout << "\033[2J\033[H";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "Invalid Option" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
        }
    }
}

void displayReply(ReplyList replyList, PostList postList) {

    for (int n = 0; n < replyList.getLength(); n++) {
        for (int j = 0; j < postList.getLength(); j++) {
            if (replyList.getID(n) == postList.getID(j)) {
                cout << "          [ " << replyList.get(n) << " ]" << endl;
                cout << "                    -" << replyList.getUser(n);
            }
            else
            {
                continue;
            }
        }
    }
}

int main()
{
    //Global variables
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Dictionary profiles;
    bool authenticated = true; // <--------- for yq's debugging
    string username;
    string choice;
    TopicList topicList = TopicList();
    PostList postList = PostList();
    ReplyList replyList = ReplyList();
    int id = 1;
    fstream file;

    topicList = loadTopic(topicList);
    postList = loadPost(postList);
    replyList = loadReply(replyList);

    // When user is not logged in
    while (username.empty()) {
        username = logIn(profiles);
        if (!username.empty()) {
            authenticated = true;
        }
    }

    cout << "\033[2J\033[H";
    while (authenticated)
    {
        choice = MainMenu(username);
        if (choice == "1")
        {
            int option;
            int length = topicList.getLength();
            cout << "\033[2J\033[H";
            cout << "===========Topics===========" << endl;
            if (length > 0) {
                for (int i = 0; i < length; i++) {
                    string tName = topicList.get(i);
                    cout << "[" << i + 1 << "] ";
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << tName << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                cout << "============================" << endl;
                cout << "Enter option: ";
                cin >> option;

                if (option - 1 < length) {
                    cout << "\033[2J\033[H";
                    while (true) {
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << "[" + topicList.get(option - 1) + "]" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                    if (!postList.isEmpty()) {
                        for (int j = 0; j < postList.getLength(); j++) {
                            string postTitle = postList.getTitle(j);
                            string postID = postList.getID(j);
                            if (postTitle == topicList.get(option - 1)) {

                                cout << "[" << postID << "] ";
                                SetConsoleTextAttribute(hConsole, 9);
                                cout << postList.getPost(j) << endl;
                                SetConsoleTextAttribute(hConsole, 15);
                                cout << "    by ";
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << postList.getUser(j) << endl;
                                SetConsoleTextAttribute(hConsole, 15);
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    else
                    {
                        cout << "No posts Found!\n " << endl;
                    }
                        cout << "\n===========Options===========" << endl;
                        cout << "[1] Create new post" << endl;
                        cout << "[2] View post" << endl;
                        cout << "[0] Back to Menu" << endl;
                        cout << "=============================" << endl;
                        cout << "Option: ";
                        string input;
                        cin >> input;

                        if (input == "1") {
                            string postContent;
                            cout << endl;

                            createPost(postContent);
                            if (!postList.isEmpty()) {
                                postList.add(postContent, topicList.get(option - 1), to_string(id + postList.getLength()), username, "0");
                            }
                            else
                            {
                                postList.add(postContent, topicList.get(option - 1), to_string(id), username, "0");
                            }
                            savePost(postList);
                            cout << "\033[2J\033[H";
                            SetConsoleTextAttribute(hConsole, 10);
                            cout << "Posted!\n";
                            SetConsoleTextAttribute(hConsole, 15);
                        }
                        else if (input == "2") {
                            ViewPost(username, postList, replyList);
                        }
                        else if (input == "0")
                        {
                            cout << "\033[2J\033[H";
                            break;
                        }
                        else
                        {
                            cout << "\033[2J\033[H";
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "Invalid option!\n" << endl;
                            SetConsoleTextAttribute(hConsole, 15);
                        }
                    }
                    
                }
                else 
                {
                    cout << "\033[2J\033[H";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "Invalid option!\n" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
            else
            {
                cout << "\033[2J\033[H";
                SetConsoleTextAttribute(hConsole, 12);
                cout << "No Topics Found\n" << endl;
                SetConsoleTextAttribute(hConsole, 15);
                continue;
            }
        }   

        else if (choice == "2") {
            string topicName; 
            createTopic(topicName);
 
            if (!topicList.isEmpty()) {
                for (int i = 0; i < topicList.getLength(); i++) {
                    string tName = topicList.get(i);
                    if (tName == topicName) {
                        cout << "\033[2J\033[H";
                        cout << "Topic already exists!\n";
                        break;
                    }
                    else if (tName != topicName and i+1 == topicList.getLength())
                    {                    
                        topicList.add(topicName);
                        file.open("topics.txt", fstream::app);
                        file << topicName + "\n";
                        file.close();
                        cout << "\033[2J\033[H";
                        cout << "Topic created!\n";
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                topicList.add(topicName);
                file.open("topics.txt", fstream::app);
                file << topicName + "\n";
                file.close();
                cout << "\033[2J\033[H";
                cout << "Topic created!\n";
            }
            
            //string title = topicList.get(0);
            //cout << title << endl;
        }

        else if (choice == "3") {
            cout << "\033[2J\033[H";
            while (true) {
                int numPost = 0;
                int i = 0;
                cout << "===================Posts===================" << endl;
                if (!postList.isEmpty()) {
                    while (i < postList.getLength()) {
                        if (postList.getUser(i) == username) {
                            string ID = postList.getID(i);
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "[" + postList.getTitle(i) + "]" << endl;
                            SetConsoleTextAttribute(hConsole, 15);
                            cout << "ID:[" << ID << "] ";
                            SetConsoleTextAttribute(hConsole, 9);
                            cout << postList.getPost(i) << endl;
                            SetConsoleTextAttribute(hConsole, 15);
                            numPost += 1;
                            i += 1;
                        }
                        else
                        {
                            i++;
                        }
                    }
                    if (numPost == 0) {
                        cout << "\n No posts by user!\n";;
                    }
                    else
                    {
                        cout << "\n===========Options===========" << endl;
                        cout << "[1] Edit Post" << endl;
                        cout << "[2] Delete Post" << endl;
                        cout << "[3] View Post" << endl;
                        cout << "[0] Back to Menu" << endl;
                        cout << "=============================" << endl;
                        cout << "Choice: ";
                        string input;
                        cin >> input;

                        if (input == "1") {
                            string edit;
                            string id;
                            cout << "\nEnter post ID: ";
                            cin >> id;

                            for (int j = 0; j < postList.getLength(); j++) {
                                if (id == postList.getID(j) && username == postList.getUser(j)) {
                                    string title = postList.getTitle(j);
                                    string likes = postList.getLikes(j);
                                    string editCheck = " [edited]";
                                    cout << "Edit content: ";
                                    getline(cin >> ws, edit);
                                    postList.remove(stoi(id) - 1);
                                    postList.add(stoi(id) - 1, edit + editCheck, title, id, username, likes);
                                    savePost(postList);
                                    cout << "\033[2J\033[H";
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "Edited!\n";
                                    SetConsoleTextAttribute(hConsole, 15);
                                    break;
                                }
                                else if (j + 1 == postList.getLength())
                                {
                                    cout << "\033[2J\033[H";
                                    SetConsoleTextAttribute(hConsole, 12);
                                    cout << "Invalid Option" << endl;
                                    SetConsoleTextAttribute(hConsole, 15);
                                    break;
                                }
                                else
                                {
                                    continue;
                                }
                            }
                        }
                        else if (input == "2") {
                            bool match = false;
                            string inputID;
                            cout << "\nEnter post ID: ";
                            cin >> inputID;

                            for (int j = 0; j < postList.getLength(); j++) {
                                if (inputID == postList.getID(j) && username == postList.getUser(j)) {
                                    match = true;
                                    string cfm;
                                    cout << "Confirm deletion (Y/N): ";
                                    cin >> cfm;

                                    if (cfm == "y") {
                                        postList.remove(j);
                                        savePost(postList);
                                        id++;
                                        cout << "\nDeleted!\n";

                                    }
                                    else if (cfm == "n") {
                                        cout << "Cancelling deletion...\n" << endl;
                                        break;
                                    }
                                    else
                                    {
                                        cout << "\033[2J\033[H";
                                        SetConsoleTextAttribute(hConsole, 12);
                                        cout << "Invalid Option" << endl;
                                        SetConsoleTextAttribute(hConsole, 15);
                                    }
                                }
                                else if (j + 1 == postList.getLength() && match == false)
                                {
                                    cout << "\033[2J\033[H";
                                    SetConsoleTextAttribute(hConsole, 12);
                                    cout << "Invalid Option" << endl;
                                    SetConsoleTextAttribute(hConsole, 15);
                                    break;
                                }
                                else
                                {
                                    continue;
                                }
                            }

                        }
                        else if (input == "3") {
                            ViewPost(username, postList, replyList);
                        }
                        else if (input == "0") {
                            cout << "\033[2J\033[H";
                            break;
                        }
                        else
                        {
                            cout << "\033[2J\033[H";
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "Invalid Option!" << endl;
                            SetConsoleTextAttribute(hConsole, 15);
                            continue;
                        }
                    }
                }
                else
                {
                    cout << "\033[2J\033[H";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "No posts by user!\n" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
        }

        else if (choice == "0") {
            cout << "\033[2J\033[H";
            return false;
        }

        else {
            cout << "\033[2J\033[H";
            cout << "Invalid option, please try again\n";
            continue;
        }
    }
}