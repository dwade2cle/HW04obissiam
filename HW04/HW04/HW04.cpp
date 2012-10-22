// HW04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Web.h"


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
	Node* root = new Node();
	Web* web = new Web(root);
	web->build(listValues, 6);
	return 0;
}

