//Jordan C. Williamson Copyright 2017
//
#include <cstdlib> 
#include <iostream>
#include "LinkedList.h"
using namespace jcw; //my Namespace

LinkedList::LinkedList()
{
  head = NULL;
}

LinkedList::~LinkedList()
{
  
}

void LinkedList::display()
{
	ptr = head;
	while (ptr)
	{
		std::cout << ptr->value << endl;
		ptr = ptr->next;
	}
}

int LinkedList::size() //returns number of data elements in list
{
	size = 0;
	ptr = head;
	while (ptr)
	{
		size++;
		ptr = ptr->next;				
	}
	return size;
} 
 
bool LinkedList::empty() //bool returns true if empty
{
	if(!head)
	{
		return true;
	}
	else
		return false;
} 
 
value_at(index) //returns the value of the nth item (starting at 0 for first)
{
	int i = 0;
	ptr = head;
	while (ptr)
	{
		if (index == i)
		{
			return value;
		}
		ptr = ptr->next;
		i++;
	}
}
 
push_front(value) //adds an item to the front of the list
{
		
} 
 
pop_front()//remove front item and return its value
{
	
} 
 
push_back(value) //adds an item at the end
{
	
} 
 
pop_back(){} //removes end item and returns its value
 
front(){} //get value of front item
 
back(){} //get value of end item
 
insert(index, value){} //insert value at index, so current item at that index is pointed to by new item at index
 
erase(index){} //removes node at given index
 
value_n_from_end(n){} //returns the value of the node at nth position from the end of the list
 
reverse(){} //reverses the list
 
remove_value(value){} //removes the first item in the list with this value
