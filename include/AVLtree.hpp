#include <algorithm>
#include <functional>

class Node {
  public:
	Node(int key)
		: key(key), left(NULL), right(NULL), height(1) {}
	Node(int key, Node* left, Node* right, int height)
		: key(key), left(left), right(right), height(height) {}

	void updateHeight() {
		int heightLeft = left ? left->height : 0;
		int heightRight = right ? right->height : 0;
		height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
	}

	int	  key;
	Node* left;
	Node* right;
	int	  height;
};

class AVLtree {
  public:
	AVLtree() : _root(NULL){};
	~AVLtree(){};

	void insertNode(int key) {
		_root = _insertNode(_root, key);
	}

	void deleteNode(int key) {
		_root = _deleteNode(_root, key);
	}

	Node* _root;

  private:
	Node* _insertNode(Node* n, int key) {
		if (!n)
			return new Node(key);
		if (key < n->key)
			n->left = _insertNode(n->left, key);
		else if (key > n->key)
			n->right = _insertNode(n->right, key);
		else
			return n;

		n->updateHeight();
		int balanceFactor = _balanceFactor(n);
		if (balanceFactor > 1) {
			if (key < n->left->key) {
				return _rightRotate(n);
			} else if (key > n->left->key) {
				n->left = _leftRotate(n->left);
				return _rightRotate(n);
			}
		}
		if (balanceFactor < -1) {
			if (key > n->right->key) {
				return _leftRotate(n);
			} else if (key < n->right->key) {
				n->right = _rightRotate(n->right);
				return _leftRotate(n);
			}
		}
		return n;
	}

	Node* _mostLeftNode(Node* n) {
		Node* current = n;
		while (current->left)
			current = current->left;
		return current;
	}

	Node* _deleteNode(Node* n, int key) {
		if (!n)
			return NULL;
		if (key < n->key)
			n->left = _deleteNode(n->left, key);
		else if (key > n->key)
			n->right = _deleteNode(n->right, key);
		else if (n->left && n->right) {
			Node* left = _mostLeftNode(n->right);
			n->key = left->key;
			n->right = _deleteNode(n->right, n->key);
		} else {
			Node* cpy = n;
			if (!n->left)
				n = n->right;
			else if (!n->right)
				n = n->left;
			delete cpy;
		}

		if (!n)
			return NULL;

		n->updateHeight();
		int balanceFactor = _balanceFactor(n);
		if (balanceFactor > 1) {
			if (_balanceFactor(n->left) >= 0) {
				return _rightRotate(n);
			} else {
				n->left = _leftRotate(n->left);
				return _rightRotate(n);
			}
		}
		if (balanceFactor < -1) {
			if (_balanceFactor(n->right) <= 0) {
				return _leftRotate(n);
			} else {
				n->right = _rightRotate(n->right);
				return _leftRotate(n);
			}
		}
		return n;
	}

	Node* _rightRotate(Node* y) {
		Node* x = y->left;
		Node* T2 = x->right;
		x->right = y;
		y->left = T2;
		x->updateHeight();
		y->updateHeight();
		return x;
	}

	Node* _leftRotate(Node* x) {
		Node* y = x->right;
		Node* T2 = y->left;
		y->left = x;
		x->right = T2;
		y->updateHeight();
		x->updateHeight();
		return y;
	}

	int _balanceFactor(Node* n) {
		if (!n)
			return 0;
		int heightLeft = n->left ? n->left->height : 0;
		int heightRight = n->right ? n->right->height : 0;
		return heightLeft - heightRight;
	}

	// disabled
	AVLtree& operator=(const AVLtree& cp);
	AVLtree(const AVLtree& cp);
};
