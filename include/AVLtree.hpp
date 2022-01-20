#include "iterator_traits.hpp"
#include "other.hpp"
#include <algorithm>
#include <functional>
#include <memory>

namespace ft {

template <typename T, typename Compare = std::less<T> /**/>
class AVLTree;

template <typename T, typename Node, typename Compare = std::less<T> /**/>
class AVLTreeIterator {

  public:
	typedef size_t						   size_type;
	typedef ptrdiff_t					   difference_type;
	typedef T							   value_type;
	typedef T*							   pointer;
	typedef T&							   reference;
	typedef ft::bidirectional_iterator_tag iterator_category;

  public:
	AVLTreeIterator(const AVLTreeIterator& other) : _n(other._n) {}

	AVLTreeIterator() {}
	~AVLTreeIterator() {}

	AVLTreeIterator& operator=(const AVLTreeIterator& other) {
		_n = other._n;
		return *this;
	}

	AVLTreeIterator& operator++() {
		if (_n->right) {
			_n = _n->right;
			while (_n->left)
				_n = _n->left;
		} else {
			Node* tmp;
			do {
				tmp = _n;
				_n = _n->parent;
			} while (_n && tmp == _n->right);
		}
		return *this;
	}

	AVLTreeIterator operator++(int) {
		AVLTreeIterator cpy = *this;
		//
		operator++();
		return cpy;
	}

	AVLTreeIterator& operator--() {
		if (_n->left) {
			_n = _n->left;
			while (_n && _n->right)
				_n = _n->right;
		} else {
			Node* tmp;
			do {
				tmp = _n;
				_n = _n->parent;
			} while (_n && tmp == _n->left);
		}
		return *this;
	}

	AVLTreeIterator operator--(int) {
		AVLTreeIterator cpy = *this;
		//
		operator--();
		return cpy;
	}

	reference operator*() const { return _n->el; }

	pointer	  operator->() const { return &_n->el; }

	template <typename T2, typename _Compare, typename Node2>
	friend bool operator==(const AVLTreeIterator<T2, _Compare, Node2>& lhs, const AVLTreeIterator<T2, _Compare, Node2>& rhs);

	template <typename T2, typename _Compare>
	friend class AVLTree;

  private:
	Node* _n;
	AVLTreeIterator(Node* n) : _n(n) {}
};

template <typename E, typename Compare, typename Node>
bool operator==(const AVLTreeIterator<E, Compare, Node>& lhs, const AVLTreeIterator<E, Compare, Node>& rhs) {
	return lhs._n == rhs._n;
}

template <typename E, typename Compare, typename Node>
bool operator!=(const AVLTreeIterator<E, Compare, Node>& lhs, const AVLTreeIterator<E, Compare, Node>& rhs) {
	return !(lhs == rhs);
}

template <typename T>
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

	T	  key;
	Node* left;
	Node* right;
	int	  height;
};

template <typename T, typename Compare = std::less<T> /**/>
class AVLtree {
  public:
	typedef T												 value_type;
	typedef Compare											 compare;
	typedef AVLTreeIterator<T, Node<T>, compare>			 iterator;
	typedef AVLTreeIterator<const T, const Node<T>, compare> const_iterator;
	typedef ptrdiff_t										 difference_type;
	typedef size_t											 size_type;
	// typedef ReverseIterator<iterator>				   reverse_iterator;
	// typedef ReverseIterator<const_iterator>			   const_reverse_iterator;

	AVLtree() : _root(NULL){};
	~AVLtree() {
		_deleteAllNodes(_root);
	};

	void insertNode(int key) {
		_root = _insertNode(_root, key);
	}

	void deleteNode(int key) {
		_root = _deleteNode(_root, key);
	}

	Node<T>* _root;

  private:
	Node<T>* _insertNode(Node<T>* n, int key) {
		if (!n)
			return new Node<T>(key);
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

	Node<T>* _mostLeftNode(Node<T>* n) {
		Node<T>* current = n;
		while (current->left)
			current = current->left;
		return current;
	}

	Node<T>* _deleteNode(Node<T>* n, int key) {
		if (!n)
			return NULL;
		if (key < n->key)
			n->left = _deleteNode(n->left, key);
		else if (key > n->key)
			n->right = _deleteNode(n->right, key);
		else if (n->left && n->right) {
			Node<T>* left = _mostLeftNode(n->right);
			n->key = left->key;
			n->right = _deleteNode(n->right, n->key);
		} else {
			Node<T>* cpy = n;
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

	void _deleteAllNodes(Node<T>* _n) {
		if (!_n)
			return;
		if (_n->left)
			_deleteAllNodes(_n->left);
		if (_n->right)
			_deleteAllNodes(_n->right);
		delete _n;
	}

	Node<T>* _rightRotate(Node<T>* y) {
		Node<T>* x = y->left;
		Node<T>* T2 = x->right;
		x->right = y;
		y->left = T2;
		x->updateHeight();
		y->updateHeight();
		return x;
	}

	Node<T>* _leftRotate(Node<T>* x) {
		Node<T>* y = x->right;
		Node<T>* T2 = y->left;
		y->left = x;
		x->right = T2;
		y->updateHeight();
		x->updateHeight();
		return y;
	}

	int _balanceFactor(Node<T>* n) {
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

} // namespace ft
