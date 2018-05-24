#ifndef BohrVertex_HPP
#define BohrVertex_HPP

#include "libs.hpp"

using namespace std;

class Bohr_Vertex
{
	friend class Bohr_Tree;

	// constructor
	Bohr_Vertex(wchar_t symb, int parrentLink = -1) : symb(symb), parrentLink(parrentLink),
		suffLink(-1), correctSuffLink(-1), isEndOfPattern(false) { }
		
	// data
	map <wchar_t, int> listOfNextVertex;
	map <wchar_t, int>	moves;

	vector <int> patternNum;
	wchar_t symb;
	int parrentLink;
	int suffLink;
	int correctSuffLink;
	bool isEndOfPattern;
};

#endif //BohrVertex_HPP
