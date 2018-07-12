/*Levi Pflepsen
Due: 6-25-18
Mr. Walley
CSC 307


This program will have a user enter a number and create a text file and random generate numbers depending
on the amount the user inputed.  The numbers from the text file will be stored in a linked list and will be
outputed to the command prompt

Change Log: I removed the nested print and delete functions and inserted them into main.  I also created a new list for every
function inside main instead of in each individual function.  I was recieving errors creating node *head over and over so 
I had to create node *head1, 2, 3.
Adjusted comments to the restructed program.
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
};

//this function will prompt user to input a number
void getData(int&);
//This function will create and write how many the numbers the user wants
//with a random function.
void createFile(ofstream &, int);
//function to delete linked list
void deleteList(node *);
//function to print list
void printList(node *);
//This function will read the data as presented in the file
int readNormal(ifstream &, int num, node *);
//this function will read the data from the bottom to the top of the file
int readReverse(int, ifstream &, node *);
//This function will sort the list highest to lowest
int readHigh(int, ifstream &, node*);
//This function will sort the list from lowest to highest
int readLow(int, ifstream&, node*);

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

	cout << "*********************************************" << endl;
	cout << "Reading file as is" << endl;
	//reading file from top to bottom
	readNormal(inFile, num, head);
	//printing list
	printList(head);
	//deleting list
	deleteList(head);

	//constructing the beginning of the list by creating a head first.
	struct node *head1;
	head1 = new(node);
	if (head1 == NULL)
	{
		cout << "Head node was not created" << endl;
		system("pause");
	}
	head1->next = NULL;

	cout << "*********************************************" << endl;
	cout << "Reading file from low to high" << endl;
	//sorting list from low to high
	readLow(num, inFile, head1);
	//printing list
	printList(head1);
	//deleting list
	deleteList(head1);

	//constructing the beginning of the list by creating a head first.
	struct node *head2;
	head2 = new(node);
	if (head2 == NULL)
	{
		cout << "Head node was not created" << endl;
		system("pause");
	}
	head2->next = NULL;

	cout << "*********************************************" << endl;
	cout << "Reading file from high to low" << endl;
	//sorting list from high to low
	readHigh(num, inFile, head2);
	//print list
	printList(head2);
	//deleting list
	deleteList(head2);

	//constructing the beginning of the list by creating a head first.
	struct node *head3;
	head3 = new(node);
	if (head3 == NULL)
	{
		cout << "Head node was not created" << endl;
		system("pause");
	}
	head3->next = NULL;

	cout << "*********************************************" << endl;
	cout << "Reading file in reverse" << endl;
	//reading file from bottom to top
	readReverse(num, inFile, head3);
	//printing list
	printList(head3);
	//deleting list
	deleteList(head3);
	


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
{//same as print we create a temporary node to delete the list
	struct node *temp;

	//Create a loop to delete nodes one at a time.  Set temp equal
	//to the node after head, delete head adn then set head equal to temp

	while (head != NULL)
	{
		temp = head->next;
		delete(head);
		head = temp;
	}
}

void printList(node *head)
{
	//create a temporary node and set it equal to head
	struct node *temp;
	temp = head->next;
	int counter = 1;

	//loop to travel linked list and print it to the console
	while (temp != NULL)
	{
		cout << temp->element << "\t";

		//This will allow the program to print 5 nodes across the screen
		//then make a new line, allowing the format to look presentable
		if (counter % 5 == 0)
		{
			cout << endl;
			counter = 0;
		}

		//next we move to the next node and increment counter
		temp = temp->next;
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
		//cout << newNode->element << endl;

		//newNode traverses between current and current->next
		newNode->next = current->next;
		current->next = newNode;
	}
	//close the file after finishing
	inFile.close();
	return 0;

}

int readReverse(int num, ifstream &inFile, node *head)
{
	inFile.open("Numbers.txt");


	int x = 0;

	//loop to populate the list
	for (int i = 0; i < num; i++)
	{
		//setting current pointer equal to head so we can traverse the list

		//struct node *current = head;
		struct node *current = head;
		struct node *newNode;
		//Check to make sure computer has not run out of memory
		if ((newNode = new(node)) == NULL)
		{
			cout << "Out of Memory" << endl;
			return 2;
		}

		inFile >> x;
		//populates the new node
		newNode->element = x;
		//cout << newNode->element << endl;

		//newNode traverses between current and current->next
		newNode->next = current->next;
		current->next = newNode;
		
	}
	//close the file after finishing
	inFile.close();
	return 0;
}

int readHigh(int num, ifstream &inFile, node *head)
{
	//opening the txt file to read from
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

		inFile >> x;
		//setting up a while loop that will populate the list from highest
		//to lowest
		while ((current->next != NULL) && (current->next->element > x))
		{
			current = current->next;
		}
		//populates the new node
		newNode->element = x;
		//cout << newNode->element << endl;

		//newNode traverses between current and current->next
		newNode->next = current->next;
		current->next = newNode;

		//setting up a while loop that will populate the list from lowest
		//to greatest
		while ((current->next != NULL) && (current->next->element > x))
		{
			current = current->next;
		}
	}

	//close the file after finishing
	inFile.close();
	return 0;
}

int readLow(int num, ifstream &inFile, node *head)
{
	//opening the txt file to read from
	inFile.open("Numbers.txt");


	int x = 0;
	//setting current pointer equal to head so we can traverse the list

	//loop to populate the list
	for (int i = 0; i < num; i++)
	{
		struct node *current = head;
		struct node *newNode;


		//Check to make sure computer has not run out of memory
		if ((newNode = new(node)) == NULL)
		{
			cout << "Out of Memory" << endl;
			return 2;
		}

		inFile >> x;
		//setting up a while loop that will populate the list from highest
		//to lowest
		while ((current->next != NULL) && (current->next->element < x))
		{
			current = current->next;
		}
		//populates the new node
		newNode->element = x;
		//cout << newNode->element << endl;

		//newNode traverses between current and current->next
		newNode->next = current->next;
		current->next = newNode;
	}

	//close the file after finishing
	inFile.close();
	return 0;
}