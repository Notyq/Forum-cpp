// Forum cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include "LinkedList.h"
#include "Dictionary.h"
#include "Topic.h"
#include "Posts.h"

using namespace std;

string logIn(Dictionary profilesTable)
{
    string username;
    string password;
    DicItemType hPass;
    string choice;
    fstream userProfiles;
    bool authenticated = false;

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

    while (authenticated == false)
    {
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
            while (!authenticated) {   //checking whether the file is open
                bool nameFound = false;
                string profile;
                string name;
                while (!nameFound) {
                    cout << "Enter Username: ";
                    cin >> username;
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
                string pass;
                while (!passRight) {
                    cout << "Enter Password: ";
                    cin >> password;
                    pass = profile.substr(profile.find(" ")+1,profile.length() - 1);
                    hPass = stoi(pass);
                    DicItemType check = profilesTable.get(username);
                    if (hPass == check) {
                        authenticated = true;
                        break;
                    }
                    else {
                        cout << "Password is Incorrect" << endl;
                    }
                }
                cout << "Successfully Logged In :)" << endl;
                return username;
            }
        }
        // Sign Up
        else if (choice == "2")
        {
            bool nameConf = false;
            bool passConf = false;
            string confirm;
            // New Username
            while (!nameConf) {
                cout << "Enter a New Username: ";
                cin >> username;
                cout << "Confirm?(Y/N): ";
                cin >> confirm;
                if (confirm == "y") {
                    nameConf = profilesTable.add(username, 12345); // Check if Username Taken
                }
                else {
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
            // open file for writing
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
    cin >> topicName;

    return topicName;
}

string createPost(string& postContent) {


    cout << "Create Posts: \n";
    getline(cin >> ws, postContent);

    return postContent;
}

int main()
{
    Dictionary profiles;
    bool authenticated = true; // <--------- for yq's debugging
    Topic topicList = Topic();
    Posts postList = Posts();
    string username;

    // login / singup function
    username = logIn(profiles);
    if (!username.empty()) {
        authenticated = true;
    }
    Topic topic = Topic();
    logIn(profiles);

    while (authenticated)
    {
        string choice;
        cout << "\n===========Forums===========" << endl;
        cout << "[1] View Topics" << endl;
        cout << "[2] Create Topics" << endl;
        cout << "[0] Exit" << endl;
        cout << "============================" << endl;
        cin >> choice;

        if (choice == "1")
        {
            int option;
            int length = topicList.getLength();

            if (length > 0) {
                for (int i = 0; i < length; i++) {
                    string tName = topicList.get(i);
                    cout << "[" << i + 1 << "] " << tName << endl;
                }

                cout << "Enter option to view topic: \n";
                cin >> option;

                for (int i = 0; i < length; i++) {
                    if (option - 1 == i) {
                        cout << "\nTopic:\n" << topicList.get(i) << endl;
                        cout << "\nPosts:\n";
                        if (!postList.isEmpty()) {
                            for (int j = 0; j < postList.getLength(); j++) {
                                string postTitle = postList.getTitle(j);
                                if (postTitle == topicList.get(i)) {
                                    cout << "[" << j+1 << "] " << postList.getPost(j) << endl;
                                    continue;
                                }
                                else if (postTitle != topicList.get(i) and j == postList.getLength())
                                {
                                    cout << "No posts in this topic!\n";
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
                            cout << "No posts!\n ";
                        }

                        cout << "\n===========Options===========" << endl;
                        cout << "[1] Create new post" << endl;
                        cout << "[2] Reply to post" << endl;
                        cout << "[0] Back to Menu" << endl;
                        cout << "===============================" << endl;
                        string input;
                        cin >> input;

                        if (input == "1") {
                            string postContent;
                            cout << endl;
                            createPost(postContent);
                            postList.add(postContent, topicList.get(i));
                            cout << "\nPosted!\n";
                        }
                        else if (input == "2") {
                            continue;
                        }
                        else if (input == "0")
                        {
                            continue;
                        }
                        else
                        {
                            cout << "Invalid option!\n";
                        }
                    }
                    else
                    {
                        cout << "Invalid option!\n";
                    }
                }
                /*string temp = topicList.get(option - 1);
                if (temp == topic);*/
            }
            else
            {
                cout << "No Topics\n";
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
                        cout << "Topic already exists!\n";
                        break;
                    }
                    else if (tName != topicName and i+1 == topicList.getLength())
                    {                    
                        topicList.add(i, topicName);
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
                cout << "Topic created!\n";
            }
            
            //string title = topicList.get(0);
            //cout << title << endl;
        }

        else if (choice == "0")
        {
            return false;
        }

        else
        {
            cout << "Invalid option, please try again\n";
            main();
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
