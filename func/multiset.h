#ifndef MULTISET_H
#define MULTISET_H

template<typename T>
class multiset {
private:
    struct Node {
        T val;
        int cnt;
        Node *left, *right;
        Node(T v) : val(v), cnt(1), left(nullptr), right(nullptr) {}
    };
    Node *root;
    int size;
    void clear(Node *p) {
        if (p == nullptr) return;
        clear(p->left);
        clear(p->right);
        delete p;
    }
    Node *insert(Node *p, T v) {
        if (p == nullptr) return new Node(v);
        if (v == p->val) {
            ++p->cnt;
            return p;
        }
        if (v < p->val) p->left = insert(p->left, v);
        else p->right = insert(p->right, v);
        return p;
    }
    Node *find(Node *p, T v) const {
        if (p == nullptr) return nullptr;
        if (v == p->val) return p;
        if (v < p->val) return find(p->left, v);
        return find(p->right, v);
    }
    Node *erase(Node *p, T v) {
        if (p == nullptr) return nullptr;
        if (v == p->val) {
            if (p->cnt > 1) {
                --p->cnt;
                return p;
            }
            if (p->left == nullptr) {
                Node *r = p->right;
                delete p;
                return r;
            }
            if (p->right == nullptr) {
                Node *l = p->left;
                delete p;
                return l;
            }
            Node *t = p->right;
            while (t->left != nullptr) t = t->left;
            p->val = t->val;
            p->cnt = t->cnt;
            p->right = erase(p->right, t->val);
            return p;
        }
        if (v < p->val) p->left = erase(p->left, v);
        else p->right = erase(p->right, v);
        return p;
    }
    void inorder(Node *p, vector<T> &v) const {
        if (p == nullptr) return;
        inorder(p->left, v);
        for (int i = 0;i < p->cnt;++i) v.push_back(p->val);
        inorder(p->right, v);
    }
public:
    multiset() : root(nullptr), size(0) {}
    ~multiset() { clear(root); }
    void insert(T v) { root = insert(root, v); ++size; }
    void erase(T v) { root = erase(root, v); --size; }
    int count(T v) const { Node *p = find(root, v); return p == nullptr ? 0 : p->cnt; }
    bool empty() const { return size == 0; }
    int size() const { return size; }
    vector<T> inorder() const { vector<T> v; inorder(root, v); return v; }
};

#endif // MULTISET_H

