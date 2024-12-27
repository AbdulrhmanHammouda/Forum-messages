#ifndef FORUM_H
#define FORUM_H

#include <iostream>
#include <vector>
#include "my_unordered_map.h"
#include "My_vector.h"
#include "post.h"
#include "My_Stack.h"
using namespace std;

template <typename UserType, typename ContentType>
class Forum {
private:
    my_unordered_map<UserType, My_vector<Post<UserType, ContentType>>> userPosts;

public:
    void createPost(const UserType& username, const ContentType& content) {
        Post<UserType, ContentType> post(username, content);//constructor
        My_vector<Post<UserType, ContentType>>* posts = nullptr;
        if (!userPosts.find(username, posts)) {
            userPosts.insert(username, My_vector<Post<UserType, ContentType>>());
            userPosts.find(username, posts); //posts = &userPosts[username];
        }
        posts->push_back(post);// -> because its a pointer
    }


    void deletePost(const UserType& username, const ContentType& content) {
        My_vector<Post<UserType, ContentType>>* posts = nullptr;
        if (!userPosts.find(username, posts)) {
            cerr << "the post is not found ";
            return;
        }
        userPosts.find(username, posts);
        My_vector x = userPosts[username];

        for (int i = 0; i < posts->getSize(); ++i) {
        if ((*posts)[i].getContent() == content) {
            posts->erase(i);
            break;
        }
    }
    }
    void displayForum() const {
        My_vector users = userPosts.getKeys(); // get usernames in a vector
        for (int i = 0; i < users.getSize(); ++i) {
             UserType& username = users[i]; //our user name
            My_vector<Post<UserType, ContentType>>* posts = nullptr;
            if (userPosts.find(username, posts)) {
                cout << "--- Posts by " << username << " ---\n";
                for (int j = 0; j < posts->getSize(); ++j) {
                    (*posts)[j].display();
                }
            }
        }
    }

    void replyToPost(const UserType& targetUser, int postIndex, const UserType& replyingUser, const ContentType& content, const My_vector<int>& replyPath) {
        try {
            My_vector<Post<UserType, ContentType>>* posts = nullptr;
            if (!userPosts.find(targetUser, posts)) {
                throw runtime_error("Target user not found.");
            }
            if (postIndex == 0 || postIndex > posts->getSize()) {
                throw out_of_range("Post index out of range.");
            }
            postIndex -= 1;

            Post<UserType, ContentType>* currentPost = &(*posts)[postIndex]; //p to the spec post
            for (int index : replyPath) {
                if (index == 0 || index > currentPost->getReplies().getSize()) {
                    throw out_of_range("Reply index in the path is out of range.");
                }
                currentPost = &currentPost->getReplies()[index - 1];
            }
            currentPost->addReply(Post<UserType, ContentType>(replyingUser, content));
        }
        catch (const exception& e) {
            cerr << "Error in replyToPost: " << e.what() << endl;
        }
    }
};

#endif