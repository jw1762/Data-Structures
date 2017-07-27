//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     dynamic array whose size is stored in member variable
//     capacity; the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[capacity - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.
//
// DOCUMENTATION for private member (helper) function:
//   void resize(int new_capacity)
//     Pre:  (none)
//           Note: Recall that one of the things a constructor
//                 has to do is to make sure that the object
//                 created BEGINS to be consistent with the
//                 class invariant. Thus, resize() should not
//                 be used within constructors unless it is at
//                 a point where the class invariant has already
//                 been made to hold true.
//     Post: The capacity (size of the dynamic array) of the
//           invoking IntSet is changed to new_capacity...
//           ...EXCEPT when new_capacity would not allow the
//           invoking IntSet to preserve current contents (i.e.,
//           value for new_capacity is invalid or too low for the
//           IntSet to represent the existing collection),...
//           ...IN WHICH CASE the capacity of the invoking IntSet
//           is set to "the minimum that is needed" (which is the
//           same as "exactly what is needed") to preserve current
//           contents...
//           ...BUT if "exactly what is needed" is 0 (i.e. existing
//           collection is empty) then the capacity should be
//           further adjusted to 1 or DEFAULT_CAPACITY (since we
//           don't want to request dynamic arrays of size 0).
//           The collection represented by the invoking IntSet
//           remains unchanged.
//           If reallocation of dynamic array is unsuccessful, an
//           error message to the effect is displayed and the
//           program unconditionally terminated.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void IntSet::resize(int new_capacity)
{
   if (new_capacity < used) //Checks if given value is less
   {
      new_capacity = used;  //than current utilized size.
   }

   if (new_capacity < 1)    //Ensures no negatives or no
   {
      new_capacity = 1;     //size (0) ojbects are made.
   }

   capacity = new_capacity;
   int *newData = new int[capacity]; //Creates new pointer and 
   for (int i =0; i < used; i++)     //points to new object array.
   {
     newData[i] = data[i];          //Copies contents.
   }
   delete [] data;              //Deletes old stuff.
   data = newData;              //New, resized array.
}

IntSet::IntSet(int initial_capacity)
   :used(0), capacity(initial_capacity)
//Used is assigned 0, capacity set to initial.
{
   if (capacity < 1)
   {    
      capacity = DEFAULT_CAPACITY;
   }
   data = new int[capacity]; //Data pointed to new
                             //array object.
}

IntSet::IntSet(const IntSet& src)
   :capacity(src.capacity), used(src.used)
 //First, capacity is assigned the source object capacity.
 //Used is then assigned the source object used.
{
   data = new int[capacity];      //Data is pointed to new array
                                  //object of size capacity.
   for (int i = 0; i < used; i++) 
   { 
      data[i] = src.data[i];      //Contents are the copied.
   }
}


IntSet::~IntSet()
{
   delete [] data;
}

IntSet& IntSet::operator=(const IntSet& rhs)
{
   if (this != &rhs)
   {
      int* newData = new int[rhs.capacity];
      for (int i = 0; i < rhs.used; i++)
      {
         newData[i] = rhs.data[i];
      }
      delete [] data;
      data = newData;
      capacity = rhs.capacity;
      used = rhs.used;
   }
   return *this;
}

int IntSet::size() const
{
   return used; //Returns number of elements in current set.
}

bool IntSet::isEmpty() const
{
   if (used == 0)
      return true;
   else
      return false;
}

bool IntSet::contains(int anInt) const
{
   bool check = false;

   //Checking if anInt is contained anywhere within the set.
   for (int cIndex = 0; cIndex < used; cIndex++)
   {
      if (data[cIndex] == anInt)
         check = true;
   }
   return check;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   int setCounter = 0; //To later check if == to used.

   //If an empty set, true is returned as per definiton.
   if (used == 0)
   {
      return true;
   }

   //Counting number of elements between sets.
   for (int subsetIndex = 0; subsetIndex < used; subsetIndex++)
   {
      for (int otherIndex = 0; otherIndex < otherIntSet.used; otherIndex++)
      {
         if (data[subsetIndex] == otherIntSet.data[otherIndex])
         {
            setCounter++;
         }
      }
   }

   //Returns true if otherIntSet has same number of elements.
   if (setCounter == used)
      return true;
   else
      return false;
}

void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
   IntSet unionSet = *this;
   
   for (int i = 0; i < otherIntSet.used; i++)
   {
      if(unionSet.contains(otherIntSet.data[i]) == false)
         unionSet.add(otherIntSet.data[i]);
   }
   return unionSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   IntSet newIntSet; //A new IntSet to represent the Intersect of the other two.

   //Looks for matching elements between sets and adds to new set if found.
   for (int x = 0; x < used; x++)
   {
      for (int y = 0; y < otherIntSet.used; y++)
      {
         if (otherIntSet.data[y] == data[x])
         {
            newIntSet.add(data[x]);
            break;
         }
      }
   }
   return newIntSet;// Return the new Intersected set of Ints.
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
   IntSet newSubIntSet;
   bool matchFlag;

   for (int subIndex = 0; subIndex < used; subIndex++)
   {
      matchFlag = false;

      for (int otherIndex = 0; otherIndex < otherIntSet.used; otherIndex++)
      {
         if (data[subIndex] == otherIntSet.data[otherIndex])
         {
            matchFlag = true;
         }
      }

      if (matchFlag == false)
      {
         newSubIntSet.data[newSubIntSet.used] = data[subIndex];
         newSubIntSet.used++;
      }
   }
   return newSubIntSet;
}

void IntSet::reset()
{
   used = 0;
}

bool IntSet::add(int anInt)
{

   if (used == capacity) //If Array is full, nothing added. Preventing Out of Bounds.
   {
      return false;
   }

   if (contains(anInt) == false)
   {
      resize(int (1.5*capacity) + 1);
      data[used] = anInt;
      used++;
      return true;
   }

   return false;
}

bool IntSet::remove(int anInt)
{
   if (contains(anInt) == true)
   {
      for (int rIndex = 0; rIndex < used; rIndex++)
      {
         if (data[rIndex] == anInt)
         {
            for (int k = rIndex; k < used; k++)
            {
                  data[k] = data[k+1]; //Moves all elements to left. 
            }
            used--;
         }
      }
   return true;
   }
return false;
}

bool operator==(const IntSet& is1, const IntSet& is2)
{
   int is1Used = is1.size();
   if (is1Used != is2.size()) return false;
   for (int i = 0; i < is1Used; i++)
      if (is1.isSubsetOf(is2) == false ) return false;
   return true;
}

