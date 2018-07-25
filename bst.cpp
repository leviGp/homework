/*Levi Pflepsen
DUE: July 18th 2018
Mr. Walley
Data Structures


This program will ask the user for a file name, then you will create a BST from the data
within the file, the first number will be the root, then it will be determined by less than or
greater than.  Print the tree to "tree.txt" in order lowest to highest and what level of the 
tree the data is on.*/

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct node
{
	int counter;
	int data;
	struct node *left;
	struct node *right;
};

void openFile(fstream &);
void fillTree(struct node *&, fstream &, int );
struct node *insert(struct node *&root, int data, int );
void writeInorder(struct node *&, ofstream &, int &);
void deleteInorder(struct node *&);

int main()
{
	int counter = 0;
	fstream inFile;
	struct node *root = NULL;
	//opening file to read from
	openFile(inFile);
	//filling the tree, with insert function nested
	fillTree(root, inFile, counter);
	ofstream outFile;
	
	
	//creating an outFile named tree.txt
	string fileName = "tree";
	fileName = fileName + "." + "txt";
	outFile.open(fileName);
	if (!outFile)
	{
		cout << "File to write to could not be opened" << endl;
	}
	
	//function to write to a file in order.
	cout << "Data:" << "\t" << "Tree Level" << endl;
	writeInorder(root, outFile, counter);



	system("pause");
	return (0);
}

void openFile(fstream &inFile)
{
	string fileName;

	//Ask the user for the file name.
	cout << "Please enter the file name..." << endl;
	cin >> fileName;

	//open the file with the string variable
	inFile.open(fileName.c_str());

	//check to make sure file as opened properly
	while (!inFile)
	{
		cout << "Your file could not be opened" << endl;
		system("pause");
		cout << "********************************************" << endl;
		cout << "Re-enter a file name" << endl;
		cin >> fileName;
		inFile.open(fileName.c_str());

	}
}

void fillTree(node *&root, fstream &inFile, int counter)
{
	int num = 0;
	//while loop to read until the end of file
	while (!inFile.eof())
	{
		inFile >> num;
		//check to make sure good data is being read in
		if (inFile.fail() || num < 0 || num > 99)
		{
			inFile.clear();
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			//send num through insert function to fill the tree.
			insert(root, num, counter);
		}
		
	}
}

node * insert(node * &root, int data, int counter)
{
	if (root == NULL)
	{
		//create new node for tree
		root = new(node);
		//putting data into the node and setting the pointers 
		//left and right to NULL
		root->data = data;
		root->left = root->right = NULL;
		root->counter = counter;
		
	}
	else
	{
		//If the data is less than the data currently in root push it left.
		if (data < root->data)
		{
			counter++;
			root->left = insert(root->left, data, counter);
			
			
		}
		//if the data is greater than the data in current root, it will be
		//placed in the right
		else if (data > root->data)
		{
			counter++;
			root->right = insert(root->right, data, counter);

			
			
		}
		//if the data is equal to the data at current root, push it left.
		else if (data == root->data)
		{
			counter++;
			root->left = insert(root->left, data, counter);
			
		}
	}
	return root;
}

void writeInorder(node *&root, ofstream&outFile, int &counter)
{
	//print tree to file.
	if (root)
	{
		writeInorder(root->left, outFile, counter);
		outFile << root->data << "\t" << root->counter << endl;
		cout << root->data << "\t" << root->counter << endl;
		writeInorder(root->right, outFile, counter);

	}
}

void deleteInorder(node *&root)
{
	struct node *temp;
	temp = root;
	if (root)
	{
		deleteInorder(root->left);
		delete(temp);
		temp = root;
		deleteInorder(root->right);

	}
}


