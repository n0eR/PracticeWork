#include "headersNclass.h"

void removeDots(string &input)
{
	for (unsigned int i = 0; i < input.length(); i++)
		if (input[i] == '.')
			input[i] = ' ';
}

void getDots(string &input)
{
	for (unsigned int i = 0; i < input.length(); i++)
		if (input[i] == ' ')
			input[i] = '.';
}

studentBase * newStudent()
{
	studentBase * student = new studentBase;
	string nameInput;
	int groupInput;
	int bookCountInput;
	vector<string> authorsInput;
	vector<string> booksInput;
	vector<int> booksIDInput;

	string tmpStr;
	int tmpInt;

	cout << "Enter student name: ";
	cin >> nameInput;
	removeDots(nameInput);

	cout << "Enter group name: ";
	cin >> groupInput;

	cout << "Enter how many books that student holds now: ";
	cin >> bookCountInput;

	if (bookCountInput > 0)
	{
		for (int i = 0; i < bookCountInput; i++)
		{
			cout << "Enter author: ";
			cin >> tmpStr;
			removeDots(tmpStr);
			authorsInput.push_back(tmpStr);

			cout << "Enter book name: ";
			cin >> tmpStr;
			removeDots(tmpStr);
			booksInput.push_back(tmpStr);

			cout << "Enter bookID: ";
			cin >> tmpInt;
			booksIDInput.push_back(tmpInt);
		}
	}
	student->changeName(nameInput);
	student->changeGroup(groupInput);
	student->changeBookCount(bookCountInput);
	student->changeAuthors(authorsInput);
	student->changeBooks(booksInput);
	student->changeBooksID(booksIDInput);
	return student;
}

int getTheStudentIndex(vector<studentBase *> &students)
{
	int tmp;
	int cursor = 0, studentCount = 0, currentStudent = 0;
	bool isDone = false;
	bool isMenuOut = false;

	for (studentBase * slot : students)
		studentCount++;

	while (!isDone)
	{
		if (isMenuOut) tmp = _getch();
		else { tmp = 0; isMenuOut = true; }
		system("cls");

		puts("Choose the student you want to change (Up arrow to go up, Down arrow to go down, Enter to choose): \n");
		if (tmp == 72) { cursor--; if (cursor < 0) cursor = studentCount - 1; }
		else if (tmp == 80) { cursor++; if (cursor >= studentCount) cursor = 0; }
		else if (tmp == 13) { isDone = true; }
		for (currentStudent = 0; currentStudent < studentCount; currentStudent++)
		{
			if (cursor == currentStudent) cout << "> ";
			else cout << "  ";

			cout << "Name: " << students[currentStudent]->getName() << " | Number of books hold by student: " << students[currentStudent]->getBookCount() << endl;
		}
	}

	return cursor;
}

int getTheBookIndex(vector<studentBase *> &students, int studentIndex)
{
	int tmp, index, cursor = 0, bookCount = 0, currentBook = 0, checkStudentIndex;
	bool isDone = false;
	bool isMenuOut = false;
	vector<string> authors;
	vector<string> books;
	vector<int> booksID;

	if (studentIndex == -1)
		for (studentBase * slot : students)
			bookCount += slot->getBookCount();
	else
		bookCount = students[studentIndex]->getBookCount();

	while (!isDone)
	{
		if (isMenuOut) tmp = _getch();
		else { tmp = 0; isMenuOut = true; }
		system("cls");

		puts("Choose the book you want to change (Up arrow to go up, Down arrow to go down, Enter to choose): \n");
		if (tmp == 72) { cursor--; if (cursor < 0) cursor = bookCount - 1; }
		else if (tmp == 80) { cursor++; if (cursor >= bookCount) cursor = 0; }

		checkStudentIndex = 0;
		index = 0;
		for (studentBase * slot : students)
		{
			authors = slot->getAuthors();
			books = slot->getBooks();
			booksID = slot->getBooksID();
			if (((studentIndex != -1) && (studentIndex == checkStudentIndex)) || (studentIndex == -1))
			{
				auto book = begin(books);
				auto bookID = begin(booksID);
				for (auto author = begin(authors); author != end(authors); ++author)
				{
					if (cursor == index) cout << "> "; 
					else cout << "  ";
					
					cout << "Auhtor: " << *author << " | Book: " << *book << " | BookID: " << *bookID << endl;

					book++;
					bookID++;
					index++;
				}
			}
			checkStudentIndex++;
		}

		if (tmp == 13) { isDone = true; }
	}

	return cursor;
}

void addBookStudent(vector<studentBase *> &students)
{
	int index, 
		bookCountInput, 
		bookCountResult;
	vector<string> authorsResult;
	vector<string> booksResult;
	vector<int> booksIDResult;

	string tmpStr;
	int tmpInt;

	index = getTheStudentIndex(students);

	authorsResult = students[index]->getAuthors();
	bookCountResult = students[index]->getBookCount();
	booksResult = students[index]->getBooks();
	booksIDResult = students[index]->getBooksID();

	cout << "How many books do you want to add? ";
	cin >> bookCountInput;

	if (bookCountInput > 0)
	{
		for (int i = 0; i < bookCountInput; i++)
		{
			cout << "Enter author: ";
			cin >> tmpStr;
			removeDots(tmpStr);
			authorsResult.push_back(tmpStr);

			cout << "Enter book name: ";
			cin >> tmpStr;
			removeDots(tmpStr);
			booksResult.push_back(tmpStr);

			cout << "Enter bookID: ";
			cin >> tmpInt;
			booksIDResult.push_back(tmpInt);
		}
	}
	
	bookCountResult += bookCountInput;

	students[index]->changeBookCount(bookCountResult);
	students[index]->changeAuthors(authorsResult);
	students[index]->changeBooks(booksResult);
	students[index]->changeBooksID(booksIDResult);
}

void removeBookStudent(vector<studentBase *> &students)
{
	int index,
		bookCountResult;
	vector<string> authorsResult;
	vector<string> booksResult;
	vector<int> booksIDInput;
	vector<int> booksIDResult;
	int removeIndex;

	index = getTheStudentIndex(students);

	authorsResult = students[index]->getAuthors();
	bookCountResult = students[index]->getBookCount();
	booksResult = students[index]->getBooks();
	booksIDResult = students[index]->getBooksID();

	removeIndex = getTheBookIndex(students, index);

	authorsResult.erase(authorsResult.begin() + removeIndex);
	booksResult.erase(booksResult.begin() + removeIndex);
	booksIDResult.erase(booksIDResult.begin() + removeIndex);
	
	bookCountResult--;

	students[index]->changeBookCount(bookCountResult);
	students[index]->changeAuthors(authorsResult);
	students[index]->changeBooks(booksResult);
	students[index]->changeBooksID(booksIDResult);
}

void addBookLibrary(vector<studentBase *> &students)
{
	int index,
		bookCountInput,
		bookCountResult;
	vector<string> name;
	vector<string> authorsResult;
	vector<string> booksResult;
	vector<int> booksIDResult;

	string tmpStr;
	int tmpInt;

	index = 0;
	for (studentBase * slot : students)
		index++;

	students[index]->changeName("NULL");
	students[index]->changeGroup(-1);
	authorsResult = students[index]->getAuthors();
	bookCountResult = students[index]->getBookCount();
	booksResult = students[index]->getBooks();
	booksIDResult = students[index]->getBooksID();

	cout << "How many books do you want to add? ";
	cin >> bookCountInput;

	if (bookCountInput > 0)
	{
		for (int i = 0; i < bookCountInput; i++)
		{
			cout << "Enter author: ";
			cin >> tmpStr;
			removeDots(tmpStr);
			authorsResult.push_back(tmpStr);

			cout << "Enter book name: " << endl;
			cin >> tmpStr;
			removeDots(tmpStr);
			booksResult.push_back(tmpStr);

			cout << "Enter bookID: " << endl;
			cin >> tmpInt;
			booksIDResult.push_back(tmpInt);
		}
	}

	bookCountResult += bookCountInput;

	students[index]->changeBookCount(bookCountResult);
	students[index]->changeAuthors(authorsResult);
	students[index]->changeBooks(booksResult);
	students[index]->changeBooksID(booksIDResult);
}

void removeBookLibrary(vector<studentBase *> &students)
{
	int tmp, bookID, index, bookCountResult, studentNumber = 0;
	vector<string> authorsResult;
	vector<string> booksResult;
	vector<int> booksIDResult;

	tmp = getTheBookIndex(students, -1);

	for (studentBase * slot : students)
		if (slot->getBookCount() <= tmp)
		{
			tmp -= (slot->getBookCount());
			studentNumber++;
		}
		else
			break;
	
	bookID = students[studentNumber]->getBooksID()[tmp];

	for (studentBase * slot : students)
	{
		bookCountResult = slot->getBookCount();
		authorsResult = slot->getAuthors();
		booksIDResult = slot->getBooksID();
		booksResult = slot->getBooks();
		index = 0;
		for (int ID : booksIDResult)
		{
			if (ID == bookID)
			{

				authorsResult.erase(authorsResult.begin() + index);
				booksIDResult.erase(booksIDResult.begin() + index);
				booksResult.erase(booksResult.begin() + index);
				bookCountResult--;
				break;
			}
			else
				index++;
		}
		slot->changeAuthors(authorsResult);
		slot->changeBooksID(booksIDResult);
		slot->changeBooks(booksResult);
		slot->changeBookCount(bookCountResult);
	}
	cout << "Done! \n";
}

void changeBookID(vector<studentBase *> &students)
{
	int oldID, newID, tmp, studentNumber = 0;
	vector<int> booksIDResult;

	tmp = getTheBookIndex(students, -1);

	for (studentBase * slot : students)
		if (slot->getBookCount() <= tmp)
		{
			tmp -= (slot->getBookCount());
			studentNumber++;
		}
		else
			break;

	oldID = students[studentNumber]->getBooksID()[tmp];

	cout << "Enter the new id: ";
	cin >> newID;

	for (studentBase * slot : students)
	{
		booksIDResult = slot->getBooksID();
		for (auto ID = begin(booksIDResult); ID != end(booksIDResult); ID++)
		{
			if (*ID == oldID)
				*ID = newID;
		}
		slot->changeBooksID(booksIDResult);
	}
	cout << "Done!\n";
}

void printStudent(vector<studentBase *> &students)
{
	for (studentBase * slot : students)
	{
		slot->printStudentInfo();
	}
}

void printBooks(vector <studentBase *> &students)
{
	vector<int> isWritten;
	for (studentBase * slot : students)
	{
		slot->printBookBase(isWritten);
	}
}

void printBookByID(vector<studentBase *> &students)
{
	int bookID;
	bool isWritten = false;
	cout << "Input book ID: ";
	cin >> bookID;

	for (studentBase * slot : students)
	{
		slot->printBookInfo(bookID, isWritten);
		if (isWritten)
			break;
	}
	if (!isWritten)
		cout << "There is no book with that BookID in the base! \n";
}

void getFromFile(vector<studentBase *> &students)
{
	ifstream fileInput;
	fileInput.open("database.txt", ios::in);

	if (!fileInput.is_open())
	{
		cout << "File didn't open! Check the file! \n";
	}
	else
	{
		int studentCount;
		string name;
		string tmpStr;
		int tmpInt;
		int group;
		int bookCount;
		vector<string> authors;
		vector<string> books;
		vector<int> booksID;
		studentBase * student;

		fileInput >> studentCount;
		for (int i = 0; i < studentCount; i++)
		{
			student = new studentBase;
			authors.clear();
			books.clear();
			booksID.clear();

			fileInput >> name;
			removeDots(name);

			fileInput >> group;
			fileInput >> bookCount;
			for (int j = 0; j < bookCount; j++)
			{
				fileInput >> tmpStr;
				removeDots(tmpStr);
				authors.push_back(tmpStr);

				fileInput >> tmpStr;
				removeDots(tmpStr);
				books.push_back(tmpStr);

				fileInput >> tmpInt;
				booksID.push_back(tmpInt);
			}

			student->changeAuthors(authors);
			student->changeBookCount(bookCount);
			student->changeBooks(books);
			student->changeBooksID(booksID);
			student->changeGroup(group);
			student->changeName(name);

			students.push_back(student);
		}
	}

	cout << "Done succesfully! \n";
}

void getToFile(vector<studentBase * > &students)
{
	ofstream fileOut;
	fileOut.open("dataBase.txt", std::ofstream::out | std::ofstream::trunc);

	int overallCount = 0;
	int tmpInt;
	string tmpStr;
	vector<string> authors;
	vector<string> books;
	vector<int> bookID;

	for (studentBase * slot : students)
		overallCount++;

	fileOut << overallCount << endl;
	for (studentBase * slot : students)
	{
		tmpStr = slot->getName();
		getDots(tmpStr);
		fileOut << tmpStr << endl;

		fileOut << slot->getGroup() << endl;

		overallCount = slot->getBookCount();
		fileOut << overallCount << endl;

		authors = slot->getAuthors();
		books = slot->getBooks();
		bookID = slot->getBooksID();
		overallCount = 0;

		for (string info : authors)
		{
			tmpStr = authors[overallCount];
			getDots(tmpStr);
			fileOut << tmpStr << endl;

			tmpStr = books[overallCount];
			getDots(tmpStr);
			fileOut << tmpStr << endl;

			tmpInt = bookID[overallCount];
			fileOut << tmpInt << endl;
			overallCount++;
		}
	}

	fileOut.close();
	cout << "Done succesfully! \n";
}

void writeFeedback()
{
	system("cls");
	ofstream fileOut;
	fileOut.open("feedback.txt", std::ofstream::app);
	time_t t = time(0);
	tm * now = localtime(&t);
	fileOut << asctime(now) << endl;
	system("pause");
}

void menu(vector<studentBase *> &students)
{
	int tmp, level = 1, cursor = 0, currentMenuSize;
	bool isMenuOut = false;
	const int menu1Size = 2, menu2Size = 4, menu3Size = 9;
	string menu1[menu1Size] = { "1. Get information", "2. Change information" },

		   menu2[menu2Size] = { "1. Books hold by student", "2. Book info by ID", 
								"3. Get the student base", "4. Get the book base"},

		   menu3[menu3Size] = { "1. Add student", "2. Remove student", 
								"3. Add book to student's hold", "4. Remove book from student's hold", 
								"5. Add book to library", "6. Remove book from library", 
								"7. Change book ID", 
								"8. Get student base from file", "9. Re-write student base to file" };
	do
	{
		if (isMenuOut) tmp = _getch();
		else { tmp = 0; isMenuOut = true; }
		system("cls");
		
		if (level == 1) currentMenuSize = menu1Size;
		else if (level == 2) currentMenuSize = menu2Size;
		else currentMenuSize = menu3Size;
		currentMenuSize--;

		if (tmp == 72) { cursor--; if (cursor < 0) cursor = currentMenuSize; }
		else if (tmp == 80) { cursor++; if (cursor > currentMenuSize) cursor = 0; }
		else if ((char)tmp == '0') { writeFeedback(); level = 1; tmp = 27; }

		if (level == 1)
			puts("Hello! This program can help you to collect up library info about students and books they hold\n"
				 "Use Up and Down arrows to control the cursor, Esc to go back, Enter to go in menu. \n"
				 "Need support? Contact: dimon@kezling.ru \n");
		else if (level == 2)
			puts("In that menu you can check information about students and books.\n");
		else
			puts("In that menu you can change students informnation and books description\n");

		for (int i = 0; i < currentMenuSize + 1; i++)
		{
			i == cursor ? cout << "> " : cout << "  ";
			if (level == 1) cout << menu1[i];
			else if (level == 2) cout << menu2[i];
			else cout << menu3[i];

			cout << endl;
		}

		if (tmp == 13)
		{
			if (level == 1)
				cursor == 0 ? level = 2 : level = 3;
			else
			{
				system("cls");
				if (level == 2)
					switch (cursor)
					{
					case 0:
						students[getTheStudentIndex(students)]->printStudentInfo();
						break;

					case 1:
						printBookByID(students);
						break;

					case 2:
						printStudent(students);
						break;

					case 3:
						printBooks(students);
						break;
					}
				else
					switch (cursor)
					{
					case 0:
						students.push_back(newStudent());
						break;

					case 1:
						students.erase(students.begin() + getTheStudentIndex(students));
						cout << "Done!\n";
						break;

					case 2:
						addBookStudent(students);
						break;

					case 3:
						removeBookStudent(students);
						break;

					case 4:
						addBookLibrary(students);
						break;

					case 5:
						removeBookLibrary(students);
						break;

					case 6:
						changeBookID(students);
						break;

					case 7:
						getFromFile(students);
						break;

					case 8:
						getToFile(students);
						break;
					}
				system("pause");
			}
			isMenuOut = false;
			cursor = 0;
		}
		else if (tmp == 27)
		{
			if ((level == 2) || (level == 3))
			{
				level = 1;
				tmp = 0;
			}	

			isMenuOut = false;
			cursor = 0;
		}

	} while (tmp != 27);

	system("cls");
	puts("Thanks for using our product! \n\n\n");
}

int main()
{
	srand((unsigned int)time(nullptr));
	vector<studentBase *> students;

	menu(students);
	
	system("pause");
	return 0;
}
