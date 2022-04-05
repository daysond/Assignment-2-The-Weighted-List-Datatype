//WeightedList.h - class definitions for a weighted list

#ifndef _WEIGHTEDLIST_H_
#define _WEIGHTEDLIST_H_

#include <iostream>

namespace asg {

template <typename T>

class WeightedList {
    
    // MARK: - Node struct
    struct Node {
        T data;
        Node* next;
        
        Node(const T& _data) {
            data = _data;
            next = nullptr;
        }
    };
    
    // MARK: - Member variables
    Node* front;
    int num;
    
public:
    
    // MARK: - Iterator class
    class iterator {
        
    protected:
        friend class WeightedList;
        Node *current;
        
    public:
        
        iterator(){ current = nullptr;  }
        
        iterator(Node* node){ current = node; }
        
        iterator& operator++(){  // prefix
            if(current) current = current->next;
            return *this;
        }
        
        iterator operator++(int value){ //postfix
            iterator copy = *this;
            if(current) current = current->next;
            return copy;
        }
        
        //        bool operator==(iterator rhs);. Perform a logical comparison between the current element and the rhs element. Return true if they are the same.
        bool operator==(const iterator& rhs){ return current == rhs.current; }
        
        //        bool operator!=(iterator rhs);. Perform a logical comparison between the current element and the rhs element. Return true if they are different.
        bool operator!=(const iterator& rhs){ return current != rhs.current; }
        //        T& operator*();. Returns a reference to the current element.
        T& operator*() { return current->data; }
        
    };
    
    
    // MARK: - WeightedList methods
    
    WeightedList(): front(nullptr), num(0){}
    
    WeightedList(const WeightedList& rhs){
        front = nullptr;
        *this = rhs;
    }
    
    WeightedList& operator=(const WeightedList& rhs){
        
        num = rhs.num;
        deleteNodes();
        copyNode(rhs.front, front);
        
        return *this;
    }
    
    WeightedList(WeightedList&& rhs){
        front = nullptr;
        *this = std::move(rhs);
    }
    
    
    //    WeightedList& operator=(WeightedList&& rhs);. A move assignment for the list. Delete the current list then set the front variable to the front variable of rhs. Then set the front variable of the rhs to nullptr. Copy the data element counter from the rhs then set the data element counter of the rhs to zero. The rhs is effectively an empty list.
    WeightedList& operator=(WeightedList&& rhs){
        
        deleteNodes();
        
        num = rhs.num;
        front = rhs.front;
        rhs.front = nullptr;
        rhs.num = 0;
        return *this;
    }
    
    
    iterator begin(){ return iterator(front); }
    
    iterator end(){ return iterator(); }
    
    void push_back(const T& data) {
        
        if(!front)  front = new Node(data);
        
        else {
            
            Node* current = front;
            
            while (current->next)
                current = current->next;
            
            Node* temp = new Node(data);
            current->next = temp;
            
        }
        
        ++num;
    }
    
    iterator search(const T& data){
        
        Node *retNode = nullptr;
        Node* current = front;
        Node* previous = nullptr;
        Node* secondPre = nullptr;
        
        
        while (current && current->data != data) {
            //next node
            secondPre = previous;
            previous = current;
            current = current->next;
        }
        
        if(current) {
            //advance node
            if (previous == nullptr) { //target is front
                retNode = front;
                
            } else if(secondPre == nullptr) { //target is front->next
                secondPre = front->next;
                front->next = secondPre->next;
                secondPre->next = front;
                front = secondPre;
                retNode = front->next;
                
            } else {
                secondPre->next = current; //debug
                previous->next = current->next;
                current->next = previous;
                retNode = current;
     
            }
        }

        return iterator(retNode);
    }
    
    iterator erase(iterator it){
        
        Node* retNode = nullptr;
        
        if(!front)  throw std::out_of_range("Empty list");
        
        Node* current = front;
        Node* previous = nullptr;
        
        while (current->data != *it) {
            previous = current;
            current = current->next;
        }
        
        retNode = current->next;
        
        previous ? previous->next = current->next : front = retNode;
        
        delete current;
        current =  nullptr;
        
        --num;
        
        return iterator(retNode);
        
    }
    
    iterator erase(iterator begin, iterator end){
        
        if(!front)  throw std::out_of_range("Empty list");
        
        Node* retNode = nullptr;
        Node* current = front;
        Node* previous = nullptr;
        //find the begin node
        while(current->data != *begin) {
            previous = current;
            current = current->next;
        }
        
        //Deleting elements
        //while condition: if the last element needs to be erased, end condition: current is nullptr,
        //                 if the ending element is within range, check if the current pointer element is same as the end element
        while ((end == iterator()) ? current != nullptr
               : current && current->data != *end) {
            
            retNode = current->next;
            delete current;
            current = retNode;
            --num;
        }
        
        previous ? previous->next = retNode : front = retNode;
        
        return iterator(retNode);
        
    }
    
    
    bool empty() const{ return num == 0;}
    
    int size() const{ return num; }
    
    ~WeightedList() { deleteNodes();  }
    
private:
    //Helper functions
    void copyNode(WeightedList<T>::Node* src, WeightedList<T>::Node* &dest) {
        //base
        if(src->next == nullptr)
            dest = new Node(src->data);
        
        else if(dest == nullptr) {
            dest = new Node(src->data);
            copyNode(src->next, dest->next);
        }
    }
    
    void deleteNodes(Node* terminatingNode = nullptr) {
        
        while(front != terminatingNode) {
            Node* temp = front->next;
            delete front;
            front = temp;
        }
    }
    
};

}

#endif// _WEIGHTEDLIST_H_

/*
 Would the following work? Why or why not? (0.5 mark)
 for (auto e = wList.begin(); e != wList.end(); ++e) {
 wList.erase(e);
 }
 
 
 
 Would the following work? Why or why not? (0.5 mark)
 for (auto e = wList.begin(); e != wList.end(); ) {
 e = wList.erase(e);
 }
 
 
 Compare the weighted list with STL's list. What pointers and functionality appear in STL's list that are missing in our weighted list? (0.5 mark)
 
 
 
 The program WeightedListMainTimer.cpp was created to run in Linux (where there are higher resolution timers) to see if the search algorithm actually improves itself over time. See the bottom 1/4 of the file for the test code. A weighted list was created with 10,000 elements and an element with data=6 was inserted at the end. The program performed a number of searches, with a search for data=6 every third search, to simulate a situation where data=6 starts in the worst case (at the back) but is searched for frequently. The time elapsed for each search for data=6 is recorded. Take a look at the data in the file searchTime.dat. On the left is the number of the search attempt and on the right is the time elapsed in nanoseconds. You can see a graph of search time vs number of searches below. What will you report to the company executives - did this search algorithm "learn"? Did it learn well enough to pursue applying this algorithm to other data types? If not, how would you improve this algorithm? (0.5 mark)
 
 
 */
