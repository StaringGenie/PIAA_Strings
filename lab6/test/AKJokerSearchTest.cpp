#include <gtest/gtest.h>
#include "../hdr/BohrTree.hpp"

using ::testing::TestWithParam;
using ::testing::Values;

typedef vector <int> resVec;

struct AKJokerSearchTestStruct
{
    wstring text;
	wstring joker;
	wchar_t   jokerSymb;
	resVec expRes;
};

class AKJokerSearchFixture : public TestWithParam<AKJokerSearchTestStruct>
{
public:
	virtual void SetUp()
	{
		Bohr_Tree AKsearch;
		res = AKsearch.searchJokerByBohr(GetParam().text, GetParam().joker, GetParam().jokerSymb);
		sort(res.begin(), res.end());
	}
	virtual void TearDown() { res.clear(); }

protected:
	resVec res;
};

INSTANTIATE_TEST_CASE_P(AKJokerSearch_Incomplete_TestCase, AKJokerSearchFixture, 
Values(
	AKJokerSearchTestStruct{L" ", L"A&A", L'&', 				resVec()},
	AKJokerSearchTestStruct{L"KACKA", L"A&A", L'&', 			resVec()}
));

INSTANTIATE_TEST_CASE_P(AKJokerSearch_Simple_TestCase, AKJokerSearchFixture, 
Values(
	AKJokerSearchTestStruct{L"JOKER", L"J&K&R", L'&',		 	resVec({1})},
	AKJokerSearchTestStruct{L"JOJOREFERENCE", L"J&", L'&',		resVec({1,3})}
));

INSTANTIATE_TEST_CASE_P(AKJokerSearch_Complex_TestCase, AKJokerSearchFixture, 
Values(
	AKJokerSearchTestStruct{L"AAAAAABA", L"A&", L'&', 					resVec({1,2,3,4,5,6})},
	AKJokerSearchTestStruct{L"JOJOREFERENCE", L"J&&&&&&&&&&&&", L'&', 	resVec({1})},
	AKJokerSearchTestStruct{L"WHYJOKERISLETTER", L"EM", L'M', 			resVec({7,12,15})},
	AKJokerSearchTestStruct{L"ACACACAC", L"A&A", L'&', 				resVec({1,3,5})},
	AKJokerSearchTestStruct{L"РУСЙQAЙF", L"Й&", L'&', 				resVec({4,7})}
));

TEST_P(AKJokerSearchFixture, AKJokerSearchTestStruct) {
    ASSERT_EQ(GetParam().expRes, res);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}