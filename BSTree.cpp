
#include "BSTree.h"
#include <algorithm>

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::copyTree(const BSTree<DataType, KeyType> &otherTree)
{
	copyTreeHelper(root, otherTree.root);
}
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::copyTreeHelper(BSTreeNode *&p, const BSTreeNode *otherPtr)
{
	if (p != 0)
	{
		p = new BSTreeNode(otherPtr->dataItem, 0, 0);
		copyTreeHelper(p->left, otherPtr->left)
			copyTreeHelper(p->right, otherPtr->right);
	}

}

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
{
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ()
{
	root = NULL;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ( const BSTree<DataType,KeyType>& other )
{
	*this = other;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>:: operator= ( const BSTree<DataType,KeyType>& other )
{
	if (*this == &other)
		return *this;
	clear();
	copyTreeHelper(root, other.root);
	return *this;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree ()
{
	clearHelper(root);
}

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode * &p)
{
	if (p != nullptr)
	{
		clearHelper(p->left);
		clearHelper(p->right);
		delete p;
	}
	p = nullptr;
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem )
{
	insertHelper(root, newDataItem);
}


template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode *&p, const DataType &newDataItem)
{
	if (p == nullptr)
		p = new BSTreeNode{ newDataItem, nullptr, nullptr };
	else if (newDataItem.getKey() < p->dataItem.getKey())
	{
		insertHelper(p->left,newDataItem);
	}
	else if (newDataItem.getKey() > p->dataItem.getKey())
	{
		insertHelper(p->right,newDataItem);
	}
	else; //duplicate, do nothing
}


template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const
{

	return retrieveHelper(root,searchKey, searchDataItem);

}


template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode *p, const KeyType& searchKey, DataType &searchDataItem) const
{
	if (p == nullptr)
		return false;
	else if (searchKey < p->dataItem.getKey())
		return retrieveHelper(p->left, searchKey, searchDataItem);
	else if (searchKey > p->dataItem.getKey())
		return retrieveHelper(p->right, searchKey, searchDataItem);
	else
	{
		searchDataItem = p->dataItem;
		return true; //match
	}

}


template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey )
{

	return removeHelper(root, deleteKey);
}
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode *&p, const KeyType& deleteKey)
{
	if (p == nullptr)
		return false;
	else if (deleteKey < p->dataItem.getKey())
	{
		return removeHelper(p->left, deleteKey);
	}
	else if (deleteKey > p->dataItem.getKey())
	{
		return removeHelper(p->right, deleteKey);
	}
	else{
		BSTreeNode *oldNode = p;
		if (p->left == nullptr)
			p = p->right;
		else if (p->right == nullptr)
			p = p->left;
		else
			cutRightmost(p->left, oldNode);
		delete oldNode;
		return true;
	}

}


template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::cutRightmost(BSTreeNode *&r, BSTreeNode *&delPtr)
{
	if (r->right != nullptr)
		cutRightmost(r->right, delPtr);
	else
	{
		delPtr->dataItem = r->dataItem;
		delPtr = r;
		r = r->left;
	}
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys () const
{
	writeKeysHelper(root);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode *p) const
{
	if (p != nullptr)
	{
		
		writeKeysHelper(p->left);
		cout << p->dataItem.getKey() << " "; //line separated by spaces
		writeKeysHelper(p->right);
	}
	return;
}


template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear ()
{
	clearHelper(root);
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty () const
{
	return (root == nullptr);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight () const
{
	return getHeightHelper(root);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode *p) const
{
	if (p != nullptr)
	{
		return max(getHeightHelper(p->left), getHeightHelper(p->right)) + 1;
	}
	else
		return 0;
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount () const
{
	return getCountHelper(root);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode *p) const
{
	if (p == nullptr)
		return 0;
	else
		return 1 + getCountHelper(p->left) + getCountHelper(p->right);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLessThan ( const KeyType& searchKey ) const
{
	writeLTHelper(root, searchKey);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLTHelper(BSTreeNode *p, const KeyType& searchKey) const
{
	if (p == nullptr)
		return; 
		writeLTHelper(p->left, searchKey);
    if (p->dataItem.getKey() < searchKey)
	{
		cout << p->dataItem.getKey() << " ";
		writeLTHelper(p->right, searchKey);
	}
}

#include "show9.cpp"