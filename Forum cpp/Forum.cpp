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

HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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

// Load Topics from Text File and returns a topicList
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

// Load Posts from Text File and returns a PostList
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

// Load Replies from Text File and returns a ReplyList
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

// Save Topics into Text File from TopicList
void saveTopic(TopicList topicList) {
    fstream file;
    string topic;

    file.open("topics.txt");
    for (int i = 0; i < topicList.getLength(); i++) {
        topic = topicList.get(i);
        file << topic + "\n";
    }
    file.close();
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

// Input of Topic content
string createTopic(string& topicName)
{
    cout << "New topic title: ";
    getline(cin >> ws, topicName);

    return topicName;
}

// Input of Post content
string createPost(string& postContent) {

    cout << "Create Post: \n";
    getline(cin >> ws, postContent);

    return postContent;
}

// Input of Reply content
string replyPost(string& reply) {

    cout << "Reply to post: \n";
    getline(cin >> ws, reply);

    return reply;
}
// Display Main Menu with username and returns choice of option

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
    cout << "[3] View Your Topics and Posts by you" << endl;
    cout << "[0] Exit" << endl;
    cout << "============================" << endl;
    cout << "Choice: ";
    cin >> choice;
    return choice;
}
// Display post & options for post and returns a bool value to check if a post is displayed
bool DisplayPost(string index, PostList postList, ReplyList replyList) {
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string id;
    string content;
    string user;
    string topic;
    string likes;
    for (int i = 0; i < postList.getLength(); i++) {
        if (index == postList.getID(i)) {
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
        if (replyList.getID(n) == index) {
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

// Displays the Post and its details, likes and replies and also allows
// users to reply to the post and like it. This requires the username, 
// PostList and ReplyList
void ViewPost(string username, PostList postList, ReplyList replyList) {
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string reply;
    string postID;
    cout << "Select Post id: ";
    cin >> postID;
    // check if there is post in topic
    if (postList.compareID(postID) == true) {
        while (true)
        {
            cout << "\033[2J\033[H";
            bool displayed = DisplayPost(postID, postList, replyList);
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
                    string reply;
                    for (int j = 0; j < postList.getLength(); j++) {
                        if (postList.compareID(postID) == true) {
                            replyPost(reply);
                            replyList.add(reply, username, postID);
                            saveReply(replyList);
                            cout << "\033[2J\033[H";
                            cout << "Reply posted!\n";
                            break;
                        }
                    }
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
    else {
        cout << "\033[2J\033[H";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Invalid option!" << endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
}

// Displays all posts under a topic using the postlist, topic list
void displayPostList(PostList postList, TopicList topicList, int index) {
    if (!postList.isEmpty()) {
        for (int j = 0; j < postList.getLength(); j++) {
            string postTitle = postList.getTitle(j);
            string postID = postList.getID(j);
            if (postTitle == topicList.get(index - 1)) {

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
}


int main()
{
    //Global variables
    Dictionary profiles;
    bool authenticated = true; // <--------- for yq's debugging
    string username;
    string choice;
    TopicList topicList = TopicList();
    PostList postList = PostList();
    ReplyList replyList = ReplyList();
    int id = 1;
    fstream file;

    // LinkedLists to store all information
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
        //display main menu
        choice = MainMenu(username);
        if (choice == "1") // view all topics
        {
            int option;
            int length = topicList.getLength();
            cout << "\033[2J\033[H";
            cout << "===========Topics===========" << endl;
            if (length > 0) {
                for (int i = 0; i < length; i++) {
                    string tName = topicList.get(i);
                    cout << i + 1 << " ";
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << tName << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                cout << "============================" << endl;
                cout << "[1] View topic";
                cout << "\n[2] Stick topic\n";
                cout << "============================" << endl;
                cout << "Option: ";
                cin >> option;

                if (option == 1) { // view into specific topic
                    int topicid;
                    cout << "Enter topic ID: ";
                    cin >> topicid;

                    if (topicid - 1 < length) {
                        cout << "\033[2J\033[H";
                        while (true) {
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "[" + topicList.get(topicid - 1) + "]" << endl;
                            SetConsoleTextAttribute(hConsole, 15);

                            displayPostList(postList, topicList, topicid);
                            
                            cout << "\n===========Options===========" << endl;
                            cout << "[1] Create new post" << endl;
                            cout << "[2] View post" << endl;
                            cout << "[3] Set sticky post" << endl;
                            cout << "[0] Back to Menu" << endl;
                            cout << "=============================" << endl;
                            cout << "Option: ";
                            string input;
                            cin >> input;

                            if (input == "1") { // create new posts
                                string postContent;
                                createPost(postContent);
                                if (!postList.isEmpty()) {
                                    postList.add(postContent, topicList.get(topicid - 1), to_string(id + postList.getLength()), username, "0");
                                }
                                else
                                {
                                    postList.add(postContent, topicList.get(topicid - 1), to_string(id), username, "0");
                                }
                                savePost(postList);
                                cout << "\033[2J\033[H";
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "Posted!\n";
                                SetConsoleTextAttribute(hConsole, 15);
                            }
                            else if (input == "2") { // view into specific posts (replies, likes)
                                ViewPost(username, postList, replyList);
                            }
                            else if (input == "3") // set sticky posts
                            {
                                int index;
                                cout << "\nChoose Post to stick: ";
                                cin >> index;

                                if (postList.getLength() >= index && postList.compareTitle(topicList.get(topicid - 1)) == true && postList.compareID(to_string(index)) == true) {
                                    postList.swap(to_string(index));
                                    cout << "\033[2J\033[H";
                                    cout << "Sticky post added!\n";
                                    savePost(postList);

                                    continue;
                                }
                                else
                                {
                                    cout << "\nInvalid option!\n";
                                }
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
                else if (option == 2)
                {
                    int index;
                    cout << "\nChoose topic to stick: ";
                    cin >> index;

                    if (topicList.getLength() >= index) {
                        topicList.swap(index - 1);
                        cout << "\nSticky topic added!\n";

                        saveTopic(topicList);
                    }
                    else
                    {
                        cout << "\nInvalid option!\n";
                    }
                }
                else
                {
                    cout << "\033[2J\033[H";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "Invalid Option\n" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                    continue;
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

        else if (choice == "2") { // creates topic
            string topicName; 
            createTopic(topicName);
 
            if (!topicList.isEmpty()) {
                for (int i = 0; i < topicList.getLength(); i++) {
                    string tName = topicList.get(i);
                    if (tName == topicName) { // validation if new topic name is already existing
                        cout << "\033[2J\033[H";
                        cout << "Topic already exists!\n";
                        break;
                    }
                    else if (tName != topicName and i+1 == topicList.getLength())
                    {                    
                        topicList.add(topicName);
                        saveTopic(topicList);
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
            else // adds immediately if no topics in topicList
            {
                topicList.add(topicName);
                file.open("topics.txt", fstream::app);
                file << topicName + "\n";
                file.close();
                cout << "\033[2J\033[H";
                cout << "Topic created!\n";
            }
        }

        else if (choice == "3") { // views all topics and post by own user
            cout << "\033[2J\033[H";
            while (true) {
                int numPost = 0;
                cout << "==============Topics and Posts by you==============" << endl;
                if (!postList.isEmpty()) {
                    for (int i = 0; i < postList.getLength(); i++) {
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
                        }
                    }                    
                    if (numPost == 0) { // if no posts made by user
                        cout << "No posts by user!\n\n";;
                        break;
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

                        if (input == "1") { // edit posts
                            string edit;
                            string id;
                            cout << "\nEnter post ID: ";
                            cin >> id;

                            for (int j = 0; j < postList.getLength(); j++) {
                                if (postList.compareID(id) == true && username == postList.getUser(j)) { // if current user matches post's user
                                    string title = postList.getTitle(j);
                                    string likes = postList.getLikes(j);
                                    string editCheck = " [edited]";
                                    cout << "Edit content: ";
                                    getline(cin >> ws, edit);
                                    postList.remove(id);
                                    postList.add(j, edit + editCheck, title, id, username, likes);
                                    savePost(postList);
                                    cout << "\033[2J\033[H";
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "Edited!\n";
                                    SetConsoleTextAttribute(hConsole, 15);
                                    break;
                                }
                                else if (j + 1 == postList.getLength()) // checks for valid id
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
                        else if (input == "2") { // delete post
                            bool match = false;
                            string inputID;
                            cout << "\nEnter post ID: ";
                            cin >> inputID;

                            for (int j = 0; j < postList.getLength(); j++) {
                                if (postList.compareID(inputID) && username == postList.getUser(j)) {
                                    match = true;
                                    string cfm;
                                    cout << "Confirm deletion (Y/N): ";
                                    cin >> cfm;

                                    if (cfm == "y") {
                                        postList.remove(inputID);
                                        id++;
                                        //postList.print();
                                        savePost(postList);
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