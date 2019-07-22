// CS221ProgrammingAssignment3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Book_Database.h"
#include <iostream>

int main()
{
	char c;

	//Read test
	Book_Database *Inv = new Book_Database();
	Inv->readDatabase("BookData.txt");

	//Print test
	cout<<"\n\nPrint Test:\n"<<endl;
	Inv->PrintDatabase();

	//Add test
	cout<<"Add a book test:\n"<<endl;
	BookRecord *aBook = new BookRecord("A Tested Title", 7777, 777, 65.65);
	Inv->addBook(aBook);
	Inv->PrintDatabase();

	//Remove test
	cout<<"\n\nRemove book test:\n"<<endl;
	cout<<"Removing book"<<endl;
	Inv->removeBook(7777);
	Inv->removeBook(5678);
	Inv->PrintDatabase();

	//Search by stock number test
	cout<<"\n\nSearch by stock number: \n"<<endl;
	BookRecord *x = Inv->searchByStockNumber(2345);
	cout<<"Searched Record is:"<<x->getStockNum()<<endl;

	//Print record test
	cout<<"\n\nPrint Record Test:\n"<<endl;
	x->printRecord();

	//Search by classification test
	cout<<"\n\nSearch by classification test:\n"<<endl;
	cout<<"Those records matching the classification 613 are as follows: \n"<<endl;
	Inv->searchByClassification(x->getClassification());
	
	//search by cost test
	cout<<"\n\nGet cost test:\n"<<endl;
	cout<<"Those records whose cost is in the following interval:"<<endl;
	Inv->searchByCost(25.00,30.00);

	//Get number in stock test
	cout<<"\n\n Get number in stock test:\n"<<endl;
	cout<<"Number of books in stock for the given stock number"<<endl;
	int y = Inv->getNumberInStock(2345);//15
	cout<<"The stock num for 2345 is: "<<y<<endl;
	cout<<"printing inventory"<<endl;
	Inv->PrintDatabase();

	//Add double test
	cout<<"\n\nRe-Add test print:\n"<<endl;
	BookRecord *aBook2 = new BookRecord("A Tested Title", 7777, 777, 65.65);
	BookRecord *aBook3 = new BookRecord("A Tested Title", 7777, 777, 65.65);
	Inv->addBook(aBook2);
	//Inv->addBook(aBook3);
	Inv->PrintDatabase();

	//Search by classification for new book
	cout<<"\n\nSearch for books that match classification:\n"<<endl;
	Inv->searchByClassification(777);


	//Destructor test
	cout<<"\n\n Destructor test:"<<endl;
	Inv->~Book_Database();

	cin>>c;
	return 0;
}

