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

class RedBlackTree
{
	public:
		typedef Node *NodePtr;

		/****
		 * Constructor
		****/
		RedBlackTree()
		{
			TNULL = new Node;
			TNULL->color = BLACK;
			TNULL->left = NULL;
			TNULL->right = NULL;
			_root = TNULL;
		};

		~RedBlackTree() { };


	/****
		 * Members
	****/
	private:
		NodePtr	_root;
		NodePtr	TNULL;


	/****
		 * Helpers
	****/
		NodePtr searchTreeHelper( NodePtr node, int key )
		{
			if (node == TNULL || key == node->data)
				return node;
			if (key < node->data)
				return searchTreeHelper(node->left, key);
			return searchTreeHelper(node->right, key);
		}


	/****
		 * Deletion
	****/
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
				return;

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

	/****
		 * Insertion
	****/
		void insertFix( NodePtr k )
		{
			NodePtr u;

			while(k->parent->color == RED)
			{
				if (k->parent == k->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == RED)
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							rightRotate(k);
						}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					leftRotate(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;
					if (u->color == RED)
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else{
						if (k == k->parent->right)
						{
							k = k->parent;
							leftRotate(k);
						}
						k->parent->color= BLACK;
						k->parent->parent->color = RED;
						rightRotate(k->parent->parent);
					}
				}
				if (k == _root)
					break ;
			}
			_root->color = BLACK;
		}


	public:
		/****
		 * Helpers - Root - Search - Min and max
		****/
		NodePtr getRoot()
		{ return this->_root; }

		NodePtr searchTree(int k) 
		{
			//return searchTreeHelper(this->_root, k);
			NodePtr tmp = getRoot();
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
		}

		NodePtr minimum( NodePtr node ) //Node at the utter left
		{
			while(node->left != TNULL)
				node = node->left;
			return node;
		}

		NodePtr maximum( NodePtr node ) //Node at the utter right
		{
			while(node->right != TNULL)
				node = node->right;
			return node;
		}

		/*NodePtr successor( NodePtr x )
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
		}*/

	/****
		 * Rotations
	****/
		void leftRotate( NodePtr x )
		{
			NodePtr y = x->right;
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
			x->parent = y;
		}

		void rightRotate( NodePtr x )
		{
			NodePtr y = x->left;
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
			x->parent = y;
		}


	/****
		 * Insertion
	****/
		NodePtr createNewNode( int key )
		{
			NodePtr node = new Node;
			node->parent = NULL;
			node->data = key;
			node->left = TNULL;
			node->right = TNULL;
			node->color = RED;
			return node;
		}

		void insert( int key )
		{
			NodePtr node = createNewNode(key);
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
				return ;
			insertFix(node);
		}

	/****
		 * Deletion
	****/
		void deleteNode( int data )
		{ deleteNodeHelper(_root, data); }

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

  bst.deleteNode(40);
  bst.deleteNode(60);

}