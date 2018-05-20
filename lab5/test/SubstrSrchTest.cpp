#include <gtest/gtest.h>
#include "../hdr/KMPfunc.hpp"

using ::testing::TestWithParam;
using ::testing::Values;

struct SubstrTest
{
    string text;
	string pattern;
	vector <size_t> expectedAnsw;
};

class StandartFixtureKMP : public TestWithParam<SubstrTest>
{
public:
	virtual void SetUp() 
	{
		operationsKMP = 0;
	    KMPansw = KMP(GetParam().pattern, GetParam().text, operationsKMP);
	}
    virtual void TearDown() { }

protected:
	int operationsKMP;
    vector <size_t> KMPansw;
};

INSTANTIATE_TEST_CASE_P(StandartInstantiate, StandartFixtureKMP,
Values(
	SubstrTest{"CCCA", "CC", {0,1} },
	SubstrTest{"HELLOWORLDHEREISNOWORLD", "WORLD", {5,18}},
	SubstrTest{"IAMTHEONLYONE", "IAMTHEONLYONE", {0}},
	SubstrTest{"KMPISHERE", "TUTETOGONET", {}}
));

TEST_P(StandartFixtureKMP, SubstrTest) {
    ASSERT_EQ(GetParam().expectedAnsw, KMPansw);
}

class StandartFixtureNaive : public TestWithParam<SubstrTest>
{
public:
	virtual void SetUp()
	{
		operationsNaive = 0;
		naiveAnsw = naive(GetParam().pattern, GetParam().text, operationsNaive);
	}
	virtual void TearDown() { }

protected:
	int operationsNaive;
	vector <size_t> naiveAnsw;
};

INSTANTIATE_TEST_CASE_P(StandartInstantiate, StandartFixtureNaive,
	Values(
		SubstrTest{ "CCCA", "CC",{ 0,1 } },
		SubstrTest{ "HELLOWORLDHEREISNOWORLD", "WORLD",{ 5,18 } },
		SubstrTest{ "IAMTHEONLYONE", "IAMTHEONLYONE",{ 0 } },
		SubstrTest{ "KMPISHERE", "TUTETOGONET",{} }
));

TEST_P(StandartFixtureNaive, SubstrTest) {
	ASSERT_EQ(GetParam().expectedAnsw, naiveAnsw);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}