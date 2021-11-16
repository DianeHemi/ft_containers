//https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp
//https://gist.github.com/SubCoder1/70c2cedc44353ffc539c7567b1051028

#include <iostream>
#include <string>

#define BLACK   0
#define RED     1

namespace ft
{
	/****
	 * Structure
	****/
	template <class T>
	struct Node
	{
		int color;
		T data;   //Holds the key

		Node*   parent;	//Except root node
		Node*   left;	//left child
		Node*   right;	//right child
	};


	/****
	 * RBTree
	****/
	template <class T>
	class RedBlackTree
	{
		public:
			typedef Node<T> *NodePtr;
			typedef T value_type;;

		/****
		 * Constructor
		****/
			RedBlackTree()
			{
				_root = NULL;
			};

			~RedBlackTree() { };


		/****
		 * Members
		****/
		private:
			NodePtr	_root;

		/****
		 * Printing
		****/
			void printHelper(NodePtr root, std::string indent, bool last) 
			{
				if (root) {
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

		/****
			 * Deletion
		****/
			void deleteFix( NodePtr z )
			{
				while(z->data != _root->data && z->color == BLACK) {
                auto sibling = getRoot();
                if(z->parent->left == z) {
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
                        if(!sibling->left && !sibling->right) {
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
                            z = _root;
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
                             if(!sibling->left && !sibling->right) {
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
                                z = _root;
                            }
                        } 
                    }

                }
            }
            z->color = BLACK;
			}

			void rbTransplant( NodePtr node1, NodePtr node2 )
			{
				if (!node1->parent)
					_root = node2;
				else if ( node1 == node1->parent->left )
					node1->parent->left = node2;
				else
					node1->parent->right = node2;
				node2->parent = node1->parent;
			}

			void deleteNodeHelper( NodePtr parent, NodePtr curr, value_type stuff )
			{
				//Search for key
				//Should compare to know if search go right or left ?

				if(!curr) { return; }
				if(curr->data == stuff) {
					//CASE -- 1
					if(!curr->left && !curr->right) {
						if(parent->data == curr->data){ _root = NULL; }
						else if(parent->right == curr) {
							deleteFix(curr);
							parent->right = NULL;
						} 
						else { 
							deleteFix(curr);
							parent->left = NULL;
						}
					}
					//CASE -- 2
					else if(curr->left && !curr->right) {
						int swap = curr->data;
						curr->data = curr->left->data;
						curr->left->data = swap;
						deleteNodeHelper(curr, curr->right, stuff);
					}
					else if(!curr->left && curr->right) {
						int swap = curr->data;
						curr->data = curr->right->data;
						curr->right->data = swap;
						deleteNodeHelper(curr, curr->right, stuff);
					}
					//CASE -- 3
					else {
						bool flag = false;
						NodePtr temp = curr->right;
						while(temp->left) { flag = true; parent = temp; temp = temp->left; }
						if(!flag) { parent = curr; }
						int swap = curr->data;
						curr->data = temp->data;
						temp->data = swap;
						deleteNodeHelper(parent, temp, swap);
					}
				}
			}


		/****
			 * Insertion
		****/
			void insertFix( NodePtr node )
			{
				while(node->parent->color == RED) 
				{
					NodePtr grandparent = node->parent->parent;
					NodePtr uncle = getRoot();
					if(node->parent == grandparent->left) 
					{
						if (grandparent->right)
							uncle = grandparent->right;
						if (uncle->color == RED)
						{
							node->parent->color = BLACK;
							uncle->color = BLACK;
							grandparent->color = RED;
							if (grandparent->data != _root->data)
								node = grandparent;
							else 
								break;
						}
							else if (node == grandparent->left->right) {
							leftRotate(node->parent);
						}
						else 
						{
							node->parent->color = BLACK;
							grandparent->color = RED;
							rightRotate(grandparent);
							if (grandparent->data != _root->data)
								node = grandparent;
							else 
								break;
						}
					}
					else
					{
						if (grandparent->left != NULL)
							uncle = grandparent->left;
						if (uncle->color == RED)
						{
							node->parent->color = BLACK;
							uncle->color = BLACK;
							grandparent->color = RED;
							if (grandparent->data != _root->data)
								node = grandparent;
							else 
								break;
						}
						else if (node == grandparent->right->left)
							rightRotate(node->parent);
						else 
						{
							node->parent->color = BLACK;
							grandparent->color = RED;
							leftRotate(grandparent);
							if (grandparent->data != _root->data)
								node = grandparent;
							else
								break;
						}
					}
				}
				_root->color = BLACK;
			}


		public:
			/****
			 * Helpers - Root - Search - Min and max
			****/
			NodePtr getRoot() { return this->_root; }

			NodePtr searchTree(value_type key) 
			{
				NodePtr temp = getRoot();
				if(!temp) 
					return NULL;

				while(temp) {
					if (key == temp->data)
						return temp;
					else if (key < temp->data)
						temp = temp->left;
					else 
						temp = temp->right;
				}
				return NULL;
			}

			NodePtr minimum( NodePtr node ) //Node at the utter left
			{
				while(node->left)
					node = node->left;
				return node;
			}

			NodePtr maximum( NodePtr node ) //Node at the utter right
			{
				while(node->right)
					node = node->right;
				return node;
			}

			NodePtr successor( NodePtr node )
			{
				if (node->right)
					return minimum(node->right);
				
				NodePtr parent = node->parent;
				while(parent && node == parent->right)
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}

			NodePtr predecessor( NodePtr node )
			{
				if (node->left)
					return minimum(node->left);
				
				NodePtr parent = node->parent;
				while(parent && node == parent->left)
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}

		/****
			 * Rotations
		****/
			void leftRotate( NodePtr node )
			{
				Node<T>* nw_node = new Node<T>();
				if(node->right->left)
					nw_node->right = node->right->left;
				nw_node->left = node->left;
				nw_node->data = node->data;
				nw_node->color = node->color;
				node->data = node->right->data;

				node->left = nw_node;
				if(nw_node->left)
					nw_node->left->parent = nw_node;
				if(nw_node->right)
					nw_node->right->parent = nw_node;
				nw_node->parent = node;

				if(node->right->right)
					node->right = node->right->right;
				else 
					node->right = NULL;

				if(node->right)
					node->right->parent = node;
			}

			void rightRotate( NodePtr node )
			{
				Node<T>* nw_node = new Node<T>();
				if(node->left->right)
					nw_node->left = node->left->right;
				nw_node->right = node->right;
				nw_node->data = node->data;
				nw_node->color = node->color;

				node->data = node->left->data;
				node->color = node->left->color;

				node->right = nw_node;
				if(nw_node->left)
					nw_node->left->parent = nw_node;
				if(nw_node->right)
					nw_node->right->parent = nw_node;
				nw_node->parent = node;

				if(node->left->left)
					node->left = node->left->left;
				else
					node->left = NULL;

				if(node->left)
					node->left->parent = node;
			}


		/****
			 * Insertion
		****/
			NodePtr createNewNode( value_type key )
			{
				NodePtr node = new Node<T>;
				node->parent = NULL;
				node->data = key;
				node->left = NULL;
				node->right = NULL;
				node->color = RED;
				return node;
			}

			void insert( value_type key )
			{
				if(!_root)
				{
					_root = new Node<T>();
					_root->data = key;
					_root->parent = NULL;
					_root->left = NULL;
					_root->right = NULL;
					_root->color = BLACK;
				}
				else 
				{
					NodePtr linker = getRoot();
					NodePtr newnode = new Node<T>();
					newnode->data = key;
					while (linker != NULL)
					{
						if (linker->data > key)
						{
							if(linker->left == NULL)
							{
								linker->left = newnode;
								newnode->color = RED;
								newnode->parent = linker;
								break;
							}
							else 
								linker = linker->left;
						} 
						else 
						{
							if (linker->right == NULL)
							{
								linker->right = newnode;
								newnode->color = RED;
								newnode->parent = linker;
								break; 
							}
							else
								linker = linker->right;
						}
					}
					insertFix(newnode);
				}
			}

		/****
			 * Deletion
		****/
			void deleteNode( value_type data )
			{ 
				NodePtr temp = _root;
				NodePtr parent = temp;
				deleteNodeHelper(parent, temp, data); }


		/****
			 * Printing
		****/
			void printTree()
			{
				if (_root)
					printHelper(_root, "", true);
			}

	};
}




#include <map>
int main() {
	ft::RedBlackTree<int> bst;
	bst.insert(55);
	bst.insert(40);
	
	bst.insert(65);
	bst.insert(60);
	bst.insert(75);
	bst.insert(57);
	bst.insert(20);
	bst.insert(62);

	bst.deleteNode(40);
	bst.deleteNode(0);
	bst.printTree();
  	/*for (int i = 0; i < 1000000; i++)
		bst.insert(i);
	std::cout << "Done" <<std::endl;

	for (int i = 0; i < 1000000; i++)
		bst.deleteNode(i);*/
}