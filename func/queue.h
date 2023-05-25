#ifndef QUEUE_H
#define QUEUE_H
#include"vector.h"
namespace wh{ 

    template <typename T >
    class priority_queue{
        private:
            Vector<T> lis;
        public:
            T top(){
                return lis.front();
            }
            void swap(T &a,T &b){
                T temp=a;
                a=b;
                b=temp;
                return;
            }
            void push(T val){
                lis.push_back(val);
                int i=lis.getSize()-1;
                while(i>0){
                    if(lis[(i-1)/2] < lis[i]){
                        swap(lis[(i-1)/2],lis[i]);
                        i=(i-1)/2;
                    }
                    else
                        break;
                }
            }
            void pop(){
                swap(lis[0],lis[lis.getSize()-1]);
                lis.pop_back();
                int i=0;
                while(i*2+1<lis.getSize()){
                    int j=i*2+1;
                    if(j+1<lis.getSize()&&lis[j]<lis[j+1])
                        j++;
                    if(lis[i]<lis[j]){
                        swap(lis[i],lis[j]);
                        i=j;
                    }
                    else
                        break;
                }
            }
            bool empty(){
                return lis.getSize()==0;
            }

    };

    template <typename T>
    class queue{
        private:
            struct node{
                T val;
                node *next; 
                node *pre;
                node (T val){
                    this->val=val;
                    next=nullptr;
                    pre=nullptr;
                }
            };
            node *head;
            node *tail;
            int size;
        public:
            queue(){
                head=nullptr;
                tail=nullptr;
                size=0;
            }
            void push(T val){
                node *tmp=new node(val);
                if(size==0){
                    head=tmp;
                    tail=tmp;
                }
                else{
                    tail->next=tmp;
                    tmp->pre=tail;
                    tail=tmp;
                }
                size++;
            }
            void pop(){
                if(size==0)
                    return;
                node *tmp=head;
                head=head->next;
                delete tmp;
                size--;
            }
            T front(){
                return head->val;
            }
            T back(){
                return tail->val;
            }
            int getSize(){
                return size;
            }
            bool empty(){
                return size==0;
            }
    };
}

#endif