// HW04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Web.h"
#include <iostream>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Entry listValues[6];
	listValues[0].identifier = "Zero";
	listValues[0].x = .25;
	listValues[0].y = .25;
	listValues[1].identifier = "Zero";
	listValues[1].x = .50;
	listValues[1].y = .50;
	listValues[2].identifier = "Zero";
	listValues[2].x = .50;
	listValues[2].y = .75;
	listValues[3].identifier = "Zero";
	listValues[3].x = .89;
	listValues[3].y = .42524;
	listValues[4].identifier = "Zero";
	listValues[4].x = .4525;
	listValues[4].y = .246525;
	listValues[5].identifier = "Zero";
	listValues[5].x = .25;
	listValues[5].y = .25;
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
	web->build(listValues, 6);
	Entry* e = web->getNearest(0.25, 0.25);
	cout << e->x << endl << e->y << endl; 

	return 0;
}

