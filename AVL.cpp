#include "NodeInterface.h"
#include "Node.h"
#include "AVL.h"
#include <algorithm>
#include <sstream>
#include <queue>
#include <string>
using namespace std;



string tsb(Node* bst) {
    queue<NodeInterface*> readQ; // used to read in the levels of the tree, contains Node*
    stringstream nodeReader_ss; // used to store the values of the nodes and the level-order sequence
    int depth = 0; // the depth of a node on the tree

    if (bst == NULL) {
        return "BST is empty\n";
    }

    readQ.push(bst); // push the root node of the tree into the queue

    while (!readQ.empty()) { // as long as the queue has a remaining node:
        int i = readQ.size(); // store the number of nodes on this level of the tree
        nodeReader_ss << depth << ":  ";
        for (; i > 0; i--) { // for each node on this level,
            NodeInterface* nextNode = readQ.front(); // store the next node in the queue
            nodeReader_ss << nextNode->getData() << " "; // store the data from the node into the ss
            if (nextNode->getLeftChild() != NULL) { // if there is a left child, push the left child into the queue
                readQ.push(nextNode->getLeftChild());
            }
            if (nextNode->getRightChild() != NULL) { // if there is a right child, push the left child into the queue
                readQ.push(nextNode->getRightChild());
            }
            readQ.pop(); // pop the node off of the queue, leaving its children in the queue
        }
        nodeReader_ss << "\n"; // push an endl into the ss to distinguish levels
        depth++;
    }

    return nodeReader_ss.str();
}






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
	//cout << "Add_Function adding " << value << endl;
	if (n == NULL)
	{
		n = new Node(value);
		n->height = 0;
		return true;
	}

	if (n->data == value)
	{
		//cout << "Add_Function FALSE FALSE FALSE" << endl;
		return false;
	}

	if (n->data > value)
	{
		//cout << "Add_Function n->data > value" << endl;
		bool fluff = add_function(n->leftChild, value);
		if (fluff == true)
		{
			if (n->getBalance() > 1)
				balanceLeft(n);
			if (n->getBalance() < -1)
				balanceRight(n);
		}
		return fluff;
	}

	if (n->data < value)
	{
		//cout << "Add_Function n->data < value" << endl;
		bool fluff2 = add_function(n->rightChild, value);
		if (fluff2 == true)
		{
			if (n->getBalance() > 1)
				balanceLeft(n);
			if (n->getBalance() < -1)
				balanceRight(n);

		}
		return fluff2;
	}
	if (n->getBalance() > 1)
		balanceLeft(n);
	if (n->getBalance() < -1)
		balanceRight(n);
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
		bool fluff5;
		fluff5 = remove_function(root, data);
		balance(root);
		return fluff5;


}

bool AVL::remove_function(Node*& n, int value)
{
		//cout << "Remove_Function Removing " << value << endl;
	if (n == NULL)
	{
		return false;
	}
	if (n->data > value)
	{
		//cout << "Remove_Function n > value " << value << endl;

		bool fluff3 = remove_function(n->leftChild, value);

		balance(n);

		return fluff3;
	}
	if (n->data < value)
	{
		//cout << "Remove_Function n < value " << value << endl;

		bool fluff4 = remove_function(n->rightChild, value);

		balance(n);

		return fluff4;
	}

	if (n->rightChild == NULL && n->leftChild == NULL) //No next of kin
	{
		//cout << "Remove_Function no children " << value << endl;

		delete n;
		n = NULL;
		return true;
	}

	if (n->rightChild == NULL || n->leftChild == NULL) //one child
	{
		//cout << "Remove_Function one child " << value << endl;

		Node* temp;
		temp = n->leftChild;
		if (n->leftChild == NULL)
		{
			temp = n->rightChild;
		}
		delete n;
		n = temp;
		balance(n);
		return true;
	}

	Node* temp = fosterParent(n->leftChild);

	temp->leftChild = n->leftChild;
	temp->rightChild = n->rightChild;
	delete n;
	n = temp;
	return true;
}

Node* AVL::fosterParent(Node*& n)
{
	if (n->rightChild == NULL)
	{
		Node* temp = n;
		n = n->leftChild;
		return temp;
	}
	Node* temp = fosterParent(n->rightChild);
	balance(n);
	return temp;
}

/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void AVL::clear()
{
	clear_function(root);
	root = NULL;
}
void AVL::clear_function(Node*& n)
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


void AVL::balanceRight(Node*& n) //right-right and right-left
{
	if (n == NULL)
		return;

		//cout << "balanceRight" << endl;
		if (n->leftChild->getBalance() >= 1)
		{
			rotateLeft(n->leftChild);
		}
		rotateRight(n);
}

void AVL::balanceLeft(Node*& n) //left-left and left-right
{
	if (n == NULL)
		return;
	//cout << "balanceLeft" << endl;
		if (n->rightChild->getBalance() <= -1)
		{
			rotateRight(n->rightChild);
		}
		rotateLeft(n);
}


void AVL::rotateRight(Node*& n)
{
	//cout << "rotateRight" << endl;
	Node* temp = n->leftChild;
	n->leftChild = temp->rightChild;
	temp->rightChild = n;
	n = temp;
}

void AVL::rotateLeft(Node*& n)
{
	Node* temp = n->rightChild;
	n->rightChild = temp->leftChild;
	temp->leftChild = n;
	n = temp;
}

void AVL::balance(Node*& n)
{
	if (n == NULL)
		return;
	if (n->getBalance() > 1)
		balanceLeft(n);
	else if (n->getBalance() < -1)
		balanceRight(n);

		balance(n->leftChild);
		balance(n->rightChild);
}
