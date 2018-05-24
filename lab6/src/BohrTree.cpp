#include "../hdr/BohrTree.hpp"

Bohr_Tree::Bohr_Tree() { bohr.push_back(Bohr_Vertex(-1)); }

void Bohr_Tree::addStrToBohr(const wstring & pattern, int numberOfPattern)
{
	int vertexNum = 0;

	for (size_t i = 0; i < pattern.size(); i++)
	{
		if (bohr[vertexNum].listOfNextVertex.find(pattern[i]) == bohr[vertexNum].listOfNextVertex.end())
		{

			bohr.push_back(Bohr_Vertex(pattern[i], vertexNum));
			bohr[vertexNum].listOfNextVertex[pattern[i]] = bohr.size() - 1;
		}

		vertexNum = bohr[vertexNum].listOfNextVertex[pattern[i]];

	}

	bohr[vertexNum].patternNum.push_back(numberOfPattern);
	bohr[vertexNum].isEndOfPattern = true;

}

int Bohr_Tree::getSuffLink(int vertexNum)
{
	if (bohr[vertexNum].suffLink == -1)
	{
		if (vertexNum == 0 || bohr[vertexNum].parrentLink == 0)
			bohr[vertexNum].suffLink = 0;
		else
			bohr[vertexNum].suffLink = getAutoMove(getSuffLink(bohr[vertexNum].parrentLink), bohr[vertexNum].symb);
	}

	return bohr[vertexNum].suffLink;
}

int Bohr_Tree::getAutoMove(int vertexNum, wchar_t symb)
{
	if (bohr[vertexNum].moves.find(symb) == bohr[vertexNum].moves.end())
	{
		if (bohr[vertexNum].listOfNextVertex.find(symb) != bohr[vertexNum].listOfNextVertex.end())
			bohr[vertexNum].moves[symb] = bohr[vertexNum].listOfNextVertex[symb];
		else
		{
			if (vertexNum == 0)
				bohr[vertexNum].moves[symb] = 0;
			else
				bohr[vertexNum].moves[symb] = getAutoMove(getSuffLink(vertexNum), symb);
		}
	}
	return bohr[vertexNum].moves[symb];
}

int Bohr_Tree::getCorrectSuffLink(int vertexNum)
{
	if (bohr[vertexNum].correctSuffLink == -1)
	{
		int tmpLink = getSuffLink(vertexNum);
		if (tmpLink == 0)
			bohr[vertexNum].correctSuffLink = 0;
		else
		{
			if (bohr[tmpLink].isEndOfPattern == true)
				bohr[vertexNum].correctSuffLink = tmpLink;
			else
				bohr[vertexNum].correctSuffLink = getCorrectSuffLink(tmpLink);
		}
	}
	return bohr[vertexNum].correctSuffLink;
}

void Bohr_Tree::SubstringsCheck(int vertexNum, int currentPos, const vector <wstring> & patterns, vector <Result> & results)
{
	for (int nextVertex = vertexNum; nextVertex != 0; nextVertex = getCorrectSuffLink(nextVertex))
	{
		if (bohr[nextVertex].isEndOfPattern)
			results.push_back({ currentPos - (int)patterns[bohr[nextVertex].patternNum.back()].size() + 1,
				bohr[nextVertex].patternNum.back() + 1 });
	}
}

void Bohr_Tree::JokerCheck(int vertexNum, int currentPos, vector<int>& results,
	vector<int>& background, vector<size_t>& lengths, size_t jokerLength)
{
	for (int nextVertex = vertexNum; nextVertex != 0; nextVertex = getCorrectSuffLink(nextVertex))
	{
		if (bohr[nextVertex].isEndOfPattern)
		{
			for (size_t m = 0; m < bohr[nextVertex].patternNum.size(); m++)
			{
				if ((currentPos - (int)lengths[bohr[nextVertex].patternNum[m]]) >= 0)
					if ((++background[currentPos - lengths[bohr[nextVertex].patternNum[m]]]) == (int)lengths.size())
					{
						if (background.size() - (currentPos - lengths[bohr[nextVertex].patternNum[m]]) >= jokerLength)
							results.push_back(currentPos - lengths[bohr[nextVertex].patternNum[m]] + 1);
					}
			}
		}
	}
}

vector <Result> Bohr_Tree::searchSubstringsByBohr(const wstring & text, const vector <wstring> & patterns)
{
	for (size_t i = 0; i<patterns.size(); i++)
		addStrToBohr(patterns[i], i);

	vector <Result> results;

	int vertexNum = 0;

	for (size_t i = 0; i < text.size(); i++)
	{
		vertexNum = getAutoMove(vertexNum, text[i]);
		SubstringsCheck(vertexNum, i + 1, patterns, results);
	}

	return results;
}

vector <size_t> Bohr_Tree::jokerParse(const wstring & jokerPattern, wchar_t joker)
{

	vector <size_t> lengths;

	wstring tmp;

	for (size_t i = 0; i < jokerPattern.size(); i++)
	{
		if (jokerPattern[i] == joker)
		{
			if (tmp.size() > 0)
			{
				lengths.push_back(i);
				addStrToBohr(tmp, (int)(lengths.size() - 1));
				tmp.clear();
			}
			continue;
		}
		else
			tmp.push_back(jokerPattern[i]);

		if ((i == (jokerPattern.size() - 1)) && tmp.size())
		{
			lengths.push_back(i + 1);
			addStrToBohr(tmp, (int)(lengths.size() - 1));
		}
	}

	return lengths;
}

vector<int> Bohr_Tree::searchJokerByBohr(const wstring & text, const wstring & joker, wchar_t jokerSymb)
{
	vector <int> results;
	vector <int> background(text.size(), 0);
	vector <size_t> lengths = jokerParse(joker, jokerSymb);
	int vertexNum = 0;

	for (size_t i = 0; i < text.size(); i++)
	{
		vertexNum = getAutoMove(vertexNum, text[i]);
		JokerCheck(vertexNum, i + 1, results, background, lengths, joker.size());
	}

	return results;
}
