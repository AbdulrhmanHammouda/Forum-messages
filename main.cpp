#include <iostream>
#include "forum.h"
#include "user.h"
#include "My_vector.h"
#include "my_unordered_map.h"
#include "My_Stack.h"
#include <string>

using namespace std;

void displayMenu() {
    cout << "\n--- Forum Menu ---\n";
    cout << "1. Register User\n";
    cout << "2. Login User\n";
    cout << "3. Create Post\n";
    cout << "4. Reply to Post\n";
    cout << "5. delte post\n";
    cout << "6. Display Forum\n";
    cout << "7. Logout\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Forum<string, string> forum;
    UserManager<string, string> userManager;
    string username, password, content;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        try {
            switch (choice) {
            case 1: // Register
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                while (password.length() < 8) {
                    cout << "Password must be at least 8 characters long.\n";
                    cout << "Enter password: ";
                    getline(cin, password);
                }
                userManager.registerUser(username, password);
                break;

            case 2: // Login
                if (userManager.isLoggedIn()) {
                    throw runtime_error("You are already logged in.");
                }
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                userManager.login(username, password);
                break;

            case 3: // Create Post
                if (!userManager.isLoggedIn()) {
                    cout << "You must be logged in to create a post.\n";
                    break;
                }

                do {
                    cout << "Enter post content (cannot be empty): ";
                    getline(cin, content);

                    if (content.empty()) {
                        cout << "Error: Post content cannot be empty. Please try again.\n";
                    }
                } while (content.empty());

                forum.createPost(userManager.getCurrentUser(), content);
                break;

            case 4: // Reply to Post
                try {
                    if (!userManager.isLoggedIn()) {
                        throw runtime_error("You must be logged in to reply to a post.");
                    }

                    cout << "Enter the target user's username: ";
                    getline(cin, username);

                    int postIndex;
                    cout << "Enter the post index to reply to: ";
                    if (!(cin >> postIndex) || postIndex < 1) {
                        throw invalid_argument("Invalid post index. Must be a positive integer.");
                    }
                    cin.ignore();

                    My_vector<int> replyPath;
                    cout << "Enter reply path indices separated by spaces (end with -1): ";
                    int index;
                    while (cin >> index && index != -1){
                        replyPath.push_back(index);
                    }
                    cin.ignore();

                    cout << "Enter reply content: ";
                    getline(cin, content);

                    forum.replyToPost(username, postIndex, userManager.getCurrentUser(), content, replyPath);
                }
                catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                }
                break;
            case 5: // Create Post
                if (!userManager.isLoggedIn()) {
                    cout << "You must be logged in to create a post.\n";
                    break;
                }

                do {
                    cout << "Enter post content (cannot be empty): ";
                    getline(cin, content);

                    if (content.empty()) {
                        cout << "Error: Post content cannot be empty. Please try again.\n";
                    }
                } while (content.empty());

                forum.deletePost(userManager.getCurrentUser(), content);
                break;

            case 6: // Display Forum
                forum.displayForum();
                break;
            
            case 7: // Logout
                userManager.logout();
                break;

            case 8: // Exit
                cout << "Exiting program.\n";
                return 0;
             
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
