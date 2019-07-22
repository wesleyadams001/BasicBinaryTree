/*******************************************************************
*   Source Code File Name
*   Wesley Adams
*   Programming Assignment 3
*   
*   This program is entirely my own work
*******************************************************************/
#include "Book_Database.h"
#include <iostream>
#include <string.h>
#include <cmath>

#define DEBUG
using namespace std;

// Class constructor
Book_Database::Book_Database ()
{
	m_pRoot = NULL;
}

// Class destuctor
Book_Database::~Book_Database ()
{
#ifdef DEBUG
	cout<<"reached clear database"<<endl;
#endif
	ClearDatabase(m_pRoot);
}

// Read database from file
bool Book_Database::readDatabase(const char *filename)
{
	 char     line[128];
     int      numBooks;
	 
     // define other variables here as needed

    m_InFile.open(filename, ifstream::in); 
    if(!m_InFile.is_open())
    {
        // m_InFile.is_open() returns false if the file could not be found or
        //    if for some other reason the open failed.
        cout << "Unable to open file" << filename << "\nProgram terminating...\n";
        return false;
    }
#ifdef DEBUG
	cout<<"getting next line"<<endl;
#endif
	getNextLine(line, 128);
    // Read number of books
    
    numBooks = atoi(line);
    for(int i=0; i<numBooks; i++)
    {
		BookRecord *br = new BookRecord();
		#ifdef DEBUG
		cout<<"reading lines of inventory"<<endl;
		#endif
	     getNextLine(line, 128);
		 br->setStockNum(atoi(line));
		 getNextLine(line, 128);
		 br->setTitle(line);
		 getNextLine(line, 128);
		 br->setClassification(atoi(line));
		 getNextLine(line, 128);
		 br->setCost(atof(line));
		 getNextLine(line, 128);
		 br->setNumberInStock(atoi(line));
		 
		 addBook(br);
    }
    return true;
}

// Add the given book to the list
bool Book_Database::addBook(BookRecord *br)
{

	#ifdef DEBUG
	cout<<"Reached search by add book"<<endl;
#endif
	//Set base variables
	BookRecord *temp;
	BookRecord *back;
	temp = m_pRoot;
	back = NULL;

	//while temp is not null assign to left or right depending on 
	//how it compares to the temp stocknum
	while(temp!=NULL)
	{
		//move back to temp
		back = temp;

		//if the stock num is less than temps stock num move forward to either left or right
		if(br->getStockNum()<temp->getStockNum())
		{
			temp = temp->m_pLeft;
		}
		else
		{
			temp = temp->m_pRight;
		}
	}
	//if back is null set the root to the new record
	if(back == NULL)
	{
		m_pRoot = br;
	}
	else
	{
		if(br->getStockNum() < back->getStockNum())
		{
			back->m_pLeft = br;
		}
		else
		{
			back->m_pRight = br;
		}
	}
	return true;


}

// Remove a book from the list
BookRecord *Book_Database::removeBook(long stockNum)
{
	#ifdef DEBUG
	cout<<"Reached search by remove book"<<endl;
#endif
	BookRecord *back = NULL;
	BookRecord *temp = NULL;
	BookRecord *delParent = NULL;
	BookRecord *delNode = NULL;

	temp = m_pRoot;
	back = NULL;
	//search while temp is not null and stocknum is not equal to current stock number
	while((temp!=NULL)&&(stockNum != temp->getStockNum()))
	{
		back = temp;
		if(stockNum < temp->getStockNum())
		{
			temp = temp->m_pLeft;
		}
		else
		{
			temp = temp->m_pRight;
		}

	}
	//Didnt find
	if(temp==NULL)
	{
		cout<<"Did not find book"<<endl;
		return NULL;
	}
	else
	{
		delNode = temp;
		delParent = back;
	}

	if(delNode->m_pRight==NULL)
	{
		if(delParent == NULL)
		{
			m_pRoot = delNode->m_pLeft;
			delNode->m_pLeft = NULL;
			return delNode;
		}
		else
		{
			if(delParent->m_pLeft == delNode)
			{
				delParent->m_pLeft = delNode->m_pLeft;

			}
			else
			{
				delParent->m_pRight = delNode->m_pLeft;
			}
			delNode->m_pLeft = NULL;
			return delNode;
		}
	}
	else if(delNode->m_pLeft == NULL)
	{
			if(delParent == NULL)
			{
				m_pRoot =  delNode->m_pRight;
				delNode->m_pRight = NULL;
				return delNode;
			}
			else
			{
				if(delParent->m_pLeft == delNode)
				{
					delParent->m_pLeft = delNode->m_pRight;
				}
				else
				{
					delParent->m_pRight = delNode->m_pRight;
				}
				delNode->m_pRight = NULL;
				return delNode;
			}
	}
	else
	{
		//Make a copy
		BookRecord *rec = new BookRecord();
		*rec = *delNode;

		temp = delNode->m_pLeft;
		back = delNode;
		while(temp->m_pRight != NULL)
		{
			back = temp;
			temp = temp->m_pRight;
		}
		
		//copy out values of target
		char arr[128];
		delNode->setStockNum(temp->getStockNum());
		temp->getTitle(arr);
		delNode->setTitle(arr);
		delNode->setNumberInStock(temp->getNumberInStock());
		delNode->setCost(temp->getCost());
		delNode->setClassification(temp->getClassification());

		//remove replacement node
		if(back==delNode)
		{
			back->m_pLeft = temp->m_pLeft;
		}
		else
		{
			back->m_pRight = temp->m_pLeft;
		}
		delete temp;
		return delNode;
		
	}
		
}

// Search for a book by stock number
BookRecord *Book_Database::searchByStockNumber(long stockNum)
{
	#ifdef DEBUG
	cout<<"Reached search by stock number"<<endl;
#endif
	BookRecord *temp = NULL;
	temp = m_pRoot;

	//Search
	while((temp!=NULL)&&(temp->getStockNum()!=stockNum))
	{
		if(stockNum<temp->getStockNum())
		{
			temp = temp->m_pLeft;
		}
		else
		{
			temp = temp->m_pRight;
		}
	}
	if(temp == NULL)
	{
		//return null if did not find
		cout<<"Did not find target stock number"<<endl;
		return NULL;
	}
	else
	{
		//Specifically stated that we do not need to make a copy
		//Just return pointer to node
		/*BookRecord *copy = new BookRecord();
		*copy = *temp;*/
		return temp;
	}
}

// Search for all books of the given classification
void Book_Database::searchByClassification(int cl)
{
	searchByClassification(cl, m_pRoot);

}

// Search for all books whose cost is within the given range
void Book_Database::searchByCost(double min, double max)
{
	searchByCost(min, max, m_pRoot);
}

// Get number of books of given stock number in stock
int Book_Database::getNumberInStock(long sn)
{
#ifdef DEBUG
	cout<<"reached get number in stock"<<endl;
#endif
	//initialize number of items to an impossible value
	int numItems = 0;

	//Set temp to head
	BookRecord *temp = NULL;
	temp = m_pRoot;

	//while temp is not null and stock num is not equal to the 
	//current items stock num set temp to the next item by using
	//getNext() function
	while((temp != NULL)&&(temp->getStockNum() != sn))
	{
		if(temp->getStockNum()<sn)
		{
			temp = temp->m_pLeft;
		}
		else
		{
			temp = temp->m_pRight;
		}
	}
	//If temp is null return null as you cannot search an empty list
	if(temp == NULL)
	{
		cout<<"Did not find target value"<<endl;
		return NULL;
	}
	//if found the item
	if(temp->getStockNum() == sn)
	{
		//copy out the value of the number of items in stock and return the value
		numItems += temp->getNumberInStock();
		return numItems;
	}

	//return -1 if did not find value
	return numItems;
}

// Print
void Book_Database::PrintDatabase()
{
#ifdef DEBUG
	cout<<"Reached print"<<endl;
#endif
	PrintDatabase(m_pRoot);
}

// Recursively remove any items from the list
void Book_Database::ClearDatabase(BookRecord *rt)
{
	// Nothing to clear
	if(rt==NULL) 
	{
		cout<<"Empty Database"<<endl;
		return;
	}

	// Clear left tree
	if(rt->m_pLeft != NULL) 
	{
		ClearDatabase(rt->m_pLeft);
	}

	// Clear right tree
    if(rt->m_pRight != NULL)
	{
		ClearDatabase(rt->m_pRight);
	}

	// Destroy this node
	#ifdef DEBUG
	cout<<"deleted node"<<rt->getStockNum()<<endl;
	#endif
    delete rt;   


    return;
}

// Read next line from a file
bool Book_Database::getNextLine(char *line, int lineLen)
{
	int    done = false;
    while(!done)
    {
        m_InFile.getline(line, lineLen);
        
		// If a line was successfully read
        if(m_InFile.good())    
        {
            if(strlen(line) == 0)
			{
				// Skip any blank lines
                continue;
			}
            else if(line[0] == '#')
			{
				// Skip any comment lines
				continue;
			}
            
			//valid data line so return with this line
            else return true;    
        }
		// No valid line read, meaning we reached the end of file
        else 
        {
			// Copy empty string into line as sentinal value
            strcpy(line, ""); 
            return false;
        }
		// end while
    } 
    return false; // Cannot reach this point but include a return to avoid compiler warning
                  //   that not all paths return a value.
}

// Recursive search by classification
void Book_Database::searchByClassification(int cl, BookRecord *rt)
{
	#ifdef DEBUG
	cout<<"Reached search by classification"<<endl;
#endif
	// Nothing to print
	if(rt==NULL) 
	{
		cout<<"No matching classifications"<<endl;
		return;
	}

	//get target node's cost
	int targetClassification = rt->getClassification();

	//if record has the target classification
	if(targetClassification == cl)
	{
		//print the record
		char title[128];
		rt->getTitle(title);
		cout<<title<< " " <<rt->getStockNum()<< " "<<targetClassification<<" $"<<rt->getCost()<<" " <<rt->getNumberInStock()<<endl;
	}

	// Print left sub-tree
	if(rt->m_pLeft != NULL) 
	{
		searchByClassification(cl, rt->m_pLeft);
	}

	// Print right sub-tree
    if(rt->m_pRight != NULL)
	{
		
		searchByClassification(cl, rt->m_pRight);
	}
}

// Recursive search by cost range
void Book_Database::searchByCost(double min, double max, BookRecord *rt)
{
#ifdef DEBUG
	cout<<"Reached search by cost"<<endl;
#endif
	// Nothing to print
	if(rt==NULL) 
	{
		cout<<"No items with cost in the given interval"<<endl;
		return;
	}

	//get target node's cost
	double targetCost = rt->getCost();

	//if cost is in the desired range
	if((targetCost<max)&&(targetCost>min))
	{
		//print the record
		char title[128];
		//Get title into char array
		rt->getTitle(title);
		cout<<title<<" " <<rt->getStockNum()<< " " <<rt->getClassification()<< " $"<<targetCost<< " "<<rt->getNumberInStock()<<endl;
	}

	// Print left sub-tree
	if(rt->m_pLeft != NULL) 
	{
		searchByCost(min, max, rt->m_pLeft);
	}

	// Print right sub-tree
    if(rt->m_pRight != NULL)
	{
		
		searchByCost(min, max, rt->m_pRight);
	}
}

// Recursive print all
void Book_Database::PrintDatabase(BookRecord *rt)
{
	// Nothing to print
	if(rt==NULL) 
	{
		cout<<"Empty database nothing to print"<<endl;
		return;
	}

	//print the record
	char title[128];
	rt->getTitle(title);
	cout<<title<< " " <<rt->getStockNum()<<" " <<rt->getClassification()<< " $" <<rt->getCost()<< " " <<rt->getNumberInStock()<<endl;

	// Print left sub-tree
	if(rt->m_pLeft != NULL) 
	{
		PrintDatabase(rt->m_pLeft);
	}

	// Print right sub-tree
    if(rt->m_pRight != NULL)
	{
		PrintDatabase(rt->m_pRight);
	}
}