#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <iostream>
#include "my_unordered_map.h"
#include "My_Stack.h"
#include <stdexcept>
using namespace std;

template <typename KeyType, typename ValueType>
class UserManager {
private:
    my_unordered_map<KeyType, ValueType> users; // Custom my_unordered_map for user data
    KeyType currentUser;

public:
    void registerUser(const KeyType& username, const ValueType& password) {
        ValueType* existingPassword = nullptr;

        if (users.find(username, existingPassword)) {
            if (currentUser == username) {
                throw runtime_error("You are already registered and logged in with this username.");
            }
            else {
                throw runtime_error("This username is already registered by another user.");
            }
        }

        users.insert(username, password);
        cout << "User registered successfully.\n";
    }

    void login(const KeyType& username, const ValueType& password) {
        try {
            ValueType* storedPassword = nullptr;
            if (!users.find(username, storedPassword)) {
                throw runtime_error("Username not found.");
            }
            if (*storedPassword != password) {
                throw runtime_error("Incorrect password.");
            }
            currentUser = username;
            cout << "Login successful. Welcome, " << username << "!\n";
        }
        catch (const exception& e) {
            cerr << "Error during login: " << e.what() << endl;
        }
    }

    void logout() {
        if (!isLoggedIn()) {
            throw runtime_error("No user is currently logged in.");
        }
        cout << "Logged out successfully.\n";
        currentUser = KeyType();
    }

    bool isLoggedIn() const {
        return !currentUser.empty();
    }

    KeyType getCurrentUser() const {
        if (!isLoggedIn()) {
            throw runtime_error("No user is currently logged in.");
        }
        return currentUser;
    }
};

#endif
