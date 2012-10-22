#include "stdafx.h"
#include "Node.h"

Node::Node()	{
	nodeInfo_ = 0;
	sizeLeaf = 0;
	data_ = new Entry();
	parent_ = NULL;
	left_ = right_ = NULL;
	top_Left_ = top_Middle_ = top_Right_ = NULL;
	bottom_Left_ = bottom_Middle_ = bottom_Right_ = NULL;
	middle_Left_ = middle_Right_ = NULL;	
}

Node::~Node()	{};

Node::Node(Entry* in)	{
	sizeLeaf = 0;
	nodeInfo_ = 0;
	data_ = in;
	parent_ = NULL;
	left_ = right_ = NULL;
	top_Left_ = top_Middle_ = top_Right_ = NULL;
	bottom_Left_ = bottom_Middle_ = bottom_Right_ = NULL;
	middle_Left_ = middle_Right_ = NULL;
}

Node* Node::insertNode(Node* parent, bool leftOrRight)	{
	Node* newNode;
	char test = 0;
	if (leftOrRight == true)	{
		//test = parent->nodeInfo_& (1 << HASLEFTCHILD);
		//if (test > 0) return parent->left_;
		if (exists(parent, leftOrRight)) return parent->left_;
		newNode = new Node();
		parent->left_ = newNode;
		parent->nodeInfo_ |= 1 << HASLEFTCHILD;
	} else {
		//test = parent->nodeInfo_& (1 << HASRIGHTCHILD);
		//if (test > 0) return parent->right_;
		if (exists(parent, leftOrRight)) return parent->right_;
		newNode = new Node();
		parent->right_ = newNode;
		parent->nodeInfo_ |= 1 << HASRIGHTCHILD;
	}
	newNode->parent_ = parent;
	return newNode;
}

bool Node::exists(Node* node, bool leftOrRight)	{
	char test = 0;
	if (leftOrRight == true)	
		test = node->nodeInfo_& (1 << HASLEFTCHILD);
	else 
		test = node->nodeInfo_& (1 << HASRIGHTCHILD);
	return test > 0;
}