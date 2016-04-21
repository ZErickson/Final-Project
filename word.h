#pragma once

#include <string>
#include <vector>

using namespace std;

class Word {

	string word;
	int frequency;


public:
	Word();
	Word(string My_Word);

	string Get_Word();
	int Get_Frequency();
	void Set_Word(string My_Word);
	void Set_Frequency(int n);

	//A printing function
	void Print_Word();

	//Is the word in a list
	bool In_List(vector <string> List);
	//A function to increment a word's frequency
	void Increment();
	bool Contains_No_Lowercase();

};