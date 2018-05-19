#include "../hdr/KMPfunc.hpp"

int main()
{
	string first;
	string second;
	cin >> first >> second;

	if (first.size() != second.size())
		cout << -1;
	else
	{
		int tmp = 0;
		vector <size_t> result = KMP(second, first + first, tmp);
		if (result.size())
			cout << result[0] << endl;
		else
			cout << -1 << endl;
	}
	return 0;
}