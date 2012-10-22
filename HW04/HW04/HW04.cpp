// HW04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Web.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Node* root_ = new Node();
	Web* web = new Web(root_, NUMBITS);
	root_->left_->nodeInfo_ |= 0 << LOCATIONBIT0;
	root_->left_->nodeInfo_ |= 0 << LOCATIONBIT1;
	root_->right_->nodeInfo_ |= 0 << LOCATIONBIT0;
	root_->right_->nodeInfo_ |= 1 << LOCATIONBIT1;	
	web->defineCorner(root_->left_, true);
	web->defineCorner(root_->right_, false);
	web->insertTethers(root_->left_->left_, 2*NUMBITS - 2);
	web->insertTethers(root_->left_->right_, 2*NUMBITS - 2);
	web->insertTethers(root_->right_->left_, 2*NUMBITS - 2);
	web->insertTethers(root_->right_->right_, 2*NUMBITS - 2);
	//Node* hey = root_->right_->left_;
	//int yo = hey->getX();
	//cout << yo << endl;
	return 0;
}

