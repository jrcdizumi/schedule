#include"hashmap.h"
int main(){
    HashMap<int> map{10};
    map.insert("a", 1);
    map.insert("b", 2);
    map.insert("c", 3);
    map.insert("d", 4);
    map.insert("e", 5);
    map.insert("f", 6);
    map.insert("g", 7);
    map.insert("h", 8);
    map.insert("i", 9);
    map.insert("j", 10);
    map.insert("k", 11);
    map.insert("l", 12);
    map.insert("m", 13);
    map.insert("n", 14);
    map.insert("o", 15);
    map.insert("p", 16);
    map.insert("q", 17);
    map.insert("r", 18);
    map.insert("s", 19);
    map.insert("t", 20);
    map.insert("u", 21);
    map.insert("v", 22);
    map.insert("w", 23);
    map.insert("x", 24);
    map.insert("y", 25);
    map.insert("z", 26);
    map.print();
    cout<<map.get("1")<<endl;
    return 0;
}