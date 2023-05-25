#ifndef MYSTRING_H_
#define MYSTRING_H_
#include<string>
namespace mystring{
    //0相等，1表示a>b,-1表示a<b
    typedef std::string string;
    int cmp(const string& a,const string& b){
        int lena=a.length();
        int lenb=b.length();
        if(lena<lenb){
            return -1;
        }
        else if(lenb < lena){
            return 1;
        }
        else{
            for(int i=0;i<lena;i++){
                if(a[i]<b[i]){
                    return -1;
                }
                else if(a[i]>b[i]){
                    return 1;
                }
            }
            return 0;
        }
    }
}
#endif