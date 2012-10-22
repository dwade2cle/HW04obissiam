#include "Node.h"
#include "Starbucks.h"

#define NUMBITS 4
class Web : public Starbucks
{
	public:
		Web(Node* root);
		Web(Node* root, char numBits);
		virtual void defineCorner(Node* root, bool leftOrRight);
		virtual void insertTethers(Node* root, char size);
		virtual void build(Entry* c, int n);
		virtual Entry* getNearest(double x, double y);

	private:
		Node* root_;
};