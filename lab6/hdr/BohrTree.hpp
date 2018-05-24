#ifndef BohrTree_HPP
#define BohrTree_HPP

#include "BohrVertex.hpp"

using namespace std;

typedef pair<int, int> Result;

class Bohr_Tree
{
public:
	Bohr_Tree();

	// public method for start default searching patterns in text
	vector<Result> searchSubstringsByBohr(const wstring & text, const vector <wstring> & patterns);

	// public method for start searching joker pattern in text
	vector<int> searchJokerByBohr(const wstring & text, const wstring & joker, wchar_t jokerSymb);

private:

	// Default methods for build bohr tree Aho Korasik ed.
	void addStrToBohr(const wstring & pattern, int numberOfPattern);
	int getSuffLink(int vertexNum);
	int getAutoMove(int vertexNum, wchar_t symb);
	int getCorrectSuffLink(int vertexNum);

	// Parse bohr tree for joker search
	void SubstringsCheck(int vertexNum, int currentPos, const vector <wstring> & patterns, vector <Result> & results);

	// Parse bohr tree for default substrings search
	void JokerCheck(int vertexNum, int currentPos, vector <int> & results, vector <int> & background, vector <size_t> & lengths, size_t jokerLength);

	// Split joker for substrings without joker symb
	vector <size_t> jokerParse(const wstring & jokerPattern, wchar_t joker);

	// data
	vector <Bohr_Vertex> bohr;
};

#endif //BohrTree_HPP
