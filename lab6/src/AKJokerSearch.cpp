#include "../hdr/BohrTree.hpp"

int main()
{
	/////////////////////////////////JOKER///////////////////////////////////
	setlocale(LC_ALL, "");
	wstring text;
	wstring joker;
	wchar_t jokerSymb;
	wcin >> text >> joker >> jokerSymb;

	Bohr_Tree AKsearch;

	vector <int> result = AKsearch.searchJokerByBohr(text, joker, jokerSymb);
	sort(result.begin(), result.end());

	for (size_t i = 0; i < result.size(); i++)
		wcout << result[i] << endl;
	
	return 0;
}