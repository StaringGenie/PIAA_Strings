#include "../hdr/BohrTree.hpp"

int main()
{
	//////////////////////////////////AHO_KORASIK/////////////////////////////
	setlocale(LC_ALL, "");
	wstring text;
	size_t howMuchPatterns;
	wcin >> text >> howMuchPatterns;

	Bohr_Tree AKsearch;

	vector <wstring> patterns;

	for (size_t i = 0; i<howMuchPatterns; i++)
	{
		wstring tmp;
		wcin >> tmp;
		patterns.push_back(tmp);
	}

	vector <Result> results = AKsearch.searchSubstringsByBohr(text, patterns);
	sort(results.begin(), results.end());

	for (size_t i = 0; i < results.size(); i++)
		wcout << results[i].first << " " << results[i].second << endl;
	
	return 0;
}