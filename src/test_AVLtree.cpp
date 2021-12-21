#include "AVLtree.hpp"
#include <iostream>

void printTree(Node* root, std::string indent, bool last) {
	if (root) {
		std::cout << indent;
		if (last) {
			std::cout << "R----";
			indent += "   ";
		} else {
			std::cout << "L----";
			indent += "|  ";
		}
		std::cout << root->key << std::endl;
		printTree(root->left, indent, false);
		printTree(root->right, indent, true);
	}
}

void test_AVLtree() {
	AVLtree tree;
	tree.insertNode(33);
	tree.insertNode(13);
	tree.insertNode(53);
	tree.insertNode(9);
	tree.insertNode(21);
	tree.insertNode(61);
	tree.insertNode(8);
	tree.insertNode(11);
	printTree(tree._root, "", true);
	tree.deleteNode(13);
	std::cout << "After deleting " << std::endl;
	printTree(tree._root, "", true);
}
