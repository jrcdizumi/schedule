#ifndef USERTRIE_H
#define USERTRIE_H

#include <iostream>
#include <string>

using namespace std;

class UserTrieNode {
public:
    UserTrieNode* children[10];
    bool is_end_of_word;
    string password;

    UserTrieNode() {
        for (int i = 0; i < 10; i++) {
            children[i] = nullptr;
        }
        is_end_of_word = false;
        password = "";
    }
};

class UserTrie {
public:
    UserTrieNode* root;

    UserTrie() {
        root = new UserTrieNode();
    }

    void insert(string word, string password) {
        UserTrieNode* current = root;
        for (char c : word) {
            if (!isdigit(c)) {
                cout << "Error: student ID should only contain digits." << endl;
                return;
            }

            int num = c - '0';
            if (current->children[num] == nullptr) {
                current->children[num] = new UserTrieNode();
            }
            current = current->children[num];
        }
        current->is_end_of_word = true;
        current->password = password;
    }

    string search(string word) {
        UserTrieNode* current = root;
        for (char c : word) {
            if (!isdigit(c)) {
                cout << "Error: student ID should only contain digits." << endl;
                return "";
            }

            int num = c - '0';
            if (current->children[num] == nullptr) {
                return "";
            }
            current = current->children[num];
        }
        if (current->is_end_of_word) {
            return current->password;
        }
        return "";
    }
};

#endif