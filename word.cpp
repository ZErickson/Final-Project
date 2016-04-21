#include "word.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

Word::Word()
{
	word = "";
	frequency = 0;
}

Word::Word(string My_Word)
{
	word = My_Word;
	frequency = 0;
}

string Word::Get_Word()
{
	return word;
}

int Word::Get_Frequency()
{
	return frequency;
}

void Word::Set_Word(string My_Word)
{
	word = My_Word;
}
void Word::Set_Frequency(int n)
{
	if (n >= 0)
	{
		frequency = n;
	}
}

//A printing function
void Word::Print_Word()
{
	cout << "The word " << word << " appears in the text " << frequency << " times." << endl;
}

//Is the word in a list
bool Word::In_List(vector <string> List)
{
	bool Ret_Val = false;
	for (int i = 0; i < List.size(); i++)
	{
		if (word == List[i])
		{
			Ret_Val = true;
		}
	}

	return Ret_Val;
}
//A function to increment a word's frequency
void Word::Increment()
{
	frequency++;
}

bool Word::Contains_No_Lowercase()
{
	bool Ret_Val = true;

	//For now, I am stating that the empty word is NOT an all caps word.
	if (word == "")
	{
		Ret_Val = false;
	}
	else
	{
		for (int i = 0; i < word.size(); i++)
		{
			if (islower(word[i]))
			{
				Ret_Val = false;
			}
		}
	}

	return Ret_Val;
}