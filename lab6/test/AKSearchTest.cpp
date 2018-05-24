#include <gtest/gtest.h>
#include "../hdr/BohrTree.hpp"

using ::testing::TestWithParam;
using ::testing::Values;

typedef vector <wstring> strVec;
typedef vector<pair<int, int>> resVec;

struct AKSearchTestStruct
{
    wstring text;
	strVec patterns;
	resVec expRes;
};

class AKSearchFixture : public TestWithParam<AKSearchTestStruct>
{
public:
	virtual void SetUp()
	{
		wstring text = GetParam().text;
		
		vector <wstring> patterns = GetParam().patterns;
		
		Bohr_Tree AKsearch;
		res = AKsearch.searchSubstringsByBohr(text, patterns);
		sort(res.begin(), res.end());
	}
	virtual void TearDown() { res.clear(); }

protected:
	resVec res;
};

INSTANTIATE_TEST_CASE_P(AKSearch_Incomplete_TestCase, AKSearchFixture, 
Values(
	AKSearchTestStruct{L" ", 	strVec({L"HELL", L"ELLO", L"EL"}), resVec({})}
));

INSTANTIATE_TEST_CASE_P(AKSearch_Simple_TestCase, AKSearchFixture, 
Values(
	AKSearchTestStruct{L"HELLO", strVec({L"HELL", L"ELLO", L"EL"}), resVec({{1,1},{2,2},{2,3}})},
	AKSearchTestStruct{L"TEST",  strVec({L"TEST"}), 				resVec({{1,1}})},
	AKSearchTestStruct{L"TEST", 	strVec({L"ST", L"TE"}), 			resVec({{1,2},{3,1}})}
));

INSTANTIATE_TEST_CASE_P(AKSearch_Complex_TestCase, AKSearchFixture, 
Values(
	AKSearchTestStruct{L"ACCACCACCA", strVec({L"ACCA", L"ACC", L"AC", L"CAA"}),
	resVec({{1,1},{1,2},{1,3},{4,1},{4,2},{4,3},{7,1},{7,2},{7,3}})},
	AKSearchTestStruct{L"ACANCNACTNGNANANNCGANCNNANNGACA", strVec({L"G", L"NN", L"ACA", L"TN", L"ANC"}),
	resVec({{1,3},{3,5},{9,4},{11,1},{16,2},{19,1},{20,5},{23,2},{26,2},{28,1},{29,3}})},
	AKSearchTestStruct{L"SЫRФЫ", strVec({L"Ф", L"Ы"}),
	resVec({{2,2},{4,1},{5,2}})}
));

TEST_P(AKSearchFixture, AKSearchTestStruct) {
    ASSERT_EQ(GetParam().expRes, res);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}