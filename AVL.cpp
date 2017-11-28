#include "NodeInterface.h"
#include "Node.h"
#include "AVL.h"
#include <algorithm>
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
			n->height = 1;
      return true;
    }
    if (n->data > value)
    {
			bool fluff = add_function(n->leftChild, value);
			if (fluff == true)
			{
				setHeight(n);
				cout << "n height: " << n->height << endl;
				if (n->getHeight() < -1)
					balanceLeft(n);
				if (n->getHeight() > 1)
					balanceRight(n);
				setHeight(n);
			}
      return fluff;
    }
    if (n->data < value)
    {
			cout << "n height: " << n->height << endl;
			bool fluff2 = add_function(n->rightChild, value);
			if (fluff2 == true)
			{
				setHeight(n);
				cout << "n height 2: " << n->height << endl;
				if (n->getHeight() < -1)
					balanceLeft(n);
				if (n->getHeight() > 1)
					balanceRight(n);
				setHeight(n);
			}
      return fluff2;
    }

		setHeight(n);
		if (n->getHeight() < -1)
			balanceLeft(n);
		if (n->getHeight() > 1)
			balanceRight(n);
		setHeight(n);
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
			n->height=0;
      return false;
    }
    if (n->data > value)
    {
			bool fluff3 = remove_function(n->leftChild, value);
			if (fluff3 == true)
			{
				setHeight(n);
				if (n->leftChild != NULL)
					balanceLeft(n);
				if (n->rightChild != NULL)
					balanceRight(n);
				setHeight(n);
			}
      return fluff3;
    }
    if (n->data < value)
    {
			bool fluff4 = remove_function(n->rightChild, value);
			if (fluff4 == true)
			{
				setHeight(n);
				if (n->leftChild != NULL)
					balanceLeft(n);
				if (n->rightChild != NULL)
					balanceRight(n);
				setHeight(n);
			}
      return fluff4;
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
	setHeight(n);

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

	int AVL::setHeight(Node*& n)
	{
		n->height = n->getHeight();
		return n->height;
	}

	void AVL::balanceRight(Node* n) //right-right and right-left
	{
		if (n->rightChild != NULL)
		{
			if (n->getBalance() > 1)
			{
				if (n->rightChild->getBalance() < 0)
				{
					rotateRight(n);
				}
				rotateLeft(n);
			}
		}
	}

	void AVL::balanceLeft(Node* n) //left-left and left-right
	{
		if (n->getBalance() < -1)
		{
			if (n->leftChild->getBalance() > 0)
			{
				rotateLeft(n);
			}
			rotateRight(n);
		}
	}


	void AVL::rotateRight(Node* n)
	{
		Node* temp = n->leftChild;
		n->leftChild = temp->rightChild;
		temp->rightChild = n;
		n = temp;
	}

	void AVL::rotateLeft(Node* n)
	{
		Node* temp = n->rightChild;
		n->rightChild = temp->leftChild;
		temp->leftChild = n;
		n = temp;
	}
