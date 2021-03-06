#ifndef KMPfunc
#define KMPfunc

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <size_t> prefix_function(const string & s);
vector <size_t> KMP(const string & pattern, const string & text, int & operations);
vector <size_t> naive(const string & pattern, const string & text, int & operations);

#endif //KMPfunc
