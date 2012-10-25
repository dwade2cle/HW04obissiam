// HW04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Web.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Entry listValues[1000];
	for(int i = 0; i < 1000; i++)	{
		listValues[i].identifier = "Zero";
		listValues[i].x = .001*i;
		listValues[i].y = .001*i;
	}
	Node* root = new Node();
	Web* web = new Web(root);
	web->build(listValues, 999);
	Entry* e = web->getNearest(0.95, 0.15);
	cout << e->x << endl << e->y << endl; 

	return 0;
}

