#pragma once
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class studentBase
{
private:
	string name;
	int group;
	int bookCount;
	vector<string> authors;
	vector<string> books;
	vector<int> booksID;

public:
	studentBase();
	studentBase(string nameInput, int groupInput, int bookCountInput, vector<string> authorsInput, vector<string> bookInput, vector <int> bookIDinput);
	~studentBase();

	void addBook(string bookName, int bookNumber);
	void removeBookByName(string bookName);
	void removeBookByNumber(int number);
	void printStudentInfo();
	void printBookInfo(int bookID, bool &isWritten);
	void printBookBase(vector<int> &isWritten);
	void changeName(string newName);
	void changeGroup(int newGroup);
	void changeBookCount(int newBookCount);
	void changeAuthors(vector <string> newAuthors);
	void changeBooks(vector <string> newBooks);
	void changeBooksID(vector <int> newBooksID);

	string getName();
	int getGroup();
	int getBookCount();
	vector<string> getAuthors();
	vector<string> getBooks();
	vector<int> getBooksID();

};
