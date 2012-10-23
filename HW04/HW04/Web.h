#include "Node.h"
#include "Starbucks.h"

#define NUMBITS 3
class Web : public Starbucks
{
	public:
		// A constructor method that sets the root of the Web
		Web(Node* root);
		// A construtor method that creates nodes to form the Web, ending with leaves
		Web(Node* root, char numBits);
		// Goes through a Web, starting at the root, and gives it location values that are important to other methods.
		virtual void defineCorner(Node* root, bool leftOrRight);
		// Links values together so that, searching can be accomplished more quickly.
		virtual void insertTethers(Node* root, char size);
		// Builds a Web that ends with Entry values
		virtual void build(Entry* c, int n);
		// Searches for the closest entry to the value we use
		virtual Entry* getNearest(double x, double y);

	private:
		Node* root_;
};