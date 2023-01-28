// Forum cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "Dictionary.h"

using namespace std;

bool logIn()
{

    string username;
    string password;
    string choice;
    fstream userProfiles;
    bool authenticated = false;

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
            userProfiles.open("profiles.txt");
            while (!authenticated) {   //checking whether the file is open
                bool nameFound = false;
                string profile;
                string name;
                while (!nameFound) { //read data from file object and put it into string.
                    cout << "Enter Username: ";
                    cin >> username;
                    while (!nameFound) {
                        getline(userProfiles, profile);
                        name = profile.substr(0, profile.find(","));
                        cout << name << endl;
                        if (name == username) {
                            nameFound = true;
                        }
                        if (userProfiles.eof()) {
                            cout << "Username is Not Found" << endl;
                            userProfiles.clear();
                            userProfiles.seekg(0);
                            break;
                        }
                    }
                }
                bool passRight = false;
                string pass;
                while (!passRight) { //read data from file object and put it into string.
                    cout << "Enter Password: " << endl;
                    cin >> password;
                    pass = profile.substr(profile.find(",")+1,profile.length() - 1);
                    cout << pass << endl;
                    if (pass == password) {
                        authenticated = true;
                        break;
                    }
                    else {
                        cout << "Password is Incorrect" << endl;
                    }
                }
                cout << "Successfully Logged In :)" << endl;
                return authenticated;
            }
        }
        // Sign Up
        else if (choice == "2")
        {
            cout << "Enter a New Username: " << endl;
            cin >> username;
            cout << "Enter a New Password: " << endl;
            cin >> password;
            // open file for writing
            userProfiles.open("profiles.txt");
            userProfiles << username + "," + password;
            userProfiles.close();
            authenticated = true;
            return authenticated;
        }
        else if (choice == "0") {
            exit(0);
        }
        else {
            cout << "Please Enter a Valid Option" << endl;
        }
    }
}

List createTopic(List topicList)
{
    string topicName;
    cout << "New topic title: " << endl;
    cin >> topicName;

    topicList.add(topicName);
    return topicList;
}

void ListTopics(List topicList)
{
    topicList.print();
}

int main()
{
    bool authenticated;
    List topicList = List();
    authenticated = logIn();
    //while (authenticated)
    //{
    //    string choice;
    //    cout << "===========Forums===========" << endl;
    //    cout << "View Topics" << endl;
    //    cout << "Create Topics" << endl;
    //    cout << "============================" << endl;
    //    cin >> choice;

    //    if (choice == "1")
    //    {
    //        ListTopics(topicList);
    //    }

    //    else if (choice == "2")
    //    {
    //        createTopic(topicList);
    //    }

    //    else
    //    {
    //        return false;
    //    }
    //}
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
