// Forum cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include "LinkedList.h"
#include "Dictionary.h"
#include "Topic.h"
#include "Posts.h"

using namespace std;

bool logIn()
{

    string username;
    string password;
    string choice;
    ofstream userProfiles;
    bool authenticated = false;

    while (authenticated == false)
    {
        cout << "===========Forums===========" << endl;
        cout << "[1] Login" << endl;
        cout << "[2] Sign Up" << endl;
        cout << "============================" << endl;
        cin >> choice;
        if (choice == "1")
        {
            cout << "Enter Username: " << endl;
            cin >> username;
            cout << "Enter Password: " << endl;
            cin >> password;
            authenticated = true;
        }
        else if (choice == "2")
        {
            cout << "Enter a New Username: " << endl;
            cin >> username;
            cout << "Enter a New Password: " << endl;
            cin >> password;
            // open file for writing
            userProfiles.open("profiles.txt");
            userProfiles << "test\n";
            userProfiles.close();
            authenticated = true;
        }
    }
    return authenticated;
}

Topic createTopic(Topic t1)
{

    string topicName;
    string topicDesc;

    cout << "New topic title: \n";
    cin >> topicName;
    cout << "Topic description: \n";
    cin >> topicDesc;

    Topic t1(topicName, topicDesc);

    return t1;
}

int main()
{
    bool authenticated;
    List topicList = List();
    authenticated = logIn();
    Topic topic = Topic();

    while (authenticated)
    {
        string choice;
        cout << "===========Forums===========" << endl;
        cout << "View Topics" << endl;
        cout << "Create Topics" << endl;
        cout << "============================" << endl;
        cin >> choice;

        if (choice == "1")
        {
            topicList.print();
        }

        else if (choice == "2")
        {
            createTopic(topic);
            topicList.add(topic.getTitle());
        }

        else
        {
            return false;
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
