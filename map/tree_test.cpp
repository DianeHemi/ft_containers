//https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp
//https://gist.github.com/SubCoder1/70c2cedc44353ffc539c7567b1051028

#include <iostream>
#include <string>

#define BLACK   0
#define RED     1

struct Node
{
	int color;
	int data;   //Holds the key
	Node*   parent;	//Except root node
	Node*   left;	//left child
	Node*   right;	//right child
};

//Every node is colored
//Root is black
//Every leaf (NIL) is black
//If a red node has a child, it's always black
//For each node, path to any of it's descendant -> Same black depth (nb of black nodes)

/*Rotations :
	- Right
	- Left
	- Left/right
	- Right/left
*/

/*Insertion :
	- Recolor
	- Rotation
Newly inserted nodes are always red -> To not violate the black depth rule
*/


class RedBlackTree
{
	public:
		typedef Node *NodePtr;

	private:
		NodePtr	_root;
		NodePtr	TNULL;

	void initializeNULLNode( NodePtr node, NodePtr parent )
	{
		node->data = 0;
		node->parent = parent;
		node->left = NULL;
		node->right = NULL;
		node->color = 0;
	}

	/*Helpers*/
	void preOrderHelper( NodePtr node )
	{
		if (node != TNULL)
		{
			std::cout << node->data << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
		std::cout << std::endl;
	}

	void inOrderHelper( NodePtr node )
	{
		if (node != TNULL)
		{
			inOrderHelper(node->left);
			std::cout << node->data << " ";
			inOrderHelper(node->right);
		}
		std::cout << std::endl;
	}

	void postOrderHelper( NodePtr node )
	{
		if (node != TNULL)
		{
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			std::cout << node->data << " ";
		}
		std::cout << std::endl;
	}

	NodePtr searchTreeHelper( NodePtr node, int key )
	{
		if (node == TNULL || key == node->data)
			return node;
		if (key < node->data)
			return searchTreeHelper(node->left, key);
		return searchTreeHelper(node->right, key);
	}


	/*
		* Deletion
	*/
	void deleteFix( NodePtr x )
	{
		NodePtr s;

		while(x != _root && x->color == BLACK)
		{
			if (x == x->parent->left)
			{
				s = x->parent->right;
				if (s->color == RED)
				{
					s->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == BLACK && s->right->color == BLACK)
				{
					s->color = RED;
					x = x->parent;
				}
				else
				{
					if (s->right->color == BLACK)
					{
						s->left->color = BLACK;
						s->color = RED;
						rightRotate(s);
						s = x->parent->right;
					}
					s->color = x->parent->color;
					x->parent->color = BLACK;
					leftRotate(x->parent);
					x = _root;
				}
			}
			else
			{
				s = x->parent->left;
				if (s->color == RED)
				{
					s->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					s = x->parent->left;
				}
				if(s->right->color == BLACK && s->right->color == BLACK)
				{
					s->color = RED;
					x = x->parent;
				}
				else
				{
					if (s->left->color == BLACK)
					{
						s->right->color = BLACK;
						s->color = RED;
						leftRotate(s);
						s = x->parent->left;
					}
					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->left->color = BLACK;
					rightRotate(x->parent);
					x = _root;
				}
			}
		}
		x->color = BLACK;

	/*while(k->data != root->data && z->color == BLACK) {
			auto sibling = getRoot();
			if(k->parent->left == z) {
				if(z->parent->right){ sibling = z->parent->right; }
				if(sibling) {
					//CASE -- 1
					if(sibling->color == RED) {
						sibling->color = BLACK;
						z->parent->color = RED;
						leftRotate(z->parent);
						sibling = z->parent->right;
					}
					 //CASE -- 2
					if(sibling->left == nullptr && sibling->right == nullptr) {
						sibling->color = RED;
						z = z->parent;
					}
					else if(sibling->left->color == BLACK && sibling->right->color == BLACK) {
						sibling->color = RED;
						z = z->parent;
					}
					//CASE -- 3
					else if(sibling->right->color == BLACK) {
						sibling->left->color = BLACK;
						sibling->color = RED;
						rightRotate(sibling);
						sibling = z->parent->right;
					} else {
						sibling->color = z->parent->color;
						z->parent->color = BLACK;
						if(sibling->right){ sibling->right->color = BLACK; }
						leftRotate(z->parent);
						z = root;
					}
				} 
			} else {
				if(z->parent->right == z){
					if(z->parent->left){ sibling = z->parent->left; }
					if(sibling) {
						//CASE -- 1
						if(sibling->color == RED){
							sibling->color = BLACK;
							z->parent->color = RED;
							rightRotate(z->parent);
							sibling = z->parent->left;
						}
						//CASE -- 2
						 if(sibling->left == nullptr && sibling->right == nullptr) {
							sibling->color = RED;
							z = z->parent;
						}
						else if(sibling->left->color == BLACK && sibling->right->color == BLACK) {
							sibling->color = RED;
							z = z->parent;
						}
						//CASE -- 3 
						else if(sibling->left->color == BLACK) {
							sibling->right->color = BLACK;
							sibling->color = RED;
							rightRotate(sibling);
							sibling = z->parent->left;
						} else {
							sibling->color = z->parent->color;
							z->parent->color = BLACK;
							if(sibling->left){ sibling->left->color = BLACK; }
							leftRotate(z->parent);
							z = root;
						}
					} 
				}

			}
		}
		z->color = BLACK;*/
	}

	void rbTransplant( NodePtr u, NodePtr v )
	{
		if (u->parent == NULL)
			_root = v;
		else if ( u == u->parent->left )
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	void deleteNodeHelper( NodePtr node, int key )
	{
		NodePtr z = NULL;
		NodePtr x, y;
		while(node != TNULL)
		{
			if ( node->data == key)
				z = node;
			if (node->data <= key)
				node = node->right;
			else
				node = node->left;
		}
		if (z == TNULL)
		{
			std::cout << "Key not found in tree" << std::endl;
			return;
		}

		y = z;
		int y_original_color = y->color;
		if(z->left == TNULL)
		{
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if ( z->right == TNULL)
		{
			x = z->left;
			rbTransplant(z, z->left);
		}
		else
		{
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else
			{
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if(y_original_color == 0)
			deleteFix(x);
	}

	/*
		* Insertion
	*/
	void insertFix( NodePtr k )
	{
		//Fast but not working
		while(k->parent->color == RED) 
		{
			NodePtr grandparent = k->parent->parent;
			NodePtr uncle = getRoot();
			if(k->parent == grandparent->left) 
			{
				if (grandparent->right)
					uncle = grandparent->right;
				if (uncle->color == RED)
				{
					k->parent->color = BLACK;
					uncle->color = BLACK;
					grandparent->color = RED;
					if (grandparent->data != _root->data)
						k = grandparent;
					else 
						break;
				}
					else if (k == grandparent->left->right) {
					   leftRotate(k->parent);
				}
				else 
				{
					k->parent->color = BLACK;
					grandparent->color = RED;
					rightRotate(grandparent);
					if (grandparent->data != _root->data)
						k = grandparent;
					else { break; }
				}
			}
			else 
			{
				if (grandparent->left)
					uncle = grandparent->left;
				if (uncle->color == RED)
				{
					k->parent->color = BLACK;
					uncle->color = BLACK;
					grandparent->color = RED;
					if (grandparent->data != _root->data)
						k = grandparent;
					else 
						break;
				}
				else if (k == grandparent->right->left)
					rightRotate(k->parent);
				else 
				{
					k->parent->color = BLACK;
					grandparent->color = RED;
					leftRotate(grandparent);
					if (grandparent->data != _root->data)
						k = grandparent;
					else
						break;
				}
			}
		}
		_root->color = BLACK;

		//Works but is too slow
		/*NodePtr u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u->color == 1) {
					// case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {
						// case 3.2.2
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right; // uncle

				if (u->color == 1) {
					// mirror case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->right) {
						// mirror case 3.2.2
						k = k->parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == _root) {
				break;
			}
		}
		_root->color = 0;*/
	}

	void printHelper(NodePtr root, std::string indent, bool last) 
	{
		if (root != TNULL) {
		std::cout << indent;
		if (last) {
			std::cout << "R----";
			indent += "   ";
		} else {
			std::cout << "L----";
			indent += "|  ";
		}

		std::string sColor = root->color ? "RED" : "BLACK";
		std::cout << root->data << "(" << sColor << ")" << std::endl;
		printHelper(root->left, indent, false);
		printHelper(root->right, indent, true);
		}
  }


	public:
		RedBlackTree()
		{
			TNULL = new Node;
			TNULL->color = BLACK;
			TNULL->left = NULL;
			TNULL->right = NULL;
			_root = TNULL;
		};

		~RedBlackTree() { };

		void preorder() 
		{
			preOrderHelper(this->_root);
		}

		void inorder() 
		{
			inOrderHelper(this->_root);
		}

		void postorder() 
		{
			postOrderHelper(this->_root);
		}

		NodePtr searchTree(int k) 
		{
			return searchTreeHelper(this->_root, k);
			/*NodePtr tmp = getRoot();
			if (tmp == NULL)
				return NULL;
			while(tmp)
			{
				if (k == tmp->data)
					return tmp;
				else if ( k < tmp->data)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return NULL;*/
		}

		NodePtr minimum( NodePtr node )
		{
			while(node->left != TNULL)
				node = node->left;
			return node;
		}

		NodePtr maximum( NodePtr node )
		{
			while(node->right != TNULL)
				node = node->right;
			return node;
		}

		NodePtr successor( NodePtr x )
		{
			if (x->right != TNULL)
				return minimum(x->right);
			
			NodePtr y = x->parent;
			while(y != TNULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		NodePtr predecessor( NodePtr x )
		{
			if (x->left != TNULL)
				return minimum(x->left);
			
			NodePtr y = x->parent;
			while(y != TNULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		void leftRotate( NodePtr x )
		{
			/*NodePtr y = x->right;
			x->right = y->left;
			if(y->left != TNULL)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				_root = y;
			else if(x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;*/
			Node* nw_node = new Node();
            if(x->right->left) { nw_node->right = x->right->left; }
            nw_node->left = x->left;
            nw_node->data = x->data;
            nw_node->color = x->color;
            x->data = x->right->data;

            x->left = nw_node;
            if(nw_node->left){ nw_node->left->parent = nw_node; }
            if(nw_node->right){ nw_node->right->parent = nw_node; }
            nw_node->parent = x;

            if(x->right->right){ x->right = x->right->right; }
            else { x->right = nullptr; }

            if(x->right){ x->right->parent = x; }
		}

		void rightRotate( NodePtr x )
		{
			/*NodePtr y = x->left;
			x->left = y->right;
			if(y->right != TNULL)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				_root = y;
			else if(x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;*/

			Node* nw_node = new Node();
            if(x->left->right){ nw_node->left = x->left->right; }
            nw_node->right = x->right;
            nw_node->data = x->data;
            nw_node->color = x->color;

            x->data = x->left->data;
            x->color = x->left->color;

            x->right = nw_node;
            if(nw_node->left){ nw_node->left->parent = nw_node; }
            if(nw_node->right){ nw_node->right->parent = nw_node; }
            nw_node->parent = x;

            if(x->left->left){ x->left = x->left->left; }
            else { x->left = nullptr; }

            if(x->left){ x->left->parent = x; }
		}

		void insert( int key )
		{
			NodePtr node = new Node;
			node->parent = NULL;
			node->data = key;
			node->left = TNULL;
			node->right = TNULL;
			node->color = RED;

			NodePtr y = NULL;
			NodePtr x = _root;

			while(x != TNULL)
			{
				y = x;
				if (node->data < x->data)
					x = x->left;
				else
					x = x->right;
			}

			node->parent = y;
			if (y == NULL)
				_root = node;
			else if (node->data < y->data)
				y->left = node;
			else
				y->right = node;

			if (node->parent == NULL)
			{
				node->color = BLACK;
				return ;
			}
			if (node->parent->parent == NULL)
				return;
			insertFix(node);
		}

		NodePtr getRoot()
		{ return this->_root; }

		void deleteNode( int data )
		{ deleteNodeHelper(_root, data); }

		void printTree()
		{
			if (_root)
				printHelper(_root, "", true);
		}

};

int main() {
	RedBlackTree bst;
	bst.insert(55);
	bst.insert(40);
	bst.insert(65);
	bst.insert(60);
	bst.insert(75);
	bst.insert(57);
	bst.insert(20);
	bst.insert(62);

	bst.printTree();
	std::cout << std::endl
		<< "After deleting" << std::endl;
	bst.deleteNode(40);
	bst.deleteNode(60);
  
	for (int i = 0; i < 22; i++)
		bst.insert(i);
std::cout << "Done" <<std::endl;

	/*for (int i = 0; i < 1000000; i++)
		bst.deleteNode(i);*/
	bst.printTree();
	//std::cout << bst.searchTree(62)->data <<std::endl;
}