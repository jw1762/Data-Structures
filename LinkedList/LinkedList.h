#ifndef LinkedList_H
#define LinkedList_H

class node
{
   public:
     //Constructor/Destructor
     Student(); 
     ~Student();
     
     //Methods
     void display(); //Outputs the list.
     int size(); //returns number of data elements in list
     bool empty(); - //bool returns true if empty
     int value_at(index); - //returns the value of the nth item (starting at 0 for first
     void push_front(value); - //adds an item to the front of the list
     int pop_front(); - //remove front item and return its value
     void push_back(value); -//adds an item at the end
     int pop_back(); - //removes end item and returns its value
     int front(); - //get value of front item
     int back(); - //get value of end item
     insert(index, value); - //insert value at index, so current item at that index is pointed to by new item at index
     int erase(index); - //removes node at given index
     int value_n_from_end(n); - //returns the value of the node at nth position from the end of the list
     void reverse(); - //reverses the list
     void remove_value(value); - //removes the first item in the list with this value
     
   private:
    int value;//stored data.
    node *next;//next node ptr
    node *head;//Head Ptr
};

#endif
