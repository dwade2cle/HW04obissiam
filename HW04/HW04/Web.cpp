/** Author: Eddie Obissi
This class creates a web-like data structure, whose initial nodes provide spatial organization, 
and whose final nodes have information that a user might like to use.  

All methods are original, and may be used by anyone.
*/

#include "stdafx.h"
#include "Web.h"

//Default constructor
Web::Web(Node* root)	{
	root_ = root;
};

// Here we have a Web constructor.  It's job is to create the initial nodes for the structure.
Web::Web(Node* root, char numBits)	{
	root_  = root;
	char test;
	int iterations = pow(2.0, numBits);
	int count = 0;
	Node* temp;
	for (int i = 0; i < iterations; i++)	{
		for (int j = 0; j < iterations; j++)	{
			Node* cur = root;
			for (int k = numBits; k > 0; k--)	{
				//bit = number & (1 << x);
				// Check to see if kth bit of i is greater than 0;
				test = i& (1 << k - 1);
				// Insert new node (insertNode checks if there is already a node on it's own
				temp = cur->insertNode(cur, new Entry(), (test == 0));
				// Move cur down the web
				cur = temp;
				// Clear test bit so it equals 0 again
				test &= ~(1 << k - 1); 

				// Repeat for j
				test = j& (1 << k - 1); 
				temp = cur->insertNode(cur, new Entry(), (test == 0));
				cur = temp;
				test &= ~(1 << k - 1); 
			}
		}
	}
}

// Here we give spatial information about the node.  There are four types of nodes, and 
// they branch differently.
void Web::defineCorner(Node* root, bool leftOrRight)	{
	// Case root is left
	if (leftOrRight == true)	{
		if (root->exists(root, true))	{
			root->left_->nodeInfo_ |= 0 << LOCATIONBIT0;
			root->left_->nodeInfo_ |= 0 << LOCATIONBIT1;
			root->right_->nodeInfo_ |= 0 << LOCATIONBIT0;
			root->right_->nodeInfo_ |= 1 << LOCATIONBIT1;
			defineCorner(root->left_, true);
			defineCorner(root->right_, false);
		} else return;
	// Case root is right
	} else	{
	if (root->exists(root, false))	{
			root->left_->nodeInfo_ |= 1 << LOCATIONBIT0;
			root->left_->nodeInfo_ |= 0 << LOCATIONBIT1;
			root->right_->nodeInfo_ |= 1 << LOCATIONBIT0;
			root->right_->nodeInfo_ |= 1 << LOCATIONBIT1;
			defineCorner(root->left_, true);
			defineCorner(root->right_, false);
		} else return;
	}
}

// Assumes a web of hieght 4 or greater
void Web::insertTethers(Node* root, char size)	{
	
	if (size > 1)	{
		char newSize = size - 2;
		Node* zero = root->left_->left_;
		Node* one = root->left_->right_;
		Node* two = root->right_->left_;
		Node* three = root->right_->right_;

		zero->middle_Left_ = zero->getLeft(zero, 0);
		zero->middle_Right_ = zero->getRight(zero, 0);
		zero->top_Right_ = zero->getTL(zero, 0);
		zero->top_Middle_ = zero->getTM(zero, 0);
		zero->top_Right_ = zero->getTR(zero, 0);
		zero->bottom_Right_ = zero->getBL(zero, 0);
		zero->bottom_Middle_ = zero->getBM(zero, 0);
		zero->bottom_Right_ = zero->getBR(zero, 0);

		one->middle_Left_ = one->getLeft(one, 1);
		one->middle_Right_ = one->getRight(one, 1);
		one->top_Right_ = one->getTL(one, 1);
		one->top_Middle_ = one->getTM(one, 1);
		one->top_Right_ = one->getTR(one, 1);
		one->bottom_Right_ = one->getBL(one, 1);
		one->bottom_Middle_ = one->getBM(one, 1);
		one->bottom_Right_ = one->getBR(one, 1);

		two->middle_Left_ = two->getLeft(two, 2);
		two->middle_Right_ = two->getRight(two, 2);
		two->top_Right_ = two->getTL(two, 2);
		two->top_Middle_ = two->getTM(two, 2);
		two->top_Right_ = two->getTR(two, 2);
		two->bottom_Right_ = two->getBL(two, 2);
		two->bottom_Middle_ = two->getBM(two, 2);
		two->bottom_Right_ = two->getBR(two, 2);

		three->middle_Left_ = three->getLeft(three, 3);
		three->middle_Right_ = three->getRight(three, 3);
		three->top_Right_ = three->getTL(three, 3);
		three->top_Middle_ = three->getTM(three, 3);
		three->top_Right_ = three->getTR(three, 3);
		three->bottom_Right_ = three->getBL(three, 3);
		three->bottom_Middle_ = three->getBM(three, 3);
		three->bottom_Right_ = three->getBR(three, 3);

		insertTethers(zero, newSize);
		insertTethers(one, newSize);
		insertTethers(two, newSize);
		insertTethers(three, newSize);
	} else return;
}

// This function is the workhorse of this class. It uses the other functions and constructors to create the 
// web, then adds the array of Entry objects.
void Web::build(Entry* c, int n) {
	// Local variables to help read in values from parameters
	int testX, testY;
	double inX, inY;
	// The current node points to the root;
	Node* cur = root_;
	
	for (int i = 0; i < n; i++)	{
		inX = c[i].x;
		inY = c[i].y;
		testX = (int) pow(10.0, 9) * inX;
		testY = (int) pow(10.0, 9) * inY;
		cur = root_;
		// Deciding where in the web the Entry should go.
		// It will always go to a node at the edge of our web.
		for (int j = 32; j > (32 - NUMBITS); j--)	{
			cur = cur->moveDown(cur, (testX& (1 << j) == 0));
			cur = cur->moveDown(cur, (testY& (1 << j) == 0));
		}
		// Inserts a node with our entry at the desired location
		cur->leafAdded(cur, &c[i]); 
	}
}

Entry* Web::getNearest(double x, double y) {
	// The current node points to the root;
	Node* cur = root_; Entry* e = new Entry();
	e->x = x; e->y = y;
	// Work our way down to the appropriate node
	int xInt = (int) x; int yInt = (int) y;
	for (int i = 32; i > (32 - NUMBITS); i--)	{
		cur = cur->moveDown(cur, (xInt& (1 << i) == 0));
		cur = cur->moveDown(cur, (yInt& (1 << i) == 0));
	}
	cur = cur->searchThreads(cur, e);
	return cur->data_;
}