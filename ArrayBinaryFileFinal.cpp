/*Levi Pflepsen
Date Due: 20 June, 2018
Mr. Walley
Data Structures 


This Program will read a binary file and write it into seperate files.  Meta-data
will be used to determine the size of arrays, number of files etc..
The program will also be able to be executed from the command line via argc and argv*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readMeta(int meta[4], ifstream &inBinary);
void readFile(int *, int, ifstream &inBinary);
void writeFile(int *, int, string);

int main(int argc, char *argv[])
{	
	if (argc == 2)
	{
		string inputFile = argv[1];
		//Create the ifstream outside of functions
		//creating the ifstream inside a function that gets called
		//multiple times will reset the file pointer.
		
		//open the file with argv[1] which hte user will input a file name
		ifstream inBinary(inputFile, ios::out | ios::binary);
		
		int size = 0;
		int meta[4];
		//call function to get meta-data into an array
		readMeta(meta,inBinary);
		size = meta[3];
		if (size < 0)
		{
			cout << "Bad meta-data, check your file" << endl;
		}
		//If statements to determine what to do next
		//from the meta array. 
		//created dynamic array's local to 
		//individual If statements to help break up program
		//to create the required seperate files etc.
		if (meta[0] == 1)
		{
			//this if statement is for the meta data
			//dealing with sea temperatures
			string name = "temp";
			int *tempData = new int[size];
			readFile(tempData, size, inBinary);
			writeFile(tempData, size, name);
			delete tempData;
		}
		if (meta[1] == 1)
		{
			//this if statement is for the meta data
			//dealing with salt levels
			string name = "salinity";
			int *saltData = new int[size];
			readFile(saltData, size,  inBinary);
			writeFile(saltData, size, name);
			delete saltData;
		}
		if (meta[2] == 1)
		{
			//this if statement is for the meta data
			//dealing with sea height levels
			string name = "height";
			int *heightData = new int[size];
			readFile(heightData, size, inBinary);
			writeFile(heightData, size, name);
			delete heightData;

		}
		else
		{
			cout << "Bad meta data, check the file" << endl;
		}

		system("pause");
		return (0);
	}
	else
	{
		cout << "There was a problem inputing the file" << endl;
		system("pause");
		return(1);
	}
}

void readMeta(int meta[4], ifstream &inBinary)
{
	//going to create a ofstream and set it to read binary.
	//Going to fill a 4 element array with the meta data 
	
	
	int readNumber = 0;
	if (!inBinary)
	{
		cout << "File could not be opened" << endl;
		system("pause");
	}
	for (int i = 0; i < 4; i++)
	{
		//reading the binary file
		inBinary.read(reinterpret_cast<char *>(&readNumber), sizeof(int));
		meta[i] = readNumber;
	}
	
	
		
	
}

void readFile(int *Data, int size, ifstream &inBinary)
{
	//Function will read the binary file
	if (!inBinary)
	{
		cout << "Binary File could not be opened" << endl;
	}
	
	int readNumber = 0;
	for (int i = 0; i < size; i++)
	{
		//reading the rest of hte file after meta data
		inBinary.read(reinterpret_cast<char *>(&readNumber), sizeof(int));
		Data[i] = readNumber;
	}
	
	
}

void writeFile(int *Data, int size, string fileName)
{
	
	//Setting up hte filestream to name the files according to the string variable
	//as well as the size variable to create multiple files depending on the type of data
	//example temp.40
	ofstream outFile;
	
	fileName = fileName + "." + to_string(size);
	outFile.open(fileName,ios::out | ios::binary);
	
	if (!outFile)
	{
		cout << "Data file was not created" << endl;
		system("pause");
	}
	
	
	int writeNumber = 0;
	for (int i = 0; i < size; i++)
	{
		//write the file in binary to seperate file.
		writeNumber = Data[i];
		outFile.write(reinterpret_cast<const char *>(&writeNumber), sizeof(int));
	}
	
	
	
		
		
	
}
