/*Levi Pflepsen
Due: July 7, 2018
Mr. Walley
Data Structures


This program will use stacks and queues for the data structures.  The program will have a user
input a file name and read the file.  As the program is reading the file, it will determine where to put
the data.  It will also throw away any bad data in the file.*/

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>

using namespace std;


void openFile(ifstream &);
void readFile(ifstream &, stack<int>*, queue<int>*, int &, int &);
void stackWrite( stack<int>*, int);
void queueWrite( queue<int>*, int);

int main()
{

	stack <int> myStack;
	queue <int> myQ;
	ifstream inFile;
	
	int stackCount = 0;
	int qCount = 0;
	//opening file
	openFile(inFile);
	//read the file to the stack and queue, with numerical requirements per structure.
	//Also will weed out bad data
	readFile(inFile,&myStack,&myQ, stackCount,qCount);
	//This function will write the contents of the stack to a new file
	//as well as display the average value of the stack
	stackWrite( &myStack, stackCount);
	//This function will write the contents of the queue to a new file
	//as well a display the average vale of the queue
	queueWrite( &myQ, qCount);





	system("pause");
	return(0);
}

void openFile(ifstream &inFile)
{
	string fileName;

	//Ask the user for the file name.
	cout << "Please enter the file name..." << endl;
	cin >> fileName;

	//open the file with the string variable
	inFile.open(fileName.c_str());

	//check to make sure file as opened properly
	if (!inFile)
	{
		cout << "Your file could not be opened" << endl;
		system("pause");
	}
}

void readFile(ifstream &inFile, stack<int>*myStack, queue<int>*myQ, int &stackCount, int &qCount)
{
	if (!inFile)
	{
		cout << "file not opened" << endl;
	}
	int x = 0;
	//while loop to begin reading file
	while (!inFile.eof())
	{
		inFile >> x;
		//if statement to filter out bad data
		if (!0 <= x && !x <= 99)
		{

			inFile.clear();
			inFile.ignore();
		}
		//if the numbers are between 50 and 99 and will go to stack
		//also a counter for average later
		if (50 <= x && x <= 99)
		{
			myStack->push(x);
			stackCount++;
		}
		//if the numbers are between 0 and 49 they will go to the queue
		//also counter for average later
		if(0 <= x && x <= 49)
		{
			myQ->push(x);
			qCount++;
		}
	}
	inFile.close();
}

void stackWrite( stack<int>*myStack, int stackCounter)
{
	ofstream outFile;
	float total = 0;
	float average = 0;
	//creating an outFile named stack.txt
	string fileName = "stack";
	fileName = fileName + "." + "txt";
	outFile.open(fileName);
	if (!outFile)
	{
		cout << "File to write to could not be opened" << endl;
	}
	//putting stack data into file while also adding contents and averaging
	//because stack was passed by reference I had to use -> instead
	//of the period to dereference
	while (!myStack->empty())
	{
		total += myStack->top();
		outFile << myStack->top() << endl;
		myStack->pop();
	}
	cout << endl;
	average = total / stackCounter;
	cout << "The average of the stack is: " << average << endl;
	outFile << "The average of the stack is: " << average << endl;
	outFile.close();
}

void queueWrite( queue<int>*myQ, int qCounter)
{
	ofstream outFile;
	float total = 0;
	float average = 0;
	//creating an outFile named queue.txt
	string fileName = "queue";
	fileName = fileName + "." + "txt";
	outFile.open(fileName);
	if (!outFile)
	{
		cout << "File to write to could not be opened" << endl;
	}
	//writing data to file as well as getting the aveage
	//because queue was passed by reference, I had to use the ->
	//to dereferance everything instead of jsut using hte period
	while (!myQ->empty())
	{
		outFile << myQ->front() << endl;
		total += myQ->front();
		myQ->pop();
	}
	cout << endl;
	average = total / qCounter;
	outFile << "Average of the Queue is: " << average << endl;
	cout  << "Average of the Queue is: " << average << endl;
	outFile.close();
}
