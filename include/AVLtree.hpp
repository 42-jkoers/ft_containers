#include <algorithm>
#include <functional>

class Node {
  public:
	Node(int key)
		: key(key), left(NULL), right(NULL), height(1) {}
	Node(int key, Node* left, Node* right, int height)
		: key(key), left(left), right(right), height(height) {}
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

		n->height = _maxHeight(n->left, n->right) + 1;
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

		n->height = _maxHeight(n->left, n->right) + 1;
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
		y->height = _maxHeight(y->left, y->right) + 1;
		x->height = _maxHeight(x->left, x->right) + 1;
		return x;
	}

	Node* _leftRotate(Node* x) {
		Node* y = x->right;
		Node* T2 = y->left;
		y->left = x;
		x->right = T2;
		x->height = _maxHeight(x->left, x->right) + 1;
		y->height = _maxHeight(y->left, y->right) + 1;
		return y;
	}

	int _balanceFactor(Node* n) {
		if (!n)
			return 0;
		int heightLeft = n->left ? n->left->height : 0;
		int heightRight = n->right ? n->right->height : 0;
		return heightLeft - heightRight;
	}

	int _maxHeight(Node* a, Node* b) {
		int heightA = a ? a->height : 0;
		int heightB = b ? b->height : 0;
		return heightA > heightB ? heightA : heightB;
	}

	// disabled
	AVLtree& operator=(const AVLtree& cp);
	AVLtree(const AVLtree& cp);
};
