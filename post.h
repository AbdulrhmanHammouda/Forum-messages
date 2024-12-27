#ifndef POST_H
#define POST_H

#include <iostream>
#include "My_vector.h"
using namespace std;

template <typename UserType, typename ContentType>
class Post {
private:
    UserType username;
    ContentType content;
    My_vector<Post<UserType, ContentType>> replies;

public:
    Post() : username(UserType()), content(ContentType()) {}

    Post(const UserType& username, const ContentType& content)
        : username(username), content(content) {}

    void addReply(const Post<UserType, ContentType>& reply) {
        replies.push_back(reply);
    }

    // Getter for replies
    My_vector<Post<UserType, ContentType>>& getReplies() {
        return replies;
    }

    const My_vector<Post<UserType, ContentType>>& getReplies() const {
        return replies;
    }
    void addReplyToReply(size_t replyIndex, const Post<UserType, ContentType>& reply) {
        if (replyIndex >= replies.getSize()) {
            throw out_of_range("Reply index is out of range.");
        }
        replies[replyIndex].addReply(reply); // Allow chaining
    }
    void display(int indent = 0) const {
        cout << string(indent, ' ') << username << ": " << content << endl;
        for (const auto& reply : replies) {
            reply.display(indent + 4);
        }
    }

};

#endif
