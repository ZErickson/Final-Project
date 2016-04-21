#pragma once

#include <vector>
#include <string>
#include "word.h"

using namespace std;

class Character
{
	Word Name;
	vector <string> Lines;

public:
	Character();
	//Character(string Character_Name);

	void Set_Name(Word This_Word);
	void Set_Lines(vector <string> Script);

	Word Get_Name();
	vector <string> Get_Lines();

	//A function that looks at a Script and Determines
	//Potential Characters
	static vector <Word> Possible_Characters(vector <string> Script);

};