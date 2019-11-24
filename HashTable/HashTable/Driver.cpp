/*************************************************************
*
* Lab / Assignment: Lab6 - HashTable
*
* Overview:
*		This program is an implementation of a HashTable.
*		As far as program input and output, everything is only
*		for testing the HashTable class and thus the code is
*		only test code, and requires no input.
*
* Input:
*		None required
*
* Output:
*		The program outputs the results of a simple test where
*		3 items are added to a hash table and then the titles
*		are printed using the operator[]. An item is changed
*		to test passing by reference, then the changed title
*		is printed. Because the rest of the test code is in
*		the 'HashTableTest.sln' it suggests the user to look
*		at the UnitTest code for the rest of the tests.
*
**************************************************************/

/*************************************************************
* Author: Dillon Wall
* Filename: Driver.cpp
* Date Created: 3/14/2019
* Modifications:
**************************************************************/

#include <string>
#include <iostream>
using std::cout;
using std::endl;
#include "HashTable.h"


int main()
{
	struct Book
	{
		std::string m_title;
		std::string m_author;
		int m_pages;
	};

	static const int TABLESIZE = 10;

	auto AsciiHash = [](std::string key)
	{
		int hashVal = 0;
		for (int i = 0; i < key.length(); ++i)
		{
			hashVal += key[i];
		}
		return hashVal % TABLESIZE;
	};

	HashTable<std::string, Book> table(TABLESIZE);

	table.SetHash(AsciiHash);

	Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
	table.Insert("0763757233", temp);

	Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 1 };
	table.Insert("7063757233", temp1);

	Book temp3 = { "And That n There", "Ralph Carestia", 1 };
	table.Insert("7063757234", temp3);

	cout << table["0763757233"].m_title << endl;
	cout << table["7063757233"].m_title << endl;
	cout << table["7063757234"].m_title << endl;

	table["0763757233"].m_title = "NOT What it was before";
	cout << table["0763757233"].m_title << endl;

	cout << "------------------------------------------------------------" << endl;
	cout << "    Main test complete, check unit tests for other tests    " << endl;
	cout << "------------------------------------------------------------" << endl;

	return 0;
}


