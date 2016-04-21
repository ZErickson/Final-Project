#include "character.h"
#include "word.h"
#include <vector>
#include <string>

using namespace std;

Character::Character()
{

}
//Character::Character(string Character_Name)
//
void Character::Set_Name(Word This_Word)
{
	Name = This_Word;
}

void Character::Set_Lines(vector <string> Script)
{
	for (int j = 0; j < Script.size(); j++)
	{
		if (Name.Get_Word() == Script[j])
		{
			string This_Line = "";
			j++;

			//We wish to look at the subsequent lines in the script.
			//The first test is so we don't step off the end of the script if we are at the end.
			//The second is testing to see if there is a blank line in the script
			//which signifies the end of the line as we see it.
			while (j < Script.size() && Script[j] != "")
			{
				This_Line = This_Line + Script[j];
				j++;
			}

			if (This_Line != "")
			{
				Lines.push_back(This_Line);
			}
			//Because we increment before testing, we should decrement when we fail the test.
			j--;
		}
	}
}

Word Character::Get_Name()
{
	return Name;
}
vector <string> Character::Get_Lines()
{
	return Lines;
}

//This is our static function.  It is only declared as static in the header file.
vector <Word> Character::Possible_Characters(vector <string> Script)
{
	vector <Word> Capitals;

	for (int i = 0; i < Script.size(); i++)
	{
		//Convert the word in the script to a word
		//so we can evoke the Not_All_Caps function
		Word Current_Word(Script[i]);

		//This Means we have something
		//with all caps, spaces, symbols, etc.
		if (Current_Word.Contains_No_Lowercase() == true)
		{
			bool Been_Seen = false;
			for (int j = 0; j < Capitals.size(); j++)
			{
				if (Script[i] == Capitals[j].Get_Word())
				{
					Been_Seen = true;
					Capitals[j].Increment();
				}
			}
			//If we have gone through all the words in Capitals
			//and not seen the word, it is new.  Add it to Capitals
			//along with a value of 1 since we have seen it.
			if (Been_Seen == false)
			{
				Current_Word.Increment();
				Capitals.push_back(Current_Word);
			}
		}
	}

	return Capitals;
}
