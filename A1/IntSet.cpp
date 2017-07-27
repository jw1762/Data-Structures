// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
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
//     from data[used] through data[IntSet::MAX_SIZE - 1].
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

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

IntSet::IntSet()
{
   used = 0; //No current relevant elements, so we set to 0.   
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
   //Required Precondition
   assert (size() + (otherIntSet.subtract(*this)).size() <= MAX_SIZE);
   
   IntSet unionSet;

   //Inserting first set into the new set.
   for (int index1 = 0; index1 < used; index1++)
   {
      unionSet.data[index1] = data[index1];
      unionSet.used++;
   }
   
   //Adding the second set into the new set.
   for (int index2 = 0; index2 < otherIntSet.used; index2++)
   {
      unionSet.add(otherIntSet.data[index2]);
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
   //Required Precondition
   assert (contains(anInt) ? size() <= MAX_SIZE : size() < MAX_SIZE);
   
   if (used == MAX_SIZE) //If Array is full, nothing added. Preventing Out of Bounds.
   {
      return false;
   }

   if (contains(anInt) == false)
   {
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
            data[rIndex] = data[used-1]; //Replace integer with whichever is at the end of array.
            used--; //Now reduce count by 1, so no duplicate is made.
         }
      }
   }
   return false;
}

bool equal(const IntSet& is1, const IntSet& is2)
{
   //Empty set check.
   if (is1.size() == 0 && is2.size() == 0)
   {
      return true;
   }   
   
   if (is1.size() != is2.size())
   {
      return false;
   }

   if (is1.size() == is2.size())
   {
      return is1.isSubsetOf(is2);
   }

}

