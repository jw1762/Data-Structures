// FILE: Sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).

#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_Sp2016
{
   // CONSTRUCTORS and DESTRUCTOR
   sequence::sequence(size_type initial_capacity)
      :used(0), capacity(DEFAULT_CAPACITY)
   {
      if (initial_capacity > 0)
      {
         initial_capacity = DEFAULT_CAPACITY;
      }
      else
         initial_capacity = 1;     //Initializes, assigns to default,
                                   //if negative number, sets to 1.
      data = new value_type[initial_capacity];//Creates array.
   }

   sequence::sequence(const sequence& source)
      :used(source.used), current_index(source.current_index),
       capacity(source.capacity)
   {
      data = new value_type[capacity]; //Creates a new array obj,
      for (size_type i = 0; i < used; i++)//Copies over all data 
      {                                   //to new obj.
         data[i] = source.data[i];
      }
   }

   sequence::~sequence()
   {
      delete [] data;//Deletes array.
   }

   // MODIFICATION MEMBER FUNCTIONS
   void sequence::resize(size_type new_capacity)
   {
      if (new_capacity <= used)
      {
         new_capacity = used;
         if (new_capacity <= 0)//Resizes to used if new size
         {                     //is smaller than current size.
            new_capacity = 1;  //If somehow negative, sets to 1.
         }
      }
      capacity = new_capacity;//Resizes to new larger size.
      value_type *newData = new value_type[capacity];
      for (size_type j = 0; j < used; j++)
      {
         newData[j] = data[j];//Assigns data to new obj.
      }
      delete [] data;//Deletes old data.
      data = newData;//Points to new obj.
   }

   void sequence::start()
   {
      current_index = 0;//Starts at beginning.
      if (used == 0)
      {
         current_index = used;
      }
   }

   void sequence::advance()
   {
      if (is_item() == true)
      {
         current_index++;//If an item exists, advance to next.
      }
      while (current_index == used)
      {        //If cursor goes beyond scope, ends advancement.
         break;
      }
      
   }

   void sequence::insert(const value_type& entry)
   {
      if (size() == capacity)//Resizes if at max capacity.
         resize(size_type (1.25 * capacity) + 1);

      if (is_item() == false)//Returns to beginning if 
      {                      //there is no current item.
         current_index = 0;
      }
      for (size_type j = used; j > current_index; j--)
      {                      //Shifts all elements to the right.
         data[j] = data[j-1];
      }
      data[current_index] = entry;//Now assigns at current after
      used++;                     //all elements have moved.
   }

   void sequence::attach(const value_type& entry)
   {
      if (size() == capacity)
         resize (size_type (1.25 * capacity) + 1);

      if (is_item() == false)
      {
         current_index = used - 1;
      }
      for (size_type k = used; k > current_index; k--)
      {   
         data[k] = data[k-1];//Shifts all to the left.
      }
      data[current_index + 1] = entry;
      used++;
      current_index++;
   }

   void sequence::remove_current()
   {
      if (is_item() == true)
      {
         for (size_type k = current_index; k < used; k++)
         {
            data[k] = data[k+1];//Shifts all elements to the left
         }                      //after removal.
         used--;
      }
   }

   sequence& sequence::operator=(const sequence& source)
   {
      if (this != &source)
      {
         value_type* newData = new value_type[source.capacity];
         for (size_type j = 0; j < source.used; j++)
         {
            newData[j] = source.data[j];
         }
         delete [] data;//Deletes old data,
         data = newData;//then assigns all
         used = source.used;//appropriate information.
         current_index = source.current_index;
         capacity = source.capacity;
      }
      return *this;
   }

   // CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
      return used; //Returns current number of used elements.   
   }

   bool sequence::is_item() const
   {
      if (current_index < used)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   sequence::value_type sequence::current() const
   {
      if (is_item() == true)
      {
         return data[current_index];
      }
      return data[current_index];
   }
}
