#include "../hdr/KMPfunc.hpp"

vector<size_t> prefix_function(const string & s)
{
	size_t n = s.length();
	vector<size_t> pi(n,0);
	for (size_t i = 1; i < n; ++i)
	{
		size_t j = pi[i - 1];
		while ((j > 0) && (s[i] != s[j]))
			j = pi[j - 1];
		if (s[i] == s[j])
			++j;
		pi[i] = j;
	}
	return pi;
}

vector <size_t> KMP(const string & pattern, const string & text, int & operations)
{
	vector <size_t> prefix = prefix_function(pattern);
	vector <size_t> result;


	for (size_t k = 0, i = 0; i < text.length(); ++i)
	{
		while ((k > 0) && (pattern[k] != text[i]))
		{
			operations++;
			k = prefix[k - 1];
		}

		operations++;
		if (pattern[k] == text[i])
			k++;

		if (k == pattern.length())
			result.push_back(i - pattern.length() + 1);
	}
	return result;
}

vector <size_t> naive(const string& pattern, const string& text, int & operations)
{
	vector<size_t> index;

	if (pattern.size() > text.size())
		return index;

	for (size_t i = 0; i < text.size() - pattern.size() + 1; i++)
	{
		for (size_t j = 0; j < pattern.size(); j++)
		{
			operations++;
			if (pattern[j] == text[i + j])
			{
				if (j == pattern.size() - 1)
					index.push_back(i);
			}
			else
				break;
		}
	}
	return index;
}
