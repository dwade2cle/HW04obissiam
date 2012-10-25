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

Node* Node::searchLeaf(Node* ancestor, Node* descendant, Entry* in)	{
	bool ancestorCloser;
	if (distance(in, ancestor) < distance(in, descendant)) ancestorCloser = true;
	else ancestorCloser = false;
	if (ancestor->exists(descendant, true))	{
		ancestorCloser ? searchLeaf(ancestor, descendant->left_, in) : 
			searchLeaf(descendant, descendant->left_, in);	
	} else if (ancestorCloser) return ancestor;
	else return descendant;
}

Node* Node::traverseWeb(Node* node, Entry* in)	{
	// If the node has no pointer to the right, it is at the edge of the web
	Entry* e = new Entry();
	e->x = FARVALUE; e->y = FARVALUE;
	Node* LL; Node* LR; Node* RL; Node* RR;
	double dLL, dLR, dRL, dRR;

	short test = (node->nodeInfo_& (1 << HASRIGHTCHILD));
	if (test == 0 && node->exists(node, true)) return searchLeaf(new Node(e), node->left_, in);
	else if (!node->exists(node, true)) return new Node(e);
	else {
		LL = traverseWeb(node->left_->left_, in); LR = traverseWeb(node->left_->right_, in);
		RL = traverseWeb(node->right_->left_, in); RR = traverseWeb(node->right_->right_, in);
		dLL = LL->distance(in, LL); dLR = LR->distance(in, LR); 
		dRL = RL->distance(in, RL); dRR = RR->distance(in, RR); 
		if (dLL < dLR && dLL < dRL && dLL < dRR) return LL;
		else if (dLR < dRL && dLR < dRR) return LR;
		else if (dRL < dRR) return RL;
		else return RR;
	}
}

Node* Node::searchThreads(Node* node, Entry* in)	{
	Entry* e = new Entry(); e->x = FARVALUE; e->y = FARVALUE;
	Node* L; Node* TL; Node* TM; Node* TR; Node* R; Node* BR; Node* BM; Node* BL;
	Node* outNode = traverseWeb(node, in);
	node->middle_Left_ != NULL ? L = traverseWeb(middle_Left_, in) : L = new Node(e);
	if (node->distance(in, L) < node->distance(in, outNode)) outNode = L;
	node->top_Left_!= NULL ? TL = traverseWeb(top_Left_, in) : TL = new Node(e);
	if (node->distance(in, TL) < node->distance(in, outNode)) outNode = TL;
	node->top_Middle_ != NULL ? TM = traverseWeb(top_Middle_, in) : TM = new Node(e);
	if (node->distance(in, TM) < node->distance(in, outNode)) outNode = TM;
	node->top_Right_ != NULL ? TR = traverseWeb(top_Right_, in) : TR = new Node(e);
	if (node->distance(in, TR) < node->distance(in, outNode)) outNode = TR;
	node->middle_Right_ != NULL ? R = traverseWeb(middle_Right_, in) : R = new Node(e);
	if (node->distance(in, R) < node->distance(in, outNode)) outNode = R;
	node->bottom_Right_ != NULL ? BR = traverseWeb(bottom_Right_, in) : BR = new Node(e);
	if (node->distance(in, BR) < node->distance(in, outNode)) outNode = BR;
	node->bottom_Middle_ != NULL ? BM = traverseWeb(bottom_Middle_, in) : BM = new Node(e);
	if (node->distance(in, BM) < node->distance(in, outNode)) outNode = BM;
	node->bottom_Left_ != NULL ? BL = traverseWeb(bottom_Left_, in) : BL = new Node(e);
	if (node->distance(in, BL) < node->distance(in, outNode)) outNode = BL;

	if(outNode->data_->x == FARVALUE) searchThreads(node->parent_->parent_, in);
	else return outNode;
}

double Node::distance(Entry* in, Node* node)	{
	double x1 = in->x; double y1  = in->y;
	double x2 = node->data_->x; double y2 = node->data_->y;
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}