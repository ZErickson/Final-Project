#pragma once
#include <vector>
#include <string>
#include "character.h"
#include "word.h"

using namespace std;

class rS {
	vector <Character> racialIdentifiers;
	vector <string> middleEastMuslimStereotypes;
	vector <string> nativeAmericanStereotypes;
	vector <string> latinoStereotypes;
	vector <string> africanAmericanStereotypes;
	//vector <string> genPOCStereotypes;
	vector <string> foundIdentifiers;
	vector <string> foundStereotypes;

	//rewrite input file
	void inputFile(ifstream& fin, string File_Name, vector <string>& words);
	void setRacialIdentifiers();
	void setMEMStereotypes();
	void setNAStereotypes();
	void setLStereotypes();
	void setAAStereotypes();
	//void setGPOCStereotypes();
	void setFoundIndentifiers();
	void setFoundStereotypes();
	bool inList(string Word, vector <string>& List);
	
};