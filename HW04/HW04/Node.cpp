#include "stdafx.h"
#include "Node.h"

Node::Node()	{
	nodeInfo_ = 0;
	sizeLeaf_ = 0;
	data_ = new Entry();
	parent_ = NULL;
	left_ = right_ = NULL;
	top_Left_ = top_Middle_ = top_Right_ = NULL;
	bottom_Left_ = bottom_Middle_ = bottom_Right_ = NULL;
	middle_Left_ = middle_Right_ = NULL;	
}

Node::~Node()	{};

Node::Node(Entry* in)	{
	sizeLeaf_ = 0;
	nodeInfo_ = 0;
	data_ = in;
	parent_ = NULL;
	left_ = right_ = NULL;
	top_Left_ = top_Middle_ = top_Right_ = NULL;
	bottom_Left_ = bottom_Middle_ = bottom_Right_ = NULL;
	middle_Left_ = middle_Right_ = NULL;
}

Node* Node::insertNode(Node* parent, Entry* in, bool leftOrRight)	{
	Node* newNode;
	char test = 0;
	if (leftOrRight == true)	{
		if (exists(parent, leftOrRight)) return parent->left_;
		newNode = new Node(in);
		parent->left_ = newNode;
		parent->nodeInfo_ |= 1 << HASLEFTCHILD;
	} else {
		if (exists(parent, leftOrRight)) return parent->right_;
		newNode = new Node(in);
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

Node* Node::moveDown(Node* node, bool leftOrRight)	{
	return leftOrRight ? node->left_ : node->right_;
}

void Node::leafAdded(Node* node, Entry* in)	{
	if (!node->exists(node, true)) {
		node->sizeLeaf_++;
		insertNode(node, in, true);
	} else if (!node->exists(node, false)) {
		node->sizeLeaf_++;
		insertNode(node, in, false);
		node->nodeInfo_ |= 1 << ELEMENTADDED;
	} else if (node->left_->nodeInfo_& (1 << ELEMENTADDED) == 0) leafAdded(node->left_, in);
	else if (node->left_->nodeInfo_& (1 << ELEMENTADDED) == 0) leafAdded(node->right_, in);
	else if (node->left_->sizeLeaf_ > node->right_->sizeLeaf_) leafAdded(node->right_, in);
	else leafAdded(node->left_,in);
}