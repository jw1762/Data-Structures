/************************
CS 3358-254
Assignment 7
Author: Jordan Williamson
*************************/
#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

//write definition for bst_insert here
bool bst_insert(btNode*& root, int insert)
{ 
  if (root == 0)
  {
    root = new btNode;
    root->data = insert;
    root->left = 0;
    root->right = 0;
    return true;
  }
  if (root->data == insert)
    return false;

  btNode *cursor = root;
  bool complete = false;

  while (!complete)
  {
    if (insert < cursor->data)
    {
      if(cursor->left == 0)
      {
        cursor->left = new btNode;
        cursor->left->data = insert;
        cursor->left->left = 0;
        cursor->left->right = 0;
        complete = true;
      }
      else
      {
        cursor = cursor->left;
      }
    }
    else if (insert > cursor->data)
    {
      if(cursor->right == 0)
      {
        cursor->right = new btNode;
        cursor->right->data = insert;
        cursor->right->left = 0;
        cursor->right->right = 0;
        complete = true;
      }
      else
      {
        cursor = cursor->right;
      }
    }
    else
      return false;
   
  }
  return complete;  
}      

// write definition for bst_remove here
bool bst_remove(btNode* &root, int rmInt)
{
  if (root == 0)
    return false;
  
  if (rmInt < root->data)
  {
    return bst_remove(root->left, rmInt);
  }
  else if (rmInt > root->data)
  {
    return bst_remove(root->right, rmInt);
  }
  else if (rmInt == root->data)
  {
    if (root->left == 0 && root->right == 0)
    {
      btNode* oldRoot = root;
      root = 0;
      delete oldRoot;
      
    }
    else if (root->left == 0 || root->right == 0)
    {
      if (root->right == 0)
      {
        btNode* oldRoot = root;
        root = root->left;
        delete oldRoot;
        
      }
      else
      {
        btNode* oldRoot = root;
        root = root->right;
        delete oldRoot;  
      }
     }
    else
    {
       bst_remove_max(root->left, root->data);
    }
    
   }
  return true;
}

// write definition for bst_remove_max here
void bst_remove_max(btNode* &root, int &removed)
{
  if (root->right == 0)
  {
    removed = root->data;
    btNode* oldRoot = root;
    root = root->left;
    delete oldRoot;
  }
  else
  {
    bst_remove_max(root->right, removed);
  }
}
