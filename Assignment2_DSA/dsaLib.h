/*
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : Library for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */

#ifndef A02_DSALIB_H
#define A02_DSALIB_H

#include <string>
#include <math.h>
#include <vector>

using namespace std;
#define AVL_USE_HEIGHT
class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
class List {
public:
    virtual void    clean() = 0;
    virtual void    clone(void*) = 0;
    virtual bool    isEmpty() = 0;
    virtual size_t  getSize() = 0;
    virtual T&      at(int i) = 0;
    virtual T&      operator[](int i) = 0;

    virtual bool    find(T& a, int& idx) = 0;
    virtual T*      find(T& a) = 0;
	//virtual T*      find(T& a, function<bool(T&, T&)> eqCmp);
	virtual int     insert(int i, T& a) = 0;
    virtual int     insert(int i, T&& a) = 0;
    virtual int     remove(int i) = 0;
    //virtual int     remove(T& a, function<bool (T&, T&)> eqCmp) = 0;

    virtual int     push_back(T& a) = 0;
    virtual int     push_back(T&& a) = 0;
    virtual int     insertHead(T& a) = 0;
    virtual int     insertHead(T&& a) = 0;
    virtual int     removeHead() = 0;
    virtual int     removeLast() = 0;

    //virtual void    traverse(function<void (T&)> op) = 0;
    //virtual void    traverse(function<void (T&, void*)> op, void* pParam) = 0;

    virtual void    reverse() = 0;
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;

    L1Item(T &a) : data(a), pNext(NULL) {}
    L1Item(T &a, void* next) : data(a), pNext(next) {}
    L1Item(T &&a) : data(std::move(a)), pNext(NULL) {}
    L1Item(T &&a, void* next) : data(std::move(a)), pNext(next) {}
};

template <class T>
class L1List : public List<T> {
    L1Item<T>   *_pHead;
    size_t      _size;
public:
    L1List() : _pHead(NULL), _size(0) {}
	~L1List() {	clean();	}
	void clean() {
		L1Item<T>* temp = this->_pHead;
		while (temp != NULL) {
			temp = temp->pNext;
			this->removeHead();
		}
	}
	void    clone(void*) {};
    bool    isEmpty() { return _pHead == NULL; }
    size_t  getSize() { return _size; }
	L1Item<T>* getFirstPointer() {
		return this->_pHead;
	}
	L1Item<T>* getLastPointer() {
		L1Item<T> *p = this->_pHead;
		while (p->pNext != NULL) {
			p = p->pNext;
		}
		return p;
	}

	T&      at(int i) {
		//todo
		L1Item<T> *p = _pHead;
		if (i == 0) {
			return _pHead->data;
		}
		while (i > 0)
		{
			p = p->pNext;
			i--;
		}
		return p->data;
	};
	T&      operator[](int i) {
		//todo
		L1Item<T> *p = _pHead;
		if (i == 0) {
			return _pHead->data;
		}
		while (i > 0)
		{
			p = p->pNext;
			i--;
		}
		return p->data;
	};

	bool    find(T& a, int& idx) { return 1; };
	T*      find(T& a) { return &a; };
	//T*      find(T& a, std::function<bool(T&, T&)> eqCmp) {};//bool (*eqCmp)(T&, T&));
	int     insert(int i, T& a) { return 1; };
	int     insert(int i, T&& a) { return 1; };
	int     remove(int i) { return 1; };
	//int     remove(T& a, std::function<bool(T&, T&)> eqCmp) {};

    int     push_back(T& a);
    int     push_back(T&& a);
    int     insertHead(T& a);
    int     insertHead(T&& a);
    int     removeHead();
    int     removeLast();

	void    reverse() {
		L1Item<T> *curr = this->_pHead;
		L1Item<T> *prev = NULL;
		L1Item<T> *next = NULL;
		while (curr) {
			next = curr->pNext;
			curr->pNext = prev;
			prev = curr;
			curr = next;
		}
		this->_pHead = prev;
	}

   /* void    traverse(std::function<void (T&)> op) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }*/
    //void    traverse(void (*op)(T&, void*), void* pParam) {
   /* void    traverse(std::function<void (T&, void*)> op, void* pParam) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }*/
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(a);
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(a);
    }

    _size++;
    return 0;
}

template <class T>
int L1List<T>::push_back(T &&a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(std::move(a));
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(std::move(a));
    }

    _size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T>   *p = new L1Item<T>(a);
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

template <class T>
int L1List<T>::insertHead(T&& a) {
    L1Item<T>   *p = new L1Item<T>(std::move(a));
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if(_pHead) {
        L1Item<T>* p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if(_pHead) {
        if(_pHead->pNext) {
            L1Item<T>* prev = _pHead;
            L1Item<T>* pcur = prev->pNext;
            while(pcur->pNext) {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
        }
        else {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}

/************************************************************************
 * This section is for AVL tree
 ************************************************************************/
template <class T>
struct AVLNode {
    T           _data;
    AVLNode<T>   *_pLeft, *_pRight;
#ifdef AVL_USE_HEIGHT
    int         _height;
	AVLNode() :_data(0), _pLeft(NULL), _pRight(NULL), _height(1) {};
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _height(1) {}
#else
    int         _bFactor;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _bFactor(0) {}
#endif
};

template <class T>
class AVLTree {
    AVLNode<T> *_pRoot;
	int _size;
public:
    AVLTree() : _pRoot(NULL),_size(0) {}
    ~AVLTree() { destroy(_pRoot); }

	int getSize();
    bool find(T& key, T* &ret) { return find(_pRoot, key, ret); }
    bool insertx(T key) { return insertx(_pRoot, key); }
	bool inserty(T key) { return inserty(_pRoot, key); }
    bool remove(T& key) { return remove(_pRoot, key); }
    void traverseNLR(void (*op)(T&)) { traverseNLR(_pRoot, op); }
    void traverseLNR(void (*op)(T&)) { traverseLNR(_pRoot, op); }
    void traverseLRN(void (*op)(T&)) { traverseLRN(_pRoot, op); }

protected:
	int getMax2number(int a, int b) { return a > b ? a : b; }
	int getHeight(AVLNode<T>* pR);
	int getBalance(AVLNode<T>* pR);
    void destroy(AVLNode<T>* &pR);
    //bool find(AVLNode<T> *pR, T& key, T* &ret);
    bool insertx(AVLNode<T>* &pR, T& a);
	bool inserty(AVLNode<T>* &pR, T& a);
    //bool remove(AVLNode<T>* &pR, T& a);
    void traverseNLR(AVLNode<T> *pR, void (*op)(T&));
    void traverseLNR(AVLNode<T> *pR, void (*op)(T&));
    void traverseLRN(AVLNode<T> *pR, void (*op)(T&));

    void rotLeft(AVLNode<T>* &pR);
    void rotRight(AVLNode<T>* &pR);
    void rotLR(AVLNode<T>* &pR);
    void rotRL(AVLNode<T>* &pR);

    //bool balanceLeft(AVLNode<T>* &pR);// left.height > right.height
    //bool balanceRight(AVLNode<T>* &pR);// right.height > left.height
};

template<class T>
int AVLTree<T>::getSize(){
	return this->_size;
}

template<class T>
int AVLTree<T>::getHeight(AVLNode<T>* pR) { return pR ? pR->_height : 0; }

template<class T>
int AVLTree<T>::getBalance(AVLNode<T>* pR) { return getHeight(pR->_pLeft) - getHeight(pR->_pRight); }

template<class T>
void AVLTree<T>::destroy(AVLNode<T>*& pR) {
	if (pR == NULL) return;
	destroy(pR->_pLeft);
	destroy(pR->_pRight);
	delete pR;
	pR = NULL;
}

template<class T>
bool AVLTree<T>::insertx(AVLNode<T>*& pR, T & a) {
	if (pR == NULL) {
		pR = new AVLNode<T>(a);
		this->_size++;
		return true;
	}
	if (a.x < pR->_data.x) {
		insertx(pR->_pLeft, a);
	}
	else { insertx(pR->_pRight, a); }
	//
	pR->_height = 1 + getMax2number(getHeight(pR->_pLeft),getHeight(pR->_pRight));
	//
	int balance = getBalance(pR);
	if (balance > 1 && getBalance(pR->_pLeft) >= 0) { rotRight(pR); }
	if (balance < -1 && getBalance(pR->_pRight) <= 0) { rotLeft(pR); }
	if (balance > 1 && getBalance(pR->_pLeft) < 0) {
		rotLR(pR);
	}
	if (balance < -1 && getBalance(pR->_pRight) > 0) {
		rotRL(pR);
	}
}

template<class T>
bool AVLTree<T>::inserty(AVLNode<T>*& pR, T & a) {
	if (pR == NULL) {
		pR = new AVLNode<T>(a);
		this->_size++;
		return true;
	}
	if (a.y < pR->_data.y) {
		inserty(pR->_pLeft, a);
	}
	else { inserty(pR->_pRight, a); }
	//
	pR->_height = 1 + getMax2number(getHeight(pR->_pLeft), getHeight(pR->_pRight));
	//
	int balance = getBalance(pR);
	if (balance > 1 && getBalance(pR->_pLeft) >= 0) { rotRight(pR); }
	if (balance < -1 && getBalance(pR->_pRight) <= 0) { rotLeft(pR); }
	if (balance > 1 && getBalance(pR->_pLeft) < 0) {
		rotLR(pR);
	}
	if (balance < -1 && getBalance(pR->_pRight) > 0) {
		rotRL(pR);
	}
}

template<class T>
void AVLTree<T>::traverseNLR(AVLNode<T>* pR, void(*op)(T &)) {
	if (pR == NULL) return;
	op(pR->_data);
	traverseNLR(pR->_pLeft, op);
	traverseNLR(pR->_pRight, op);
}

template<class T>
void AVLTree<T>::traverseLNR(AVLNode<T>* pR, void(*op)(T &)) {
	if (pR == NULL) return;
	traverseLNR(pR->_pLeft, op);
	op(pR->_data);
	traverseLNR(pR->_pRight, op);
}

template<class T>
void AVLTree<T>::traverseLRN(AVLNode<T>* pR, void(*op)(T &)) {
	if (pR == NULL) return;
	traverseLNR(pR->_pLeft, op);
	traverseLNR(pR->_pRight, op);
	op(pR->_data);
}

template<class T>
void AVLTree<T>::rotLeft(AVLNode<T>*& pR) {
	AVLNode<T>* temp = pR->_pRight;
	pR->_pRight = temp->_pLeft;
	temp->_pLeft = pR;
	pR->_height -= 2;
	pR = temp;
}

template<class T>
void AVLTree<T>::rotRight(AVLNode<T>*& pR) {
	AVLNode<T>* temp = pR->_pLeft;
	pR->_pLeft = temp->_pRight;
	temp->_pRight = pR;
	pR->_height -= 2;
	pR = temp;
}

template<class T>
void AVLTree<T>::rotLR(AVLNode<T>*& pR) {
	//rotate left
	AVLNode<T>* temp = pR->_pLeft->_pRight;
	pR->_pLeft->_pRight = temp->_pLeft;
	temp->_pLeft = pR->_pLeft;
	//rotate right
	pR->_pLeft = temp->_pRight;
	temp->_pRight = pR;
	//update height
	temp->_pLeft->_height --;
	temp->_height++;
	pR->_height-=2;
	//
	pR = temp;
}

template<class T>
void AVLTree<T>::rotRL(AVLNode<T>*& pR) {
	//rotate right
	AVLNode<T>* temp = pR->_pRight->_pLeft;
	pR->_pRight->_pLeft = temp->_pRight;
	temp->_pRight = pR->_pRight;
	//rotate left
	pR->_pRight = temp->_pLeft;
	temp->_pLeft = pR;
	//update height
	pR->_height-=2;
	temp->_height++;
	temp->_pRight->_height--;
	//
	pR = temp;
}





#endif //A02_DSALIB_H

