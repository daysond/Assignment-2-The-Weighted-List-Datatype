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
    Node* front = nullptr;
    int num = 0;
    
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
        
        bool operator==(const iterator& rhs){ return current == rhs.current; }
        
        bool operator!=(const iterator& rhs){ return current != rhs.current; }
      
        T& operator*() { return current->data; }
        
    };
    
    
    // MARK: - WeightedList methods
    
    WeightedList() {}
    
    WeightedList(const WeightedList& rhs){
        *this = rhs;
    }
    
    WeightedList& operator=(const WeightedList& rhs){
        if(this != &rhs && rhs.front) {
            num = rhs.num;
            deleteNodes();
            copyNode(rhs.front, front);
        }
        return *this;
    }
    
    WeightedList(WeightedList&& rhs){
        *this = std::move(rhs);
    }
    
    
    WeightedList& operator=(WeightedList&& rhs){
        
        if(this != &rhs) {
            
            deleteNodes();
            
            num = rhs.num;
            front = rhs.front;
            rhs.front = nullptr;
            rhs.num = 0;
        }

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
            
            current->next = new Node(data);
        }
        
        ++num;
    }
    
    iterator search(const T& data){
        
        Node *retNode = nullptr;
        Node* current = front;
        Node* previous = nullptr;
        Node* secondPrevious = nullptr;
        
        //Find target node
        while (current && current->data != data) {
            secondPrevious = previous;
            previous = current;
            current = current->next;
        }
        
        //Swap nodes
        if(current)
            retNode = advanceTargetNode(secondPrevious, previous, current);
        
        return iterator(retNode);
    }
    

    iterator erase(iterator it){
        
        Node* retNode = nullptr;
        Node* current = front;
        Node* previous = nullptr;
        
        if (front->data == *it) {
            //first node is the one to be erased
            retNode = front->next;
            front = front->next;
            
        } else {
    
             do {
                previous = current;
                current = current->next;
             } while (current->data != *it);
            
            retNode = current->next;
            previous->next = retNode;
            
        }
        
        delete current;
        current =  nullptr;
        --num;
        
        return iterator(retNode);
        
    }
    
    
    iterator erase(iterator begin, iterator end){
        
        Node* retNode = nullptr;
        Node* current = front;
        Node* previous = nullptr;
        
        auto deleteNode = [&](Node* &node){
            retNode = node->next;
            delete current;
            node = retNode;
            --num;
        };
        
        //find the begin node
        while(current->data != *begin) {
            previous = current;
            current = current->next;
        }
        
        //Mark: - Approach One: use iterator
        
        while (iterator(current) != end)
            deleteNode(current);
        
        //Mark: - Approach Two: use if-else
        
//        if(end == iterator())
//            while (current != nullptr)
//                deleteNode(current);
//
//        else
//            while (current->data != *end)
//                deleteNode(current);
        
        // - End
        
        //previous will be null if deleting from the beginning
        previous ?  previous->next = retNode
        : front = retNode; //set front to retNode if deleting from the beginning
        
        return iterator(retNode);
        
    }
    
    
    bool empty() const{ return num == 0;}
    
    int size() const{ return num; }
    
    ~WeightedList() { deleteNodes();  }
    
private:
    
    //Helper functions
    
    Node* advanceTargetNode(Node* &sp, Node* &p, Node* &c) {
        //sp: second previous, p: previous, c: current
        Node *retNode = nullptr;
        
        if (p == nullptr) { //target is front
            retNode = front;
            
        } else if(sp == nullptr) { //target is front->next
            sp = front->next; //secondPre acting as a temp node
            front->next = sp->next;
            sp->next = front;
            front = sp;
            retNode = front->next;
            
        } else {
            sp->next = c;
            p->next = c->next;
            c->next = p;
            retNode = c;
 
        }
        
        return  retNode;
    }
    
    void copyNode(WeightedList<T>::Node* src, WeightedList<T>::Node* &dest) {
        
        //base
        if(src->next == nullptr)
            dest = new Node(src->data);
        
        else if(dest == nullptr) {
            dest = new Node(src->data);
            copyNode(src->next, dest->next);
        }
    }
    
    void deleteNodes() {
        
        Node* temp;
        
        while(front) {
            temp = front->next;
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
 
 this would not work. When the iterator is passed into the erase method, say, the iterator pointing to the front node, after erase is implemented, the current pointer is deleted and set to null. Internally, calling ++e advances the pointer by assigning the next node of current to current, yet current has been set to nullptr and current->next will not be accessbile. Thus this would not work.
 
 
 Would the following work? Why or why not? (0.5 mark)
 for (auto e = wList.begin(); e != wList.end(); ) {
 e = wList.erase(e);
 }
 
 erase returns the next node, which advances the iterator.
 
 
 
 Compare the weighted list with STL's list. What pointers and functionality appear in STL's list that are missing in our weighted list? (0.5 mark)
 
 Pointer: pointer to the back
 
 Funtionality: push_front, pop_front, pop (front or back), insert, swap, splice, remove_if etc
 
 
 The program WeightedListMainTimer.cpp was created to run in Linux (where there are higher resolution timers) to see if the search algorithm actually improves itself over time. See the bottom 1/4 of the file for the test code. A weighted list was created with 10,000 elements and an element with data=6 was inserted at the end. The program performed a number of searches, with a search for data=6 every third search, to simulate a situation where data=6 starts in the worst case (at the back) but is searched for frequently. The time elapsed for each search for data=6 is recorded. Take a look at the data in the file searchTime.dat. On the left is the number of the search attempt and on the right is the time elapsed in nanoseconds. You can see a graph of search time vs number of searches below. What will you report to the company executives - did this search algorithm "learn"? Did it learn well enough to pursue applying this algorithm to other data types? If not, how would you improve this algorithm? (0.5 mark)
 
 
 */
