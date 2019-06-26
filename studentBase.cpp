#include "studentBase.h"
#include <string>

using std::string;
using std::cout;

studentBase::studentBase()
{
	name.clear();
	group = 0;
	bookCount = 0;
	books.clear();
	booksID.clear();
}

studentBase::studentBase(string nameInput, int groupInput, int bookCountInput, vector<string> authorsInput, vector<string> bookInput, vector <int> bookIDinput)
{ 
	name = nameInput;
	group = groupInput;
	bookCount = bookCountInput; 
	authors = authorsInput;
	books = bookInput;
	booksID = bookIDinput; 
};

studentBase::~studentBase()
{ 
	cout << "Student base has been cleaned!";
};

void studentBase::addBook(string bookName, int bookNumber)
{
	bookCount++;
	books.push_back(bookName);
	booksID.push_back(bookNumber);
}

void studentBase::removeBookByName(string bookName)
{
	int removeID = 0;
	for (string book : books)
	{
		removeID++;
		if (book == bookName)
			break;
	}
	books.erase(books.begin() + removeID);
	booksID.erase(booksID.begin() + removeID);
}

void studentBase::removeBookByNumber(int number)
{
	int removeID = 0;
	for (int ID : booksID)
		if (ID == number)
			break;
	books.erase(books.begin() + removeID);
	booksID.erase(booksID.begin() + removeID);
}

void studentBase::printStudentInfo()
{
	cout << "Name: " << name << endl;
	cout << "Group number: " << group << endl;
	cout << "Number of books hold by student: " << bookCount << endl;
	for (int i = 0; i < bookCount; i++)
	{
		cout << "Author: " << authors[i] << "\nBook name: " << books[i] << "\nBookID: " << booksID[i] << endl;
	}
	cout << "-----------------\n";
}

void studentBase::printBookInfo(int bookID, bool &isWritten)
{
	int index = 0;
	for (int check : booksID)
	{
		if (check == bookID)
		{
			cout << "Author: " << authors[index] << "\nBook name: " << books[index] << "\nBookID: " << booksID[index] << endl;
			isWritten = true;
			break;
		}
		index++;
	}
}

void studentBase::printBookBase(vector<int> &isWritten)
{
	bool flag;
	for (int i = 0; i < bookCount; i++)
	{
		flag = false;
		for (int check : isWritten)
			if (check == booksID[i])
			{
				flag = true;
				break;
			}
		if (!flag)
		{
			cout << "Author: " << authors[i] << "\nBook name: " << books[i] << "\nBookID: " << booksID[i] << endl;
			isWritten.push_back(booksID[i]);
		}
	}
	cout << "-----------------\n";
}

void studentBase::changeName(string newName) {	name = newName; }

void studentBase::changeGroup(int newGroup) { group = newGroup; }

void studentBase::changeBookCount(int newBookCount) { bookCount = newBookCount; }

void studentBase::changeAuthors(vector <string> newAuthors) { authors = newAuthors; }

void studentBase::changeBooks(vector <string> newBooks){ books = newBooks; }

void studentBase::changeBooksID(vector <int> newBooksID){booksID = newBooksID; }

string studentBase::getName(){	return name; }

int studentBase::getGroup(){ return group; }

int studentBase::getBookCount(){ return bookCount; }

vector<string> studentBase::getAuthors() { return authors; }

vector<string> studentBase::getBooks(){ return books; }

vector<int> studentBase::getBooksID(){ return booksID; }
