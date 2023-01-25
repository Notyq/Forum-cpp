// Forum cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using namespace std;

void logIn() {

    string username;
    string password;
    string choice;
    ofstream userProfiles;
    bool authenticated = false;

    while (authenticated == false) {
        cout << "===========Forums===========" << endl;
        cout << "[1] Login" << endl;
        cout << "[2] Sign Up" << endl;
        cout << "============================" << endl;
        cin >> choice;
        if (choice == "1") {
            cout << "Enter Username: " << endl;
            cin >> username;
            cout << "Enter Password: " << endl;
            cin >> password;
        }
        else if (choice == "2") {
            cout << "Enter a New Username: " << endl;
            cin >> username;
            cout << "Enter a New Password: " << endl;
            cin >> password;
            //open file for writing
            userProfiles.open("profiles.txt");
            userProfiles << "test\n";
            userProfiles.close();
        }
    }
}

int main()
{
    logIn();
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
