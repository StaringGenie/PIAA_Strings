#include "../hdr/KMPfunc.hpp"
#include <random>
#include <time.h>


// YOU CAN CONFIGURE GENERATION PARAMS HERE
#define ALPHABET_SIZE 26
#define HOW_MUCH_TEXTS 4
#define TEXT_SIZE 60000
#define TEXT_MAX_ADDED_SIZE 16666
#define HOW_MUCH_PATTERNS 200
#define PATTERN_SIZE 100
#define PATTERN_MAX_ADDED_SIZE 50

string RandString(int addedSize, int constantSize) {
	string str = "";
	int strsize = constantSize + rand() % addedSize;
	for (int i = 0; i< strsize; i++) {
		str += (char)(rand() % ALPHABET_SIZE + 'A');
	}
	return str;
}

int main() {
	srand(time(NULL));

	cout << "\n>> Heya!\n>> Now generating tests";

	vector<string> temps(HOW_MUCH_PATTERNS);
	for (int i = 0; i<HOW_MUCH_TEXTS; i++) {
		for (int j = 0; j<(HOW_MUCH_PATTERNS / HOW_MUCH_TEXTS); j++) {
			temps[j + i * (HOW_MUCH_PATTERNS / HOW_MUCH_TEXTS)] = RandString(PATTERN_SIZE, PATTERN_MAX_ADDED_SIZE);
		}
	}
	vector<string> texts(HOW_MUCH_TEXTS);
	for (int i = 0; i<HOW_MUCH_TEXTS; i++)
	{
		cout << ".";
		int limit = TEXT_SIZE + (rand() % TEXT_MAX_ADDED_SIZE) - (PATTERN_SIZE + PATTERN_MAX_ADDED_SIZE);
		while (texts[i].size() < limit)
		{
			texts[i] += temps[rand() % (HOW_MUCH_PATTERNS)];
		}
	}

	cout << "\n\n>> DONE!\n\n>> Now searching all substrings in all strings, this can take a while, please wait";

	int counter = 0;
	for (int i = 0; i<HOW_MUCH_TEXTS; i++) {
		cout << ".";
		for (int j = 0; j<(HOW_MUCH_PATTERNS / HOW_MUCH_TEXTS); j++) {
			vector<size_t> pi = prefix_function(temps[j + i * (HOW_MUCH_PATTERNS / HOW_MUCH_TEXTS)]);
			int s1 = 0, s2 = 0;
			vector<size_t> index1 = KMP(temps[j + i * (HOW_MUCH_PATTERNS / HOW_MUCH_TEXTS)], texts[i], s1);
			vector<size_t> index2 = naive(temps[j + i * (HOW_MUCH_PATTERNS / HOW_MUCH_TEXTS)], texts[i], s2);
			if (s2<s1)
				counter++;
		}
	}
	cout << "\n\n>> DONE!\n\n>> Text length equal from " << TEXT_SIZE << " to " << TEXT_SIZE + TEXT_MAX_ADDED_SIZE << " symbols.\n";
	cout << ">> Pattern length equal from " << PATTERN_SIZE << " to " << PATTERN_SIZE + PATTERN_MAX_ADDED_SIZE << " symbols.\n";
	cout << ">> Number of texts is " << HOW_MUCH_TEXTS << ".\n>> Number of patterns for every text is " << HOW_MUCH_PATTERNS / HOW_MUCH_TEXTS << ".\n";
	cout << ">> Counter of cases when naive algo was more effective than KMP algo is " << counter << endl;
	return 0;
}