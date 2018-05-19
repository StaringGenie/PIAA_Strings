#include "../hdr/KMPfunc.hpp"

int main()
{
	string pattern;
	string text;
	cin >> pattern >> text;
	int operations = 0;
	vector <size_t> positionsInText = KMP(pattern, text, operations);
	for (int i = 0; i < int(positionsInText.size() - 1); i++)
		cout << positionsInText[i] << ",";
	if (positionsInText.empty())
		cout << -1 << endl;
	else
		cout << positionsInText.back() << endl;
	return 0;
}