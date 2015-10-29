//input and output to the console
#include<iostream>
//for some date and time stuff
#include<ctime>
//the two below are for file handling
#include<fstream>
#include<ostream>
//because it's logical to develop a programming language without native handing of strings
#include<string>
using namespace std;

//function prototyping here
void viewLibrary();
void addAnime();
void sortAndUpdate();
void displayMenu();
void displayAnimeLog();

int main()
{
	//variable declaration here
	string junk;
	char userChoice = 'x';
	int userOpt = 0;

	//this welcomes the user to the program
	cout << "Hello and welcome to your offline anime library." << endl;

	
	//I'm going to make a menyu, because it seems logical?
	displayMenu();

	//collects the user's numerical response
	cin >> userOpt;

	switch(userOpt)
	{
	case 0:
	{
		exit(0);
	}
	case 1:
	{
		//displays the 'database'
		viewLibrary();
		break;
	}
	case 2:
	{
		userChoice = 'Y';
		while (userChoice == 'Y')
		{
			addAnime();
			cout << "Would you like to add more anime?" << endl;
			cin >> userChoice;
		}
		break;
	}
	case 3:
	{
		sortAndUpdate();
		//asks the user if they want to view the newly updated file
		cout << "Would you like to see your newly composed anime library?";
		cin >> userChoice;
		//#if the user entered 'Y', they get to see the database.
		if (userChoice == 'Y')
		{
			viewLibrary();
		}
		else
		{
			break;
		}
		break;
	}
	case 4:
	{
		displayAnimeLog();
		break;
	}
	default:
	{
		cout << "Error, please enter a number of one of the above options." << endl;
	}
	}
	
	userChoice = 'Y';
	while (userChoice == 'Y')
	{
		cout << "Would you like to do anything else?";
		getline(cin, junk);
		//getline(cin, junk);//because garbage seems to be happening
		cin >> userChoice;

		if (userChoice == 'Y')
		{
			displayMenu();
			cin >> userChoice;
		}
		else if (userChoice != 'Y')
		{
			break;
		}
	}

	//used to pause the program
		cout << "Enter any combination of alphanumeric characters to exit." << endl;
		getline(cin, junk);
	return 0;
}
/*
Purpose: to simply display the list of anime that is contained in the text file.
*/
void viewLibrary()
{
	//open the file in a read only designation
	ifstream fileOpen("animeList.txt");
	string animeList;
	string line;

		//#tells the user what anime is in their library
	cout << "Your anime library is:" << endl;
	if (fileOpen.good())
	{
		while (getline(fileOpen, line))
		{
			cout << line << '\n';
		}
		fileOpen.close();
	}
		cout << endl;
}
/*
Purpose: To allow the user to add an anime to the file and then append the file with it at the bottom. Separate function
for sorting
*/
void addAnime()
{
	//variable declaration
	string animeAdditions;
	ofstream fileOpen ("animeList.txt", ios::app);
	string junk;
	//fileOpen.open("animeList.txt", "a")
	cout << "Please note that this does not check for existing anime." << endl << endl;
	cout << "Type the name of the anime you would like to add. (One at a time, please)" << endl;

	//this clears the input buffer before accepting the user's new anime entry.
	getline(cin, junk);

	getline(cin, animeAdditions);
	//fileOpen ("animeList.txt", "a"); //#because I simply want to append, not replace.
	fileOpen << animeAdditions;
	fileOpen << "\n";
	fileOpen.close();
	fileOpen.open("animeLog.txt", ios::app);

	/*
	http://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
	*/
	//string dateTime;
		time_t now = time(0);

		//the variable that holds the date and time is dateTime
		char* dateTime= ctime(&now);

		//#writes the string of the date and time to the file
		fileOpen << dateTime; //this forces a line break, because that's how it rolls
		//fileOpen << ", ";
		fileOpen << animeAdditions << "\n"; //this is on another line, and I removed the comma from being in here
		//just in case I want to create a separate function to display the log data.

		//#obviously closes the file
		fileOpen.close();
	return;
}
/*
Purpose: This simple calls the Python Program I've written to sort my anime for me.
*/
void sortAndUpdate()
{
	//this calls my Python program that sorts my anime list and then writes the sorted into to the file
	system("start sortAnime.py");
	return;
}
/*
Purpose: to be called by whatever needs it as it is needed.
*/
void displayMenu()
{
	//variable declaration
	string menuOptions[5] = { "Exit", "View Library", "Add New Anime", "Sort Library", "Display Log of Added Anime" };

	//the inner workings here
	cout << "Your menu options are:" << endl;
	for (int b = 0; b < 5; b++)
	{
		cout << b << " - " << menuOptions[b] << endl;
	}
}

void displayAnimeLog()
{
	//variable declaration
	string dateStamp;
	string animeName;
	ifstream fileOpen("animeLog.txt");
	NULL;

	if (fileOpen.good())
	{
		while (fileOpen.good())
		{
			getline(fileOpen, dateStamp);
			getline(fileOpen, animeName);

			//if there isn't any more date stamps, the first line for each anime logged, then stop and don't output anything.
			if (dateStamp == "")
			{
				cout << endl;
				displayMenu();
			}
			else if (dateStamp == "\n")
			{
				cout << endl;
				displayMenu();
			}
			else if (dateStamp != " ")
			{
				cout << "The anime " << animeName << " was added on " << dateStamp << endl;
			}
			else if (dateStamp == " ")
			{
				main();
			}
			else if (dateStamp == "\n")
			{
				main();
			}

			if (fileOpen.bad())
			{
				cout << endl;
				displayMenu();
			}
			else
			{
				//do nothing
			}

			//cout << "The anime " << animeName << " was added on " << dateStamp << endl;
			//cout << line << '\n';
		}
		fileOpen.close();
	}
	else if (fileOpen.bad())
	{
		cout << "Your file has not been found OR an error opening/reading from the file has happened. Please check your file." << endl;
	}

	return;
}
