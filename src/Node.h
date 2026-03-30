class Node
{
public:
	
	Node(int ID, int PARENT = -1) : id(ID), parent_id(PARENT) {}
	
   int getID() { return id; }

   int getParentID() { return parent_id; }

private:

	int id;
	int parent_id;

};