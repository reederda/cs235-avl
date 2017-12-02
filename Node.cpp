#include <iostream>
#include <algorithm>
#include "Node.h"

	/*
	* Returns the data that is stored in this node
	*
	* @return the data that is stored in this node.
	*/
	int Node::getData() const
  {
    return data;
  }

	/*
	* Returns the left child of this node or null if it doesn't have one.
	*
	* @return the left child of this node or null if it doesn't have one.
	*/
	NodeInterface * Node::getLeftChild() const
  {
    return leftChild;
  }

	/*
	* Returns the right child of this node or null if it doesn't have one.
	*
	* @return the right child of this node or null if it doesn't have one.
	*/
	NodeInterface * Node::getRightChild() const
  {
    return rightChild;
  }

	/*
	* Returns the height of this node. The height is the number of nodes
	* along the longest path from this node to a leaf.  While a conventional
	* interface only gives information on the functionality of a class and does
	* not comment on how a class should be implemented, this function has been
	* provided to point you in the right direction for your solution.  For an
	* example on height, see page 448 of the text book.
	*
	* @return the height of this tree with this node as the local root.
	*/
	int Node::getHeight()
	{
		int leftHeight = 0;
		int rightHeight = 0;

		if (leftChild != NULL)
		{
			leftHeight = leftChild->getHeight();
		}
		if (rightChild != NULL)
		{
			rightHeight = rightChild->getHeight();
		}
		return max(leftHeight, rightHeight) + 1;
	}


	int Node::getBalance()
	{
		int right;
		int left;

		if (rightChild != NULL)
		{
			right = rightChild->getHeight();
		}
		else
		right = 0;

		if (leftChild != NULL)
		{
			left = leftChild->getHeight();
		}
		else
		left = 0;

		return right - left;
	}
