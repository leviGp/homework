/*Functions to add a node to a binary search tree as well as
an in order function to either do something with data or with a slight
modification  can delete tree*/


#include <iostream>


using namespace std;


node * insert(node * &root, int data)
{
	if (root == NULL)
	{
		//create new node for tree
		root = new(node);
		root->data = data;
		root->left = root->right = NULL;
	}
	else
	{
		//If the data is less than the data currently in root push it left.
		if (data < root->data)
		{
			root->left = insert(root->left, data, counter);

		}
		//if the data is greater than the data in current root, it will be
		//placed in the right
		else if (data > root->data)
		{
			root->right = insert(root->right, data, counter);
			
		}
		//if the data is equal to the data at current root, push it left.
		else if (data == root->data)
		{
			root->left = insert(root->left, data, counter);
			
		}
	}
	return root;
}

void inOrder(node *&root, ofstream&outFile)
{
	//print tree to file.
	if (root)
	{
		inOrder(root->left, outFile);
		outFile << root->data << "\t" << endl;
		cout << root->data << "\t" <<  endl;
		inOrder(root->right, outFile);

	}
}