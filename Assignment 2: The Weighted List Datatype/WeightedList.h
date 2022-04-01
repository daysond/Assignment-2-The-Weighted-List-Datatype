//WeightedList.h - class definitions for a weighted list

#ifndef _WEIGHTEDLIST_H_
#define _WEIGHTEDLIST_H_

#include <iostream>

namespace asg {

template <typename T>

class WeightedList {
    //***** node ******
	struct Node {
		T data;
		Node* next;

		Node(const T& _data) {
			data = _data;
			next = nullptr;
		}
	};
    //***** node ******
    
	Node* front;
	int num;
    
public:
    //TODO: Complete the iterator class
    class iterator {
        
    protected:
        
        friend class WeightedList;
        Node *current;
        
    public:
        
        iterator(){
            current = nullptr;
        }
        
        iterator(Node* node){
            current = node;
        }
        
//      iterator operator++();. Advance the current element pointer. Return the current element.
        iterator operator++(){
            if(current->next)
                current = current->next;
            return *this;
        }

//        TODO: iterator operator++(int);. Return the current element but advance the current element pointer to the next element.
        iterator operator++(int value){
            if(current->next)
                current = current->next;
            return *this;
        }
        
//        bool operator==(iterator rhs);. Perform a logical comparison between the current element and the rhs element. Return true if they are the same.
        bool operator==(iterator rhs){
            return current->data == rhs.current.data;
        }
        
//        bool operator!=(iterator rhs);. Perform a logical comparison between the current element and the rhs element. Return true if they are different.
        bool operator!=(iterator rhs){
            return current->data != rhs.current->data;
        }
//        T& operator*();. Returns a reference to the current element.
        T& operator*() {
            return current->data;
        }
        
    };

	//TODO: Complete the weighted list functionality.
	//      You can put your function declarations or prototypes here
	//      and function definitions or implementations below
//
//    WeightedList();. A default constructor for the list. Need to initialize the front and counter variables.
    WeightedList(){
        front = nullptr;
        num = 0;
    }
    
//    WeightedList(const WeightedList& rhs);. A copy constructor for the list. Copy node by node from rhs.
    WeightedList(const WeightedList& rhs){
        *this = rhs;
    }
    
//    WeightedList& operator=(const WeightedList& rhs);. A copy assignment for the list. Delete the current list and copy node by node from rhs.
    WeightedList& operator=(const WeightedList& rhs){
        num = rhs.num;
        
        return *this;
    }
//    WeightedList(WeightedList&& rhs);. A move constructor for the list. Set the front variable to the front variable of rhs. Then set the front variable of the rhs to nullptr. Copy the data element counter from the rhs then set the data element counter of the rhs to zero. The rhs is effectively an empty list.
    WeightedList(WeightedList&& rhs){
        
        
    }
    
    
//    WeightedList& operator=(WeightedList&& rhs);. A move assignment for the list. Delete the current list then set the front variable to the front variable of rhs. Then set the front variable of the rhs to nullptr. Copy the data element counter from the rhs then set the data element counter of the rhs to zero. The rhs is effectively an empty list.
    WeightedList& operator=(WeightedList&& rhs){
        
        return this;
    }
    
//    iterator begin();. Return an iterator to the beginning of the list. Return the data element pointed to by the front pointer.
    iterator begin(){
        
        return iterator();
    }
//    iterator end();. Return an iterator to the end of the list. The last element of the list is actually nullptr by convention.
    iterator end(){
        
        return iterator();
    }
//    void push_back(const T& data);. Push data of type T to the end of the list. This means starting from the front of the list, traversing all the way through to the end, then inserting your data element there.
    void push_back(const T& data){
        
        
        
    }
//    iterator search(const T& data);. Search for an item with value data. Return the iterator to this item. If the data element is found, it is moved up by one space in the list. To do this you might have to have a pointer to the current element, the element before it, and the element before that one.
    iterator search(const T& data){
        
        return iterator();
    }
//    iterator erase(iterator it);. Erase a data item. Return the iterator to the next item. To do this you might have to have a pointer to the current element and the one before it.
    iterator erase(iterator it){
        
        
        return iterator();
    }
//    iterator erase(iterator begin, iterator end);. Erase a range of data items from begin to end excluding end. Return an iterator to end. To do this you might have to have a pointer to the first element, a pointer to the element before it, and a pointer to the last element.
    iterator erase(iterator begin, iterator end){
        
        return iterator();
    }
    
//    bool empty() const;. Return true if the list is empty, false otherwise. If you have a variable that keeps track of the number of data elements, you can simply return true if this counter is zero, false otherwise.
    bool empty() const{
        
        
        return true;
    }
//    int size() const;. Return the number of data items in the list. If you have a counter that keeps track of the number of data elements, you can simply return the value of this number.
    int size() const{
        
        return 0;
    }
//    ~WeightedList();. A destructor for the weighted list. Be sure to delete all the data elements in the list.
    ~WeightedList() {
        
        
    }
    
};

}

#endif// _WEIGHTEDLIST_H_
