/**********************************************************************
***********************************************************************
***********************************************************************
***																	***
***						ID INFORMATION								***
***                                                        			***
***   Programmers				:			Johnny Brinsko			***
***   Assignment #				:   		TA #2.Account  			***
***   Assignment Name			:			Heads up for TA#2.ACCT	***
***   Course # and Title		:	   		CISC 192 - C++			***
***   Class Meeting Time		:	   		TTh 9:35 - 12:40		***
***   Instructor				:			Professor Forman		***
***   Hours						:			7						***
***   Difficulty				:			5						***
***   Completion Date			:			11/13/2012				***
***   Project Name				:  			JohnnysSecretAccount	***	 
***																	***
***********************************************************************
***********************************************************************
***                                       							***
***						PROGRAM DESCRIPTION              			***
***																	***
***	 
***                                                         		***
***********************************************************************
***********************************************************************
***																	***
***					Custom-Defined Function List					***
***                                                         		***
***		
***																	***
***********************************************************************
***********************************************************************
***																	***
***                         CREDITS				                    ***
***                                                         		***
***   		Thanks for assistance and inspiration from:        		***
***                                                         		***
***				   Professor Forman and Tim							***
***                                                         		***
***   		Thanks for the opportunity to assist and inspire:     	***
***								                               		***
***				   Professor Forman and Tim							***
***                                                         		***
***********************************************************************
***********************************************************************
**********************************************************************/

#include <iostream>				//Needed for cout, cin
#include <fstream>				//Needed for ofstream, ifstream
#include <string>				//Needed for strings

using namespace std;

bool	answeredYes(string input);
bool	answeredNo(string input);
bool	checkDupe(string possibleDupe, ifstream& readFromFile);
string	createAccount(string reply, ofstream& writeToFile, ifstream& readFromFile);

const string SECRET = "JohnnysSecretAccountInfo.dat";

int main()
{
	/////////////////////////////////////////////////////////////////////////
	//				LOCAL OBJECT/VARIABLE DECLARATION "BANNER"
	/////////////////////////////////////////////////////////////////////////
	string 		accountNumber;
	string		accountNumberFile;
	string		reply;
	ofstream	writeToFile;
	ifstream	readFromFile;
	int			invalidLogin = 0;
	/////////////////////////////////////////////////////////////////////////

	// Welcome
	cout << "W e l c o m e\n\n";
	cout << "Please login with a valid account number: ";
	cin	 >>	accountNumber;

	// Handle an invalid login
	while (accountNumber != "0")
	{
		invalidLogin++;
		switch (invalidLogin)
		{
			case 1:
			case 2:
				cout << endl << "** Login Invalid **" << endl << endl
				     << "Please login with a valid account number: ";
				cin  >> accountNumber;
				break;
			case 3:
				cout << endl << "** Login Invalid **" << endl
				     << "You have 1 more attempt remaining. If unsuccessful, program will exit."
				     << endl << endl << "Please login with a valid account number: ";
				cin  >> accountNumber;
				break;
			case 4:
				cout << endl << "Bye";
				cin.ignore();
				cin.ignore();
				return 0;
		}
	}

	// 0 is the only valid login
	if (accountNumber == "0")
	{
		cout << "Thanks for entering " << accountNumber << ". It is valid, congratulations . . ." << endl
			 << "Would you like to create another valid account number (\"yes\" or otherwise): ";
		cin  >> reply;

		// As long as we answered "yes" to any of the create another account number prompts
		while (answeredYes(reply))
		{
			cout << endl << "Thanks for entering " << reply << ".\n"
				 << "Since you did say \"yes\", I guess we are ready to continue . . ." << endl << endl;

			// Use the return of createAccount function to see if the while condition will still be true
			reply = createAccount(reply, writeToFile, readFromFile);
		}
		
		// A "no" reply at any time will tell us what's in the secret file
		if (answeredNo(reply))
		{
		cout << "Since you didn't say \"yes\", I guess we are done.\n\n";
		cout << "Currently reading from disk file . . .\n"
		     << SECRET << " contains the following account numbers: " << endl;

		readFromFile.open(SECRET);
		
		// Read every line in the secret file and separate each with a space
		while (readFromFile >> accountNumberFile)
			cout << accountNumberFile << " \n";
		
		readFromFile.close();

		// End Of File feedback
		cout << "== No more account numbers ==" << endl;
		}
	}

	// Farewell
	cout << "\nBye";
	cin.ignore();
	cin.ignore();

	return 0;
}

string createAccount(string reply, ofstream& writeToFile, ifstream& readFromFile)
{
	/////////////////////////////////////////////////////////////////////////
	//			LOCAL OBJECT/VARIABLE DECLARATION "BANNER"
	/////////////////////////////////////////////////////////////////////////
	string 		newAccountNumber;
	/////////////////////////////////////////////////////////////////////////

	cout << "Please enter a new valid account number: ";
	cin  >> newAccountNumber;

	// When entered number is already in file, continually ask until unique
	while (checkDupe(newAccountNumber, readFromFile))
	{
		cout << endl << "ERROR: The account number, " << newAccountNumber << ", already exists. Try again.\n\n";
		cout << "Please enter a new valid account number: ";
		cin  >> newAccountNumber;
	}

	// We must've entered a unique number from what's in the file
	cout << endl << "Thanks for entering " << newAccountNumber << " -- which is being written to disk file:"
	     << endl << SECRET << endl << endl;
			
	cout << "Do you want to append or overwrite the file? ( a | o ): ";
	cin  >> reply;

	if (reply == "a")
		writeToFile.open(SECRET, fstream::app);
	else
		writeToFile.open(SECRET);

	// Actually write this number on a new line in the secret file
	writeToFile << newAccountNumber << endl;
	
	cout << endl << "Closing disk file " << SECRET << endl;
		writeToFile.close();

	// Ask if we want to do it again
	cout << "Would you like to create another valid account number (\"yes\" or otherwise): ";
	cin  >> reply;

	return reply;
	
}

bool checkDupe(string possibleDupe, ifstream& readFromFile)
{
	/////////////////////////////////////////////////////////////////////////
	//				LOCAL OBJECT/VARIABLE DECLARATION "BANNER"
	/////////////////////////////////////////////////////////////////////////
	string	line;
	bool	isDupe = false; // Always false unless we find a duplicate string (number)
	/////////////////////////////////////////////////////////////////////////

	// Open the secret file for reading
	readFromFile.open(SECRET);
	cout << "opening file to check for dupes . . . \n";
	
	cout << "file is open, searching for " << possibleDupe;

	// Read each line of secret file. If we get a match from our keyword, possibleDupe, set the isDupe flag
	while ( getline(readFromFile, line) )
	{
		if ( line == possibleDupe )
			isDupe = true;
	}

	readFromFile.close();

	return isDupe;
}

bool answeredYes(string input)
{
	/* Convert string to char
	char * replyChar;
	int i = 0;
	char c;

	replyChar = new char [input.size()+1];
	strcpy(replyChar, input.c_str());
	
	while (replyChar[i])
	{
		c = replyChar[i];
		putchar (tolower(c));
		i++;
	}

	return (replyChar == "yes"); */

	return (input == "yes");
}

bool answeredNo(string input)
{
	return (input == "no");
}