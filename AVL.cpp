#include "NodeInterface.h"
#include "Node.h"
#include "AVL.h"
using namespace std;

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * AVL::getRootNode() const
  {
    return root;
  }

	/*
	* Attempts to add the given int to the AVL tree
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool AVL::add(int data)
  {
    add_function(root, data);
  }

	bool AVL::add_function(Node*& n, int value)
  {
    if (n == NULL)
    {
		  n = new Node(value);
      return true;
    }

    if (n->data > value)
    {
      return add_function(n->leftChild, value);
    }

    if (n->data < value)
    {
      return add_function(n->rightChild, value);
    }
    return false;
  }
	/*
	* Attempts to remove the given int from the AVL tree
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool AVL::remove(int data)
  {
    return remove_function(root, data);
  }
  bool AVL::remove_function(Node*& n, int value)
  {
    if (n == NULL)
    {
      return false;
    }

    if (n->data > value)
    {
      return remove_function(n->leftChild, value);
    }
    if (n->data < value)
    {
      return remove_function(n->rightChild, value);
    }
    if (n->rightChild == NULL && n->leftChild == NULL) //No next of kin
    {
      delete n;
      n = NULL;
      return true;
    }

    if (n->rightChild == NULL || n->leftChild == NULL) //one child
    {
      Node* temp;
      temp = n->leftChild;
      if (n->leftChild == NULL)
      {
        temp = n->rightChild;
      }
      delete n;
      n = temp;
      return true;
    }
    Node* temp = n->leftChild;
    Node* parent = n;
    while (temp->rightChild != NULL) //two children.
    {
      parent = temp;
      temp = temp->rightChild;
    }
		if (n->data != parent->data)
		{
    parent->rightChild = temp->leftChild;
	}
	else parent->leftChild = temp->leftChild;

		n->data = temp->data;
    delete temp;
    return true;
  }

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void AVL::clear()
  {
    clear_function(root);
    root = NULL;
  }
  void AVL::clear_function(Node* n)
  {
    if (n == NULL)
    {
      return;
    }
    if (n->leftChild != NULL)
    {
        clear_function(n->leftChild);
    }
    if (n->rightChild != NULL)
    {
      clear_function(n->rightChild);
    }

    delete n;
    return;
  }
