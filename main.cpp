#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <cctype>
#include <time.h>
#include "word.h"
#include "character.h"

using namespace std;

// This function removes all but lowercase and uppercase letters from a string.
string Remove_Punctuation(string word);
//This function converts a word to its lower case equivalent.
string To_Lower(string word);
//This function opens a file and reads in its contents
void Input_File(ifstream& fin, string File_Name, vector <string>& words);
//This function counts valid Dictionary words in the script using our old techniques.
int Num_Valid_Words(vector <string>& Dictionary, vector <string> Script);
//Our binary method for searching the Dictionary.
bool Is_Dictionary_Word(string Word, vector <string>& Dictionary);
// A function that searches a file linearly.
bool In_List(string Word, vector <string>& List);
//Tell is if a string contains only capital letters.
bool All_caps(string Word);
//Tell is if a string contains only capital letters, punctuation, and spaces.
static bool No_Lowercase(string Word);
//A one line function to update the percent part of a Word_Frequency
double Get_Percent(int frequency, int Script_Size);
//Sort a vector of word frequencies according to their frequency.
void Sort_Word(vector <Word>& List);
//A function that finds and counts all words in all caps in our list of Questionable Words.
vector <Word> Count_Questionable_Caps(vector <string>& List, int Script_Size);
//A function that removes the character names from the list of questionable words.
vector <string> Remove_Words(vector <string> Questionable_Words, vector <Word> These_Words);
//A function that counts words in a list where a given word is a prefix
vector <Word> Update_Root_Frequencies(ifstream& fin, string File_Name, vector <string>& List);
//A function that counts words in a list EXACTLY as they appear
vector <Word> Update_Exact_Frequencies(ifstream& fin, string File_Name, vector <string>& List);
//A function that counts the total frequencies in a vector of Words
int Total_Frequency(vector <Word>& List);

int main()
{
	ifstream fin;
	vector <string> Script;

	//Location on MY computer of the Script we are using
	string Script_File = "C:\\Users\\sjensen\\Desktop\\Scripts\\ForrestGump.txt";

	Input_File(fin, Script_File, Script);

	//Just a test to see what the default constructor does.
	Character My_Character;

	My_Character.Get_Name().Print_Word();
	cout << My_Character.Get_Lines().size() << endl;

	//The Possible_Characters function is located in the Character class.
	//However, it is a static function, meaning its value is not specific
	//to an individual occurence of the Character data type.
	//We use the Character:: instead of the dot notation in this case.
	vector <Word> Capital_Words = Character::Possible_Characters(Script);

	//This sorts the Capitals According to their frequency.
	Sort_Word(Capital_Words);

	vector <Character> Cast_Of_Characters;

	cout << Capital_Words.size() << endl;
	for (int i = 0; i < Capital_Words.size(); i++)
	{
		//cout << i << " " << Capital_Words[i].Get_Word() << endl;
		Character Current_Character;
		Current_Character.Set_Name(Capital_Words[i]);
		Current_Character.Set_Lines(Script);

		if (Current_Character.Get_Lines().size() > 0)
		{
			Cast_Of_Characters.push_back(Current_Character);
		}
	}

	for (int i = 0; i < Cast_Of_Characters.size(); i++)
	{
		Cast_Of_Characters[i].Get_Name().Print_Word();
	}

	system("pause");
	return 0;
}

string Remove_Punctuation(string word)
{
	string New_Word = "";
	for (int i = 0; i < word.length(); i++)
	{
		//We have a capital letter
		if (word[i] >= 'A' && word[i] <= 'Z')
		{
			New_Word = New_Word + word[i];
		}
		//Test for lower case letter
		else if (word[i] >= 'a' && word[i] <= 'z')
		{
			New_Word = New_Word + word[i];
		}
	}

	return New_Word;
}

//Convert a string to contain only lowercase letters
string To_Lower(string word)
{
	string New_Word = word;
	for (int i = 0; i < word.length(); i++)
	{
		New_Word[i] = tolower(word[i]);
	}

	return New_Word;
}

void Input_File(ifstream& fin, string File_Name, vector <string>& words)
{
	fin.open(File_Name);

	//Check to see that the file did in fact open
	if (fin.is_open())
	{
		while (fin.good())
		{
			string Current_Word;
			getline(fin, Current_Word);
			words.push_back(Current_Word);

			//Current_Word = Remove_Punctuation(Current_Word);

			//Adding an if statement so we do not add the word if it becomes the
			//empty word after removing punctuation.
			/*if (Current_Word.size() > 0)
			{
			words.push_back(Current_Word);
			}*/
		}

		fin.close();
	}

	//If the file did not open, alert the user.
	else
	{
		cout << "Sorry, there was an error opening the file" << endl;
	}
}

int Num_Valid_Words(vector <string>& Dictionary, vector <string> Script)
{

	//Counter is going to count VALID words.
	int counter = 0;
	//First, step through all words in the script.
	for (int i = 0; i < Script.size(); i++)
	{
		//The dictionary uses lowercase words.  We must change the script words to
		//their lowercase equivalents before searching for them.
		string Current_Word = To_Lower(Script[i]);

		//Second, step through all words in the dictionary.
		for (int j = 0; j < Dictionary.size(); j++)
		{
			//If the current word is a dictionary word, count.
			//Then don't bother searching the rest of the dictionary words.
			if (Current_Word == Dictionary[j])
			{
				counter++;
				break;
			}
		}
	}

	return counter;

}

bool Is_Dictionary_Word(string Word, vector <string>& Dictionary)
{
	bool Ret_Val = false;


	//Binary search ONLY to be used on a sorted list.
	//start by looking at the middle word.  Then ask, is the word equal, before this word, or after this word?
	int lower = 0;
	int higher = Dictionary.size() - 1;
	int middle = (higher + lower) / 2;

	while (lower <= higher)
	{
		//We got lucky! 
		if (Word == Dictionary[middle])
		{
			Ret_Val = true;
			break;
		}
		//The word comes earlier in the dictionary.  
		else if (Word < Dictionary[middle])
		{
			higher = middle - 1;
			middle = (higher + lower) / 2;
		}
		//The word comes later in the dictionary
		else
		{
			lower = middle + 1;
			middle = (higher + lower) / 2;
		}
	}

	return Ret_Val;
}


bool In_List(string Word, vector <string>& List)
{
	for (int i = 0; i < List.size(); i++)
	{
		if (List[i] == Word)
		{
			return true;
		}
	}

	return false;
}

bool All_caps(string Word)
{
	bool Ret_Val = true;

	for (int i = 0; i < Word.length(); i++)
	{
		// 0 means the character is NOT uppercase.  The function lists in C++ as an integer returning function
		//but we tested it in class and it really seems to be a boolean function
		if (isupper(Word[i]) == 0)
		{
			Ret_Val = false;
		}
	}
	return Ret_Val;
}

double Get_Percent(int frequency, int Script_Size)
{
	return double(frequency) / Script_Size * 100;
}

//A function that bubble sorts our lists of Words according to frequency
void Sort_Word(vector <Word>& List)
{
	for (int i = List.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (List[j].Get_Frequency() > List[j + 1].Get_Frequency())
			{
				swap(List[j], List[j + 1]);
			}
		}
	}
}

vector <Word> Count_Questionable_Caps(vector <string>& List, int Script_Size)
{
	vector <Word> Capitals;

	//Search through Questionable_Words looking for things
	//in all caps ONLY.
	for (int i = 0; i < List.size(); i++)
	{
		if (All_caps(List[i]))
		{
			//This is an example of a boolean flag.  It tells us if we have completed the loop 
			//without seeing a new word or if the word has been altered.
			bool New_Word = true;

			for (int j = 0; j < Capitals.size(); j++)
			{
				//If I've seen this word before, count it again.
				if (Capitals[j].Get_Word() == List[i])
				{
					Capitals[j].Increment();
					New_Word = false;
				}
			}
			//If the word is not already in my list, add it to the list and count it.
			if (New_Word == true)
			{
				Word My_Word;
				My_Word.Set_Word(List[i]);
				My_Word.Set_Frequency(1);
				Capitals.push_back(My_Word);
			}
		}
	}

	return Capitals;
}

vector <string> Remove_Words(vector <string> Questionable_Words, vector <Word> These_Words)
{
	vector <string> New_Questionables;

	for (int i = 0; i < Questionable_Words.size(); i++)
	{
		string Current_Word = Questionable_Words[i];
		bool In_List = false;

		for (int j = 0; j < These_Words.size(); j++)
		{
			if (To_Lower(These_Words[j].Get_Word()) == To_Lower(Current_Word))
			{
				In_List = true;
			}
		}

		if (In_List == false)
		{
			New_Questionables.push_back(Current_Word);
		}
	}

	return New_Questionables;
}

//A function that counts words in a list
vector <Word> Update_Root_Frequencies(ifstream& fin, string File_Name, vector <string>& List)
{
	vector <Word> To_Return;

	//Read in the words to check List for from File_Name
	vector <string> As_Strings;
	Input_File(fin, File_Name, As_Strings);


	//Converts the strings in the file to Word data type.
	for (int i = 0; i < As_Strings.size(); i++)
	{
		Word This_Word(As_Strings[i]);
		To_Return.push_back(This_Word);
	}

	for (int i = 0; i < To_Return.size(); i++)
	{
		//These definitions are to avoid clutter in the following code
		Word Current_Word = To_Return[i];
		string Current_String = To_Lower(Current_Word.Get_Word());
		int Current_Size = Current_String.size();

		for (int j = 0; j < List.size(); j++)
		{
			// look for the root of the word to account for possible endings or 
			//creative use of the word
			string Sub_String = List[j].substr(0, Current_Size);
			Sub_String = To_Lower(Sub_String);

			if (Current_String == Sub_String)
			{
				To_Return[i].Increment();
			}
		}
	}


	return To_Return;
}

//A function that counts words in a list
vector <Word> Update_Exact_Frequencies(ifstream& fin, string File_Name, vector <string>& List)
{
	vector <Word> To_Return;

	//Read in the words to check List for from File_Name
	vector <string> As_Strings;
	Input_File(fin, File_Name, As_Strings);


	//Converts the strings in the file to Word data type.
	for (int i = 0; i < As_Strings.size(); i++)
	{
		Word This_Word(As_Strings[i]);
		To_Return.push_back(This_Word);
	}

	for (int i = 0; i < To_Return.size(); i++)
	{
		Word Current_Word = To_Return[i];
		string Current_String = To_Lower(Current_Word.Get_Word());
		int Current_Size = Current_String.size();

		for (int j = 0; j < List.size(); j++)
		{
			string List_Word = To_Lower(List[j]);

			if (Current_String == List_Word)
			{
				To_Return[i].Increment();
			}
		}
	}

	return To_Return;
}

//A function that counts the total frequencies in a vector of Words
int Total_Frequency(vector <Word>& List)
{
	int Ret_Val = 0;

	for (int i = 0; i < List.size(); i++)
	{
		Ret_Val = Ret_Val + List[i].Get_Frequency();
	}

	return Ret_Val;
}

//Tell is if a string contains only capital letters, punctuation, and spaces.
bool No_Lowercase(string Word)
{
	bool Ret_Val = true;

	//For now, I am stating that the empty word is NOT an all caps word.
	if (Word == "")
	{
		Ret_Val = false;
	}
	else
	{
		for (int i = 0; i < Word.size(); i++)
		{
			if (islower(Word[i]))
			{
				Ret_Val = false;
			}
		}
	}

	return Ret_Val;
}