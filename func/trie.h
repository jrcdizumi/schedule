#ifndef TRIE_H
#define TRIE_H
#include<iostream>
#include "vector.h"
using namespace std;
struct TrieNode {
    Vector<int> is_end; // 标记是否为单词结尾
    TrieNode* next[1000]; // 指向下一个节点的指针数组
    TrieNode() {
        is_end.clear();
        for(int i = 0; i < 1000; i++)
            next[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root; // 根节点
public:
    Trie() {
        root = new TrieNode();
    }
    void insert(string word,int id) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->next[c + 128] == nullptr) {
                node->next[c + 128] = new TrieNode();
            }
            node = node->next[c + 128];
            node->is_end.push_back(id);
        }
        node->is_end.push_back(id);
    }
    Vector<int> search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->next[c + 128] == nullptr) {
                Vector<int> empty_vector;
                return empty_vector;
            }
            node = node->next[c + 128];
        }
        return node->is_end;
    }
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->next[c + 128] == nullptr) {
                return false;
            }
            node = node->next[c + 128];
        }
        return true;
    }
};

#endif // TRIE_H
