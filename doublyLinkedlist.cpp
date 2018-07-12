/*Levi Pflepsen
Due: 7-9-18
Mr. Walley
CSC 307
Homework 4


This program reads a random set of numbers from a file into a doubly linked list.  It will then delete all even numbers
and print teh odd numbers that is left.
*/

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

//Creating a struct for the nodes of the linked list

struct node
{
	int element;
	node *next;
	node *previous;
};

//this function will prompt user to input a number
void getData(int&);
//This function will create and write how many the numbers the user wants
//with a random function.
void createFile(ofstream &, int);
//function to delete nodes with odd numbers
void deleteList(node *);
//function to print list
void printList(node *);
//populating doubly linked list
int readNormal(ifstream &, int num, node *);



int main()
{
	int num = 0;
	ofstream outFile;
	outFile.open("Numbers.txt");
	ifstream inFile;

	//get a number from the user
	getData(num);
	//creating file
	createFile(outFile, num);
	//constructing the beginning of the list by creating a head first.
	struct node *head;
	head = new(node);
	if (head == NULL)
	{
		cout << "Head node was not created" << endl;
		system("pause");
	}
	head->next = NULL;
	head->previous = NULL;
	//populating list.
	readNormal(inFile, num, head);
	//deleting list
	deleteList(head);
	//printing list
	cout << "List printed in reverse order, with only odd numbers" << endl;
	printList(head);

	



	system("pause");
	return (0);
}

void getData(int &num)
{
	cout << "This program will take a number you enter and randomly generate" << endl;
	cout << "that many numbers to a text file named Numbers.txt" << endl;
	cout << "Enter a number between 20 and 100" << endl;
	cin >> num;

	if (num < 20 || num > 100)
	{
		cout << "Your number must be between 20 and 100, please re-enter a number" << endl;
		system("pause");

	}

}

void createFile(ofstream &outFile, int num)
{
	//random function
	srand(time(0));
	int x = 0;
	if (!outFile)
	{
		cout << "Text file could not be created" << endl;
		system("pause");
	}

	//for loop to write as many numbers randomly as the user inputed
	for (int i = 0; i < num; i++)
	{
		x = rand();
		outFile << x << endl;
		//cout << x << endl;
	}
	outFile.close();
}

void deleteList(node *head)
{
	//since we want to delete specific nodes, I want ot traverse the list looking for hte 
	//requirements.
	struct node *temp;
	struct node *current;
	current = head->next;
	
	//Traverse list as long as current->next isnt equal to NULL
	while (current->next != NULL)
	{
		//while we traverse, if the value inside node is even we will delete node
		if (current->element % 2 == 0)
		{
			//set temp node to current, move current before we delete
			temp = current;
			//This next step will link the bordering nodes of hte one being deleted.
			//Example: If i have nodes 1-2-3 and I want to delete 2, this part will
			//link 1 and 3.
			current->previous->next = current->previous->next->next;
			current->next->previous = current->next->previous->previous;
			current = current->next;

			//delete temp
			delete(temp);
			
		}
		else
		{
			current = current->next;
		}
	}
}

void printList(node *head)
{
	//create a temporary node and set it current->previous
	struct node *temp;
	temp = head->next;
	int counter = 1;
	//traversing the list to get to the end
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	//loop to print out linked list as it works its way back to head
	while (temp != head)
	{
		cout << temp->element << "\t";

		//This will allow the program to print 5 nodes across the screen
		//then make a new line, allowing the format to look presentable
		if (counter % 5 == 0)
		{
			cout << endl;
			counter = 0;
		}
		//moving back up the list to head
		temp = temp->previous;
		counter++;
	}


}

int readNormal(ifstream &inFile, int num, node *head)
{
	inFile.open("Numbers.txt");


	int x = 0;

	//loop to populate the list
	for (int i = 0; i < num; i++)
	{
		//setting current pointer equal to head so we can traverse the list

		struct node *current = head;
		struct node *newNode;
		//Check to make sure computer has not run out of memory
		if ((newNode = new(node)) == NULL)
		{
			cout << "Out of Memory" << endl;
			return 2;
		}
		//while statement to add numbers to end of the list.
		while (current->next != NULL)
		{
			current = current->next;
		}
		inFile >> x;
		//populates the new node
		newNode->element = x;
		//newNode traverses between current and current->next
		newNode->next = current->next;
		newNode->previous = current;
		//if statement to see if there is a node after current
		//if there is set previous to newNode
		if (current->next)
		{
			current->next->previous = newNode;
		}
		//current = to newNode
		current->next = newNode;
	}
	//close the file after finishing
	inFile.close();
	return 0;

}


