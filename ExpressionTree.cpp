
#include "ExpressionTree.h"

template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode ( char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr )
{
	dataItem = elem;
	left = leftPtr;
	right = rightPtr;
}

template <typename DataType>
ExprTree<DataType>::ExprTree ()
{
	root = 0;
}

template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
	copyHelper(root, source.root);
}

template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source)
{
	clearHelper(root);
	copyHelper(root, source.root);
}


template <typename DataType>
void ExprTree<DataType>::copyHelper(ExprTreeNode *&p, const ExprTreeNode *source)
{

	if (source != 0)
	{
		p = new ExprTreeNode(source->dataItem, 0, 0);
		copyHelper(p->left, source->left);
		copyHelper(p->right, source->right);
	}

}
template <typename DataType>
ExprTree<DataType>::~ExprTree ()
{
	clearHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::build ()
{
	buildHelper(root);
}

template<typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode*& p)
{
	char op;
	cin >> op;
	p = new ExprTreeNode(op, NULL, NULL); //p is the character entered

	//operator? recursively call
		if (!isdigit(op))
		{
			buildHelper(p->left); //call left
			buildHelper(p->right); //call right
		}

}


template <typename DataType>
void ExprTree<DataType>::expression () const
{
	exprHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::exprHelper(ExprTreeNode *p) const
{
	if (isdigit(p->dataItem))
	{
		cout << p->dataItem;
		return;
	}
	cout << '(';
	exprHelper(p->left);
	cout << p->dataItem;
	exprHelper(p->right);
	cout << ')';
}

template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
	if (root == nullptr)
		throw logic_error("It's empty");
	return evalHelper(root);
}

template <typename DataType>
DataType ExprTree<DataType>::evalHelper (ExprTreeNode *p) const
{
	switch (p->dataItem)
	{
	case '+': return (evalHelper(p->left) + evalHelper(p->right));
		break;
	case '-': return (evalHelper(p->left) - evalHelper(p->right));
		break;
	case '*': return (evalHelper(p->left) * evalHelper(p->right));
		break;
	case '/': return (evalHelper(p->left) / evalHelper(p->right));
		break;
	default:
		return (p->dataItem - '0');
		break;
	}

}
/*
template <>
float ExprTree<float>::evalHelper(ExprTreeNode* p) const
{

	float temp;
	return temp;
}

template <>
bool ExprTree<bool>::evalHelper(ExprTreeNode* p) const
{
	bool temp;
	return temp;
}
*/

template <typename DataType>
void ExprTree<DataType>::clear ()
{
	clearHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode *&p)
{
	if (p != nullptr)
	{
		clearHelper(p->left);
		clearHelper(p->right);
		delete p;
		p = 0;
	}
}

template <typename DataType>
void ExprTree<DataType>::commute()
{
	commuteHelper(root);
}


template <typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode* p)
{
	if (p == nullptr) return;
	if (!isdigit(p->dataItem))
	{
		ExprTreeNode *temp = p->left;
		p->left = p->right;
		p->right = temp;
	}
	commuteHelper(p->left);
	commuteHelper(p->right);
}

template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
	return isEquivalentHelper(root, source.root);
}

template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper(const ExprTreeNode* x,
	const ExprTreeNode* y) const
{
	if (x == nullptr && y == nullptr)
		return true;
	else if (x != nullptr && y != nullptr)
	{
		if (x->dataItem == y->dataItem)
		{
			if (isEquivalentHelper(x->left, y->left) && isEquivalentHelper(x->right, y->left))
			{
				if (x->dataItem == '+' || x->dataItem == '*')
					return true;
				else return false;
			}
			else
				return false;
		}
	}
	return false;
}

template <typename DataType>
bool ExprTree<DataType>::isEmpty() const
{
	return false;
}

template <typename DataType>
void ExprTree<DataType>::showStructure() const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

{
	// No isEmpty function in this class. Add a private one if you wish.
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showHelper(root, 1);
		cout << endl;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
void ExprTree<DataType>::showHelper(ExprTreeNode *p, int level) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
	int j;   // Loop counter

	if (p != 0)
	{
		showHelper(p->right, level + 1);        // Output right subtree
		for (j = 0; j < level; j++)   // Tab over to level
			cout << "\t";
		cout << " " << p->dataItem;        // Output dataItem
		if ((p->left != 0) &&          // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1);         // Output left subtree
	}
}