#include "Starbucks.h"

#define HASLEFTCHILD 0
#define HASRIGHTCHILD 1
#define LOCATIONBIT1 2
#define LOCATIONBIT0 3
#define BEENCHECKED 4

class Node	{
public:
	Node* parent_;
	Node* left_;
	Node* right_;
	// These nodes represent the surrounding blocks of points
	Node* top_Left_;
	Node* top_Middle_;
	Node* top_Right_;
	Node* middle_Right_;
	Node* bottom_Right_;
	Node* bottom_Middle_;
	Node* bottom_Left_;
	Node* middle_Left_;
	// The data that we will need when checking these nodes
	Entry* data_;
	char nodeInfo_;
	short sizeLeaf_;

	
	// Create an empty node
	Node();

	~Node();
	
	// Create a node with data in it
	Node(Entry* in);
	
	// Insert a node with data in the correct spot
	Node* insertNode(Node* parent, bool leftOrRight);

	Node* getLeft(Node* node, short locationType)	{
		switch (locationType)	{
		case 0 : return node->parent_->parent_->parent_->left_->left_->right_;
		case 1 : return node->parent_->left_;
		case 2 : return node->parent_->parent_->parent_->parent_->right_->left_->left_->left_;
		case 3 : return node->parent_->left_;
		}
		return node;
	}

	Node* getTL(Node* node, short locationType)	{
		switch (locationType)	{
		case 0 : return node->parent_->parent_->parent_->left_->right_->right_;
		case 1 : return node->parent_->parent_->right_->left_;
		case 2 : return node->parent_->parent_->parent_->parent_->right_->left_->left_->right_;
		case 3 : return node->parent_->parent_->parent_->parent_->right_->left_->left_->left_;
		}
		return node;
	}

		Node* getTM(Node* node, short locationType)	{
		switch (locationType)	{
		case 0 : return node->parent_->parent_->right_->left_;
		case 1 : return node->parent_->parent_->right_->right_;
		case 2 : return node->parent_->parent_->parent_->parent_->right_->right_->left_->left_;
		case 3 : return node->parent_->parent_->parent_->parent_->right_->left_->left_->right_;
		}
		return node;
	}

	Node* getTR(Node* node, short locationType)	{
		switch (locationType)	{
		case 0 : return node->parent_->parent_->right_->right_;
		case 1 : return node->parent_->parent_->parent_->right_->right_->left_;
		case 2 : return node->parent_->parent_->parent_->parent_->right_->right_->left_->right_;
		case 3 : return node->parent_->parent_->parent_->parent_->right_->right_->left_->left_;
		}
		return node;
	}

	Node* getRight(Node* node, short locationType)	{
		switch (locationType)	{
		case 0 : return node->parent_->right_;
		case 1 : return node->parent_->parent_->parent_->right_->left_->left_;
		case 2 : return node->parent_->right_;
		case 3 : return node->parent_->parent_->parent_->right_->right_->left_;
		}
		return node;
	}

	Node* getBR(Node* node, short locationType)	{
		switch (locationType)	{
		case 0 : return node->parent_->parent_->parent_->parent_->left_->right_->right_->right_;
		case 1 : return node->parent_->parent_->parent_->parent_->left_->right_->right_->left_;
		case 2 : return node->parent_->parent_->left_->right_;
		case 3 : return node->parent_->parent_->parent_->right_->left_->left_;
		}
		return node;
	}

	Node* getBM(Node* node, short locationType)	{
		switch (locationType)	{
		case 0 : return node->parent_->parent_->parent_->parent_->left_->right_->right_->left_;
		case 1 : return node->parent_->parent_->parent_->parent_->left_->left_->right_->right_;
		case 2 : return node->parent_->parent_->left_->left_;
		case 3 : return node->parent_->parent_->left_->right_;
		}
		return node;
	}

	Node* getBL(Node* node, short locationType)	{
		switch (locationType)	{
		case 0 : return node->parent_->parent_->parent_->parent_->left_->left_->right_->right_;
		case 1 : return node->parent_->parent_->parent_->parent_->left_->left_->right_->left_;
		case 2 : return node->parent_->parent_->parent_->left_->left_->right_;
		case 3 : return node->parent_->parent_->left_->left_;
		}
		return node;
	}
	bool exists(Node* node, bool leftOrRight);
};