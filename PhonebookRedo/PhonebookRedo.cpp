//Assignment #4: Phonebook Redo
//Michael Cohen

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "windows.h" //To Use System Function
using namespace std;

class Phonebook
{
	char fullName[50];
	char homeNumber[25];
	char mobileNumber[25];
public:
	Phonebook();
	void setFullName(char b1[], char hN[], char mN[]);
	void display();
	friend class PhonebookList; //friend class
};

Phonebook::Phonebook()
{
	strcpy_s(fullName, "");
	strcpy_s(homeNumber, "");
	strcpy_s(mobileNumber, "");
}

void Phonebook::setFullName(char b1[], char hN[], char mN[])
{
	strcpy_s(fullName, b1);
	strcpy_s(homeNumber, hN);
	strcpy_s(mobileNumber, mN);
}

void Phonebook::display()
{
	printf("Contact: %s | Home Number: %s | Mobile Number: %s \n", fullName, homeNumber, mobileNumber);
}

class PhonebookList
{
	char filename[100];
	Phonebook **mylist;
public:
	PhonebookList();
	~PhonebookList();
	void setFilename(char f[]);
	int entryCount;
	int getCount();
	void addToList(Phonebook *b);
	void showList();
	int saveList();
	void readList();
	void checkList();
};

PhonebookList::PhonebookList()
{
	mylist = new Phonebook*[100];
	entryCount = 0;
}

PhonebookList::~PhonebookList()
{
	delete mylist;
}

void PhonebookList::setFilename(char f[])
{
	strcpy_s(filename, f);
}

void PhonebookList::addToList(Phonebook *pb)
{
	mylist[entryCount] = pb;
	entryCount++;;
}

int PhonebookList::getCount()
{
	return entryCount;
}

void PhonebookList::showList()
{
	int pageNumber = 2; //first page is the 'Phonebook Entries' Page
	int pCount = 0;
	for (int i = 0; i < entryCount; i++)
	{
		if (pCount == 5) //To present 5 at a time with pause/continue step in-between pages
		{
			system("PAUSE");
			system("CLS");

			cout << "==================================================================" << endl;
			cout << "Page: " << pageNumber << endl;
			mylist[i]->display();
			pCount = 1;					//"refresh" the loop
			pageNumber++;					// to show next page
		}
		else
		{
			mylist[i]->display();
			++pCount;
		}
	}
}

int PhonebookList::saveList()
{
	ofstream output(filename);
	if (!output)
	{
		cout << "Failed!! " << endl;
		return -1;
	}
	for (int i = 0; i < entryCount; i++)
	{
		output << mylist[i]->fullName << "|";
		output << mylist[i]->homeNumber << "|";
		output << mylist[i]->mobileNumber << endl;
	}
	output.close();
	return 0;
}

void PhonebookList::readList()
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		Phonebook *ptr;
		char fullName[50];
		char homeNumber[25];
		char mobileNumber[25];

		infile.getline(fullName, 50, '|');
		if (strlen(fullName))
		{
			infile.getline(homeNumber, 25, '|');
			infile.getline(mobileNumber, 25);
			ptr = new Phonebook();
			ptr->setFullName(fullName, homeNumber, mobileNumber);
			addToList(ptr);
		}
	}
	infile.close();
}

//create duplicate check for additional entries to not add to phone book
void PhonebookList::checkList()
{
	//TBD
}

int main()
{
	char answer = 'y';
	char fullName[50];
	char homeNumber[25];
	char mobileNumber[25];
	char filename[50];
	int pbCount;

	PhonebookList *pbList = new PhonebookList();

	cout << "Enter File Name: " << endl;
	gets_s(filename);
	pbList->setFilename(filename);

	pbList->readList();
	if (pbList->getCount() == 0)
	{
		cout << "Your Phonebook is Empty!\nStart Recording!! " << endl;
	}
	else
	{
		cout << "You have " << pbList->getCount() << " entries in your Phonebook." << endl;
	}

	cout << "Add New Phonebook Entry? Enter Y to Add; Any other key view current Entries" << endl;
	cin >> answer;

	while (answer == 'Y' || answer == 'y')
	{
		pbCount = pbList->getCount();
		if (pbCount >= 100)			//don't "overfill" the phonebook (over 100)
		{
			cout << "Maximum Entries Reached!!" << endl;
			break;
		}

		cin.ignore();
		cin.clear();

		cout << "New Entry:" << endl;
		cout << "Enter Full Name:" << endl;
		gets_s(fullName);
		cout << "Enter Home Phone Number:" << endl;
		gets_s(homeNumber);
		cout << "Enter Mobile Phone Number:" << endl;
		gets_s(mobileNumber);


		Phonebook *myPB = new Phonebook();
		myPB->setFullName(fullName, homeNumber, mobileNumber);
		pbList->addToList(myPB);

		//check entries for duplicates
		//pbList->checkList();

		cout << "Another Entry? - Enter Y to Add; Any other key to view current Entries" << endl;
		cin >> answer;
	}
	//show entries on a new "page"
	system("PAUSE");
	system("CLS");

	cout << "=======================================================================" << endl;
	cout << "Phonebook Entries: \nPage: 1" << endl;
	pbList->showList();
	pbList->saveList();

	return 0;
}