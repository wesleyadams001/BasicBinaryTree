/*******************************************************************
*   Source Code File Name
*   Wesley Adams
*   Programming Assignment 3
*   
*   This program is entirely my own work
*******************************************************************/
#pragma once
#include <string.h>
using namespace std;

class BookRecord
{

private:

	//This character array shall be 128 bytes in length and will be used to store the title of a book or periodical.
	char m_sTitle[128];

	//This long shall be used to store a unique stock number for the book or periodical. This will be used as the key in any store, search, or retrieval operations.
	long m_lStockNum;

	//This integer will be used to code specific information about the book or periodical.
	int m_iClassification;

	//This double will be used to store the cost of this book or periodical.
	double m_dCost;

	//This integer will be used to store the number of copies of this item currently in the inventory.
	int m_iCount;


public:

	//default constructor
	BookRecord();

	//This constructor shall set the member variables to the values passed into the function and initialize the m_iCount variable to one 
	BookRecord(const char *title, long sn, int cl, double cost);

	//The getTitle() function shall be defined as a pointer function. 
	//A call to this function will copy the member variable m_sTitle into the character array pointed to by the function argument.
	void getTitle(char *title);
	
	//	The setTitle() function will copy the function argument into the member variable m_sTitle.
	void setTitle(const char *title);

	//The getStockNum() function shall return the value stored in the member variable m_lStockNum
	long getStockNum();

	//The setStockNum() function will copy the function argument into the member variable m_lStockNum.
	void setStockNum(long sn);

	//The getClassification() function shall be defined as a reference function. 
	//A call to this function will copy the member variable m_iClassification into the interger variable referenced by the function argument.
	int getClassification();

	//The setClassification() function will copy the function argument into the member variable m_iClassification.
	void setClassification(int cl);

	//The getCost() function shall be defined as a pointer function. 
	//A call to this function will copy the member variable m_dCost into the double variable pointed to by the function argument.
	double getCost();
	
	//The setCost() function will copy the function argument into the member variable m_dCost.
	void setCost(double c);

	//The getNumberInStock() function shall return the value stored in the member variable m_iCount. 
	int getNumberInStock();
	
	//The setNumberInStock() function will copy the function argument into the member variable m_iCount.
	void setNumberInStock(int count);

	//This function shall print to the screen all data found in the record. Data should all be printed on a single line.
	void printRecord();

	//The left pointer
	BookRecord *m_pLeft;

	//The right pointer
	BookRecord *m_pRight;

	//default destructor
	~BookRecord();
};

