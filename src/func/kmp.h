#ifndef KMP_H
#define KMP_H

#include <string>
#include <iostream>
#include <cstring>

using namespace std;
class KMP {
public:
    void get_next(char* p, int* next) {
        int p_len = strlen(p);
        next[0] = -1;
        int k = -1;
        int j = 0;
        while (j < p_len - 1) {
            if (k == -1 || p[j] == p[k]) {
                ++k;
                ++j;
                next[j] = k;
            } else {
                k = next[k];
            }
        }
    }

    int kmp(char* s, char* p) {
        int s_len = strlen(s);
        int p_len = strlen(p);
        int* next = new int[p_len];
        get_next(p, next);
        int i = 0;
        int j = 0;
        while (i < s_len && j < p_len) {
            if (j == -1 || s[i] == p[j]) {
                ++i;
                ++j;
            } else {
                j = next[j];
            }
        }
        delete[] next;
        if (j == p_len) {
            return i - j;
        } else {
            return -1;
        }
    }
};

#endif // KMP_H

