//
//  main.cpp
//  04071913024_MuhammadWahab_P1
//
//  Created by Ch Muhammad Wahab on 06/12/2020.
//  Copyright © 2020 Ch Muhammad Wahab. All rights reserved.
//

#include <iostream>
#include<fstream>
#include<stack>
using namespace std;
int i=0;
class mobile{
    int ram,rom,battery;
public:
    mobile(){
        ram=0;
        rom=0;
        battery=0;
    }
    mobile(const mobile &obj){
        ram=obj.ram;
        rom=obj.rom;
        battery=obj.battery;
    }
    friend istream& operator>>(istream& in,mobile&m){
        if (i++>=0) {
            cin.ignore();
        }
        //  m.name=m.model="iphone";
        m.rom=m.ram=m.battery=10;
        return in;
    }
    friend ostream& operator<<(ostream& out,mobile&m){
        out<<"Ram: "<<m.ram<<"GB"<<endl;
        out<<"Rom: "<<m.rom<<"GB"<<endl;
        out<<"Battery: "<<m.battery<<"mAH"<<endl;
        return out;
    }
    bool operator ==(mobile m){
        return (ram==m.ram && rom==m.rom && battery==m.battery);
    }
};
template <class t>
class list;
template <class t>
struct node {
    t data;
    node<t> *next;
    node<t> *prev;
    node(){};
    //parameterized constructor to inialize at declaration time
    node(node<t> *p,const t &val,node<t> *n){
        data=val;
        next=n;
        prev=p;
    }
};
template <typename t>
class list{
    node<t> *head,*tail;
public:
    //default constructor
    list(){
        head=tail=NULL;
    }
    //copy constructor
    //O(n)
    list(const list &obj){
        head=tail=NULL;
        operator=(obj);
    }
    //overloaded assignment operator =
    //O(n)
    void operator=(const list &obj){
        make_empty();
        node<t>*temp=obj.head;
        while(temp!=NULL){
            push_back(temp->data);
            temp=temp->next;
        }
    }
    //destructor
    //O(n2)
    ~list(){
        make_empty();
    }
    //this function make list empty
    //O(n2)
    void make_empty(){
        while (!empty()) {
            popfront();
        }
    }
    //function to check whether the list is empty or not
    //O(1)
    bool empty(){
        return head==NULL;
    }
    //function to check heap memory limitaion
    //O(1)
    bool full(){
        node<t> *memory;
        memory=new node<t>;
        if(memory)
            return false;
        else
            return true;
    }
    //push_back function to insert value at the start of the list
    //O(1)
    void push_front(const t& val){
        if(full())
            throw "Memory Full! \n";
        node<t>*input;
        if(head==NULL){
            input=new node<t>(NULL,val,NULL);
            head=tail=input;
        }
        else{
        node<t>*input=new node<t>(NULL,val,head);
        head->prev=input;
        head=input;
        }
    }
    //push_back function to insert value at the end of the list
    //O(1)
    void push_back(const t& val){
        if(full())
            throw "Memory Full! \n";
        node<t>*input;
        if(head==NULL){
            input=new node<t>(NULL,val,NULL);
            head=tail=input;
        }
        else{
        node<t>*input=new node<t>(tail,val,NULL);
        tail->next=input;
        tail=input;
        }
    }
    //insert funtion to insert values in unsorted order
    //O(1)
    void insertunsorted(const t& val){
        node<t> *input;
        if(head==NULL){
            input=new node<t>(NULL,val,NULL);
            head=tail=input;
        }
        else{
            input=new node<t>(tail,val,NULL);
            tail->next=input;
            tail=input;
        }
    }
    //insert funtion to insert values in sorted order
    //worse case O(n4)
    //best case O(n3)
    void insertsorted(const t&val){
        node<t> *input;
        if(head==NULL){
            input=new node<t>(NULL,val,NULL);
            head=tail=input;
        }
        else{
            node<t>*temp=head;
            if(val < head->data){
                push_front(val);
            }
            else if(val>tail->data){
                push_back(val);
            }
            else{
            while(temp->next!=NULL){
                if(val < temp->next->data)
                    break;
                temp=temp->next;
            }
            input=new node<t>(temp,val,temp->next);
            temp->next=input;
            }
        }
    }
    //sort function for list
    //O(n^2)
     void sort(){
        node<t>*cur=head;
        if(head==NULL)
            throw "NULL \n";
        while(cur!=NULL){
            node<t>*hold=cur;
            while(cur->next!=NULL){
                if(hold->data > cur->next->data){
                    t s=hold->data;
                    hold->data=cur->next->data;
                    cur->next->data=s;
                }
                cur=cur->next;
            }
            cur=hold->next;
        }
    }
    //this function will return pointer to first/beginning node for iterator
    //O(1)
    node<t>* begin() const{
        return head;
    }
    //this function will allocate new memory, whose value will be = to tail->data
    //tail->next part will point to this new allocated memory
    //this function is kept align with STD function end()
    //O(1)
    node<t>* end() {
        node<t> *pointer=new node<t>(tail,tail->data,NULL);
        tail->next=pointer;
        return pointer;
    }
    //front function will return frist-node data
    //O(1)
    t front(){
        return head->data;
    }
    //poptail to remove the last node
    //O(1)
    void poptail(){
        if(tail!=NULL){
        node<t>*temp=tail;
        tail=tail->prev;
        tail->next=NULL;
        delete temp;
        }
    }
    //pophead to remove the first node
    //O(1)
    void popfront(){
        node<t>*temp=head;
        head=head->next;
        if(head==NULL){
            tail=NULL;
        }
        else{
        head->prev=NULL;
        }
        delete temp;
    }    //find function to find element
    //O(n)
    //O(1) for front element
    bool find(t& val) const {
        node<t>* temp;
        temp = head;
        while(temp!=NULL){
            if (temp->data == val){
                val=temp->data;
                return true;
            }
            temp=temp->next;
        }
        return false;
    }
    // return the node_address for given value
    //O(n)
    //O(1) for front node (head->next)
    node<t>* find_ptr(const t& val) {
        node<t>* temp;
        temp = head;
        while(temp!=NULL){
            if (temp->data == val)
                return temp;
            temp=temp->next;
        }
        return NULL;
    }
    //update function to update value
    //O(n)
    bool update(const t& old_val, const t& new_val) {
        node<t>* temp;
        temp = find_ptr(old_val);
        if (temp != NULL) {
            temp->data = new_val;
            return true;
        }
        else
            return false;
    }
    //erase function will take a pointer node(iterator/begin()/end()) and delete that pointer
    //best case O(1)
    //worsse case O(n)
    void erase(const node<t>* pointer) {
        node<t>*temp=head;
        if(head==NULL || tail==NULL)
        {
            cout<<"List empty";
        }
        else if(head->data==pointer->data){
            node<t>*to_del=head;
            head=head->next;
            head->prev=head->prev->prev;
            delete to_del;
        }
        else if(tail->data==pointer->data){
            node<t>* temp=tail;
            tail=tail->prev;
            tail->next=NULL;
            delete temp;
        }
        else{
        while(temp->next!=NULL){
            if(temp->next->data==pointer->data)
            {
                node<t>*to_del=temp->next;
                temp->next=to_del->next;
                temp=temp->next;
                temp->prev=to_del->prev;
                delete to_del;
                break;
            }
            temp=temp->next;
        }
      }
    }
   
    //display the list from start/begin/head
    //O(n)
    void displayfromhead(){
        node<t> *displayer=head;
        while(displayer!=NULL){
            cout<<displayer->data<<" ";
            displayer=displayer->next;
        }
    }
    //display the list from last/end/tail
    //O(n)
    void displayfromtail(){
        node<t> *displayer=tail;
        while(displayer!=NULL){
            cout<<displayer->data<<" ";
            displayer=displayer->prev;
        }
    }
    //reverse function will reverse the link
    //
    void reverse(){
        stack<t> s;
        list<t>::iterator itr=begin();
        while(itr!=end())
        {
            s.push(*itr);
            itr++;
        }
        make_empty();
        while(!s.empty()){
            push_back(s.top());
            s.pop();
        }
    }
    //custom iterator
    //same functionalities like STL iterator
    class iterator{
        node<t> *itr;
    public:
        //default and parameterized constructor
        //O(1)
        iterator(node<t> *pointer=NULL){
            itr=pointer;
        }
        //overloaded assignmnet operator =
        //O(1)
        void operator = (node<t> *&pointer){
            itr=pointer;
        }
        //overloaded insertion opertaor <<
        //O(1)
        friend ostream& operator<<(ostream& out,const iterator obj){
            cout<<obj.itr->data;
            return out;
        }
        //overloaded pre-increment opertaor ++
        //O(1)
        void operator++(){
            itr=itr->next;
        }
        //overloaded post-increment opertaor ++
        //O(1)
        void operator++(int){
            itr=itr->next;
        }
        //overloaded pre-decrement opertaor --
        //O(1)
        void operator--(){
            itr=itr->prev;
        }
        //overloaded post-increment opertaor --
        //O(1)
        void operator--(int){
            itr=itr->prev;
        }
        //overloaded not-equal-to opertaor !=
        //O(1)
        bool operator !=(node<t> *pointer){
            return  (itr->prev!=pointer->prev && itr->next!=pointer->next);
        }
        //overloaded dereference * operator
        //O(1)
        t& operator*(){
            return itr->data;
        }
        //function to return pointer
        //O(1)
        node<t>* Itr() const{
            return itr;
        }
    };
    void erase(list<t>::iterator &itr) {
        t pointer=*itr;
        node<t>*temp=head;
        if(head==NULL || tail==NULL)
        {
            cout<<"List empty";
        }
        else if(head->data==pointer){
            node<t>*to_del=head;
            head=head->next;
            head->prev=head->prev->prev;
            delete to_del;
        }
        else if(tail->data==pointer){
            node<t>* temp=tail;
            tail=tail->prev;
            tail->next=NULL;
            delete temp;
        }
        else{
            while(temp->next!=NULL){
                if(temp->next->data==pointer)
                {
                    node<t>*to_del=temp->next;
                    temp->next=to_del->next;
                    temp=temp->next;
                    temp->prev=to_del->prev;
                    delete to_del;
                    break;
                }
                temp=temp->next;
            }
        }
    }
};

int main(int argc, const char * argv[]) {
    
    list<int> l;
//    mobile m;
//    cin>>m;
//    l.push_back(m);
//    l.push_back(m);
//    l.push_back(m);
    l.push_back(1);
    l.push_back(3);
    l.push_back(2);
    l.push_back(0);
    l.push_back(8);
    l.push_back(7);
    l.push_back(5);
    l.push_back(4);
    l.push_back(6);
    int val=6;
    if(l.find(val))
        cout<<val<<" Element found!\n";
    else
        cout<<val<<" Element not found!\n";
    l.update(1,2);               //after this list will be like 0 2 2 3 4 5 6 7 8
    l.sort();                    //after this list will be like 0 2 2 3 4 5 6 7 8
    l.erase(l.end());            //after this list will be like 0 2 2 3 4 5 6 7
    l.poptail();                 //after this list will be like 0 2 2 3 4 5 6
    l.erase(l.begin());          //after this list will be like 2 2 3 4 5 6
    list<int>::iterator itr;
    itr=l.begin();               //first/begining element
    itr++;                       //2nd element
    itr++;                       //3rd element
    l.erase(itr);          //after this list will be like 2 2 4 5 6
    itr=l.begin();               //begining element
    while(itr!=l.end()){
        cout<<*itr<<" ";
        itr++;
    }cout<<endl;
    l.reverse();
    itr=l.begin();               //begining element
    while(itr!=l.end()){         //list after reverse
        cout<<*itr<<" ";
        itr++;
    }
    
}
