#include<iostream>
#include"../func/vector.h"
using namespace std;

int main()
{
    Vector<int*> v;
    int b[3]={1,2,3};
    v.push_back(&b[0]);
    v.push_back(&b[1]);
    v.push_back(&b[2]);
    cout<<*v[0]<<endl;
    b[0]=5;
    cout<<*v[0]<<endl;
    v[0]=&b[1];
    cout<<*v[0]<<endl;
    *v[0]=6;
    cout<<b[1]<<endl;
    int* x;
    if(x==NULL)
        cout<<"NULL"<<endl;
    else
        cout<<"NOT NULL"<<endl;
    x=v[0];
    cout<<*x<<endl;
    return 0;
}