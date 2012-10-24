#include "stdafx.h"
#include "Node.h"

Node::Node()	{
	nodeInfo_ = 0;
	data_ = new Entry();
	parent_ = NULL;
	left_ = right_ = NULL;
	top_Left_ = top_Middle_ = top_Right_ = NULL;
	bottom_Left_ = bottom_Middle_ = bottom_Right_ = NULL;
	middle_Left_ = middle_Right_ = NULL;	
}

Node::~Node()	{};

Node::Node(Entry* in)	{
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
	//leftOrRight ? cout << "LEFT" << endl : cout << "RIGHT" << endl;
	return leftOrRight ? node->left_ : node->right_;
}

void Node::leafAdded(Node* node, Entry* in)	{
	double x1, x2, y1, y2, distance1, distance2;
	Node* temp;
	if (!node->exists(node, true))	{
		node->nodeInfo_ |= 1 << HASLEFTCHILD;
		Node* newNode = new Node(in);
		node->left_ = newNode;
		newNode->parent_ = node;
		return;
	} else {
		//if both |x1 - x2| <= 0.00001 and |y1 - y2| < 0.00001, return
		x1 = node->left_->data_->x; y1 = node->left_->data_->y;
		x2 = in->x; y2 = in->y;
		if (abs(x1-x2) <= 0.00001 && abs(x1-x2) <= 0.00001) return;
		distance1 = sqrt(x1*x1 + y1*y1);
		distance2 = sqrt(x2*x2 + y2*y2);
		if(distance2 < distance1)	{
			Node* newNode = new Node(in);
			newNode->left_ = node->left_;
			node->left_->parent_ = newNode;
			newNode->parent_ = node;
			node->left_ = newNode;
		} else leafAdded(node->left_, in);
	}
}

Node* Node::searchLeaf(Node* node, double x, double y, double closest)	{
	double distance;
	double x1, y1;
	if (node->exists(node, true))	{
		// Indicated that this node has been checked.
		node->nodeInfo_ |= 1 << BEENCHECKED;
		x1 = node->left_->data_->x;
		y1 = node->left_->data_->y;
		distance = sqrt(abs(x - x1)*abs(x - x1) + abs(y - y1)*abs(y - y1));
		if (distance < closest) closest = distance;
		searchLeaf(node->left_, x, y, closest);
	} else return node;
}

Node* Node::traverseWeb(Node* node)	{
	// If the node has no pointer to the right, it is at the edge of the web
	//bit = number & (1 << x);
	short test = node->nodeInfo_& (1 << HASRIGHTCHILD);
	if (test == 0) return node;
	else {
		traverseWeb(node->left_->left_);
		traverseWeb(node->left_->right_);
		traverseWeb(node->right_->left_);
		traverseWeb(node->right_->right_);
	}
}

Node* Node::searchThreads(Node* node, Entry* in)	{
	Node* outNode;
	Node* temp;
	Entry* e = new Entry();
	e->x = FARVALUE;
	e->y = FARVALUE;
	// This comes in handy if we have to widen our search
	node = traverseWeb(node);
	if (node->exists(node, true)) outNode = node->searchLeaf(node->left_, in->x, in->y, FARVALUE);
	else outNode = new Node(e);

	if (node->middle_Left_ != NULL)	{
		temp = searchLeaf(node->middle_Left_, in->x, in->y, FARVALUE);
		if (distance(in, temp) < distance(in, outNode)) outNode = temp;
	}
	if (node->top_Left_ != NULL)	{
		temp = searchLeaf(node->top_Left_, in->x, in->y, FARVALUE);
		if (distance(in, temp) < distance(in, outNode)) outNode = temp;
	}
	if (node->top_Middle_ != NULL)	{
		temp = searchLeaf(node->top_Middle_, in->x, in->y, FARVALUE);
		if (distance(in, temp) < distance(in, outNode)) outNode = temp;
	}
	if (node->top_Right_ != NULL)	{
		temp = searchLeaf(node->top_Right_, in->x, in->y, FARVALUE);
		if (distance(in, temp) < distance(in, outNode)) outNode = temp;
	}
	if (node->middle_Right_ != NULL)	{
		temp = searchLeaf(node->middle_Right_, in->x, in->y, FARVALUE);
		if (distance(in, temp) < distance(in, outNode)) outNode = temp;
	}
	if (node->bottom_Right_ != NULL)	{
		temp = searchLeaf(node->bottom_Right_, in->x, in->y, FARVALUE);
		if (distance(in, temp) < distance(in, outNode)) outNode = temp;
	}
	if (node->bottom_Middle_ != NULL)	{
		temp = searchLeaf(node->bottom_Middle_, in->x, in->y, FARVALUE);
		if (distance(in, temp) < distance(in, outNode)) outNode = temp;
	}
	if (node->bottom_Left_ != NULL)	{
		temp = searchLeaf(node->bottom_Left_, in->x, in->y, FARVALUE);
		if (distance(in, temp) < distance(in, outNode)) outNode = temp;
	}
	if (outNode->data_->x == FARVALUE)	searchThreads(node->parent_->parent_, in);
	else return outNode;
}

double Node::distance(Entry* in, Node* node)	{
	double x1 = in->x; double y1  = in->y;
	double x2 = node->data_->x; double y2 = node->data_->y;
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}