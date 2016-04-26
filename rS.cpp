#include "rS.h"
#include "character.h"
#include "word.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void rS::inputFile(ifstream& fin, string File_Name, vector <string>& words)
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
		}

		fin.close();
	}
	else
	{
		cout << "Sorry, there was an error opening the file" << endl;
	}
}
void rS::setRacialIdentifiers()
{
	
}
void rS::setMEMStereotypes()
{
	ifstream fin;
	string MEMSPath;
	inputFile(fin, MEMSPath, middleEastMuslimStereotypes);
}
void rS::setNAStereotypes()
{
	ifstream fin;
	string NASPath;
	inputFile(fin, NASPath, nativeAmericanStereotypes);
}
void rS::setLStereotypes()
{
	ifstream fin;
	string LSPath;
	inputFile(fin, LSPath, latinoStereotypes);
}
void rS::setAAStereotypes()
{
	ifstream fin;
	string AASPath;
	inputFile(fin, AASPath, middleEastMuslimStereotypes);
}
//void setGPOCStereotypes();
void rS::setFoundIndentifiers()
{

}

void rS::setFoundStereotypes()
{

}

bool rS::inList(string Word, vector <string>& List)
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