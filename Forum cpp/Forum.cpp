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

#include "LinkedList.h"
#include "Dictionary.h"
#include "Topic.h"
#include "Posts.h"
#include "Reply.h"

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
        cout << "===========Forums===========" << endl;
        cout << "[1] Login" << endl;
        cout << "[2] Sign Up" << endl;
        cout << "[0] Exit" << endl;
        cout << "============================" << endl;
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
            userProfiles << username + " " + to_string(hPass);
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

string createTopic(string& topicName)
{
    cout << "New topic title: \n";
    getline(cin >> ws, topicName);

    return topicName;
}

string createPost(string& postContent, time_t time) {

    cout << "Create Posts: \n";
    getline(cin >> ws, postContent);
    char buffer[26];
    ctime_s(buffer, sizeof buffer, &time);

    return postContent, buffer;
}

string replyPost(string& reply) {

    cout << "Reply to post: \n";
    getline(cin >> ws, reply);

    return reply;
}

//void displayReplies(int numReplies, )

int main()
{
    //Global variables
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Dictionary profiles;
    bool authenticated = true; // <--------- for yq's debugging
    string username;
    Topic topicList = Topic();
    Posts postList = Posts();
    Reply replyList = Reply();
    int id = 0;
    fstream file;

    // Loading of saved topics
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

    string PostContent;
    string PostTopic;
    string postId;
    string PostUsername;
    time_t PostTime;
    file.open("posts.txt");
    while (file >> PostContent >> PostTopic >> postId >> PostUsername >> PostTime) {
        if (!PostContent.empty()) {
            postList.add(PostContent, PostTopic, postId, PostUsername, PostTime);
        }
        if (file.eof()) {
            file.clear();
            file.seekg(0);
            break;
        }
    }
    file.close();

    string ReplyUsername;
    string ReplyContent;
    string ReplyPost;
    string ReplyUsername;
    time_t ReplyTime;
    file.open("replies.txt");
    while (file >> ReplyContent >> PostTopic >> postId >> PostUsername >> PostTime) {
        if (!ReplyContent.empty()) {
            replyList.push(ReplyContent, ReplyPost);
        }
        if (file.eof()) {
            file.clear();
            file.seekg(0);
            break;
        }
    }
    file.close();

    // When user is not logged in
    while (username.empty()) {
        username = logIn(profiles);
        if (!username.empty()) {
            authenticated = true;
        }
    }
    //Topic topic = Topic();

    cout << "\033[2J\033[H";
    while (authenticated)
    {
        cout << "Current User: ";
        SetConsoleTextAttribute(hConsole, 10);
        cout << username << endl;
        string choice;
        SetConsoleTextAttribute(hConsole, 15);
        cout << "===========Forums===========" << endl;
        cout << "[1] View Topics" << endl;
        cout << "[2] Create Topics" << endl;
        cout << "[0] Exit" << endl;
        cout << "============================" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice == "1")
        {
            int option;
            int length = topicList.getLength();
            cout << "\033[2J\033[H";
            cout << "===========";
            SetConsoleTextAttribute(hConsole, 14);
            cout << "Topics";
            SetConsoleTextAttribute(hConsole, 15);
            cout << "===========" << endl;
            if (length > 0) {
                for (int i = 0; i < length; i++) {
                    string tName = topicList.get(i);
                    cout << "[" << i + 1 << "] " << tName << endl;
                }
                cout << "============================" << endl;
                cout << "Enter option to view topic: \n";
                cin >> option;

                for (int i = 0; i < length; i++) {
                    if (option - 1 == i) {
                        cout << "\033[2J\033[H";
                        cout << "==========";
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << topicList.get(i);
                        SetConsoleTextAttribute(hConsole, 15);
                        cout << "==========" << endl;
                        if (!postList.isEmpty()) {
                            for (int j = 0; j < postList.getLength(); j++) {
                                string postTitle = postList.getTitle(j);
                                if (postTitle == topicList.get(i)) {
                                    cout << "[" << j+1 << "] " << postList.getPost(j) << endl;
                                    cout << "      by " << username << " >> " << postList.getTime(j);
                                    int n = 0;
                                    while (!replyList.isEmpty() and n < replyList.getLength()) {
                                        if (replyList.getID(n) == to_string(j+1)) {
                                            cout << "     - " << replyList.get(n) << endl;
                                            n++;
                                        }
                                        else
                                        {
                                            n++;
                                        }
                                    }
                                    continue;
                                }
                                else if (postTitle != topicList.get(i) and j == postList.getLength())
                                {
                                    cout << "\033[2J\033[H";
                                    cout << "No posts in this topic!\n" << endl;
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
                            cout << "No posts Found!\n " << endl;
                        }

                        cout << "\n===========Options===========" << endl;
                        cout << "[1] Create new post" << endl;
                        cout << "[2] Reply to post" << endl;
                        cout << "[0] Back to Menu" << endl;
                        cout << "=============================" << endl;
                        string input;
                        cin >> input;

                        if (input == "1") {
                            string postContent;
                            cout << endl;
                            auto now = chrono::system_clock::now();
                            time_t now_c = chrono::system_clock::to_time_t(now);
                            createPost(postContent, now_c);
                            id++;
                            postList.add(postContent, topicList.get(i), to_string(id), username, now_c);
                            file.open("posts.txt", fstream::app);
                            file << postContent + " " + topicList.get(i) + " " + to_string(id) + " " + username + " " + to_string(now_c) +"\n";
                            file.close();
                            cout << "\nPosted!\n";
                            postList.print();
                        }
                        else if (input == "2") {

                            // check if there is post in topic
                            string reply;
                            string postID;
                            cout << "Select Post id: ";
                            cin >> postID;

                            if (stoi(postID) <= id and stoi(postID) > 0) {
                                replyPost(reply);
                                replyList.push(reply, postID);
                                file.open("replies.txt", fstream::app);
                                file << reply + " " + postID;
                                file.close();
                                cout << "Reply posted!\n";
                            }
                            else
                            {
                                cout << "Invalid option!\n";
                            }
                        }
                        else if (input == "0")
                        {
                            cout << "\033[2J\033[H";
                            continue;
                        }
                        else
                        {
                            cout << "\033[2J\033[H";
                            cout << "Invalid option!\n" << endl;
                        }
                    }
                    else
                    {
                        cout << "\033[2J\033[H";
                        cout << "Invalid option!\n" << endl;
                        continue;
                    }
                }
            }
            else
            {
                cout << "\033[2J\033[H";
                cout << "No Topics Found\n" << endl;
                continue;
            }
        }   

        else if (choice == "2") 
        {
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

        else if (choice == "0")
        {
            cout << "\033[2J\033[H";
            return false;
        }

        else
        {
            cout << "\033[2J\033[H";
            cout << "Invalid option, please try again\n";
            continue;
        }
    }
}