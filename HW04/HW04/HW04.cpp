// HW04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Web.h"
#include <iostream>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Entry listValues[1000];
	for(int i = 0; i < 1000; i++)	{
		listValues[i].identifier = "Zero";
		listValues[i].x = .2;
		listValues[i].y = .001*i;
	}
	Node* root_ = new Node();
	Web* web = new Web(root_, NUMBITS);
	// Create web
	//Web* web = new Web(root_, NUMBITS);
	// Set values at first two child nodes
	root_->left_->nodeInfo_ |= 0 << LOCATIONBIT0;
	root_->left_->nodeInfo_ |= 0 << LOCATIONBIT1;
	root_->right_->nodeInfo_ |= 0 << LOCATIONBIT0;
	root_->right_->nodeInfo_ |= 1 << LOCATIONBIT1;	
	// Set values at all the other nodes
	web->defineCorner(root_->left_, true);
	web->defineCorner(root_->right_, false);
	// Tie nodes together to form web
	web->insertTethers(root_->left_->left_, 2*NUMBITS - 2);
	web->insertTethers(root_->left_->right_, 2*NUMBITS - 2);
	web->insertTethers(root_->right_->left_, 2*NUMBITS - 2);
	web->insertTethers(root_->right_->right_, 2*NUMBITS - 2);
	web->build(listValues, 999);
	Entry* e = web->getNearest(0.502, 0.502);
	cout << e->x << endl << e->y << endl; 

	return 0;
}

