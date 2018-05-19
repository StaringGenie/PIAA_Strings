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

struct ShiftTest
{
    string first;
	string second;
	int expectedAnswer;
};

class ShiftFixture : public TestWithParam<ShiftTest>
{
public:
	virtual void SetUp()
	{
		operations = 0;
		string tmp1 = GetParam().first;
		string tmp2 = GetParam().second;
		if (tmp1.size() == tmp2.size())
		{
			vector <size_t> res = KMP(GetParam().second, tmp1 + tmp1, operations);
			if (res.size())
				position = res[0];
			else
				position = -1;
		}
		else
			position = -1;
	}
	virtual void TearDown() { }

protected:
	int operations;
	int position;
};

INSTANTIATE_TEST_CASE_P(ShiftInstantiate, ShiftFixture, 
Values(
	ShiftTest{"HELLO", "HELLO", 0},
	ShiftTest{"RLD!WO", "WORLD!", 4},
	ShiftTest{"LOVEUI", "ILOVEU", 5},
	ShiftTest{"I", "IWILLTESTU", -1},
	ShiftTest{ "STOPIT", "HERENO", -1},
	ShiftTest{ "AADA", "DAAA", 2},
	ShiftTest{ "ASDAVDAGD", " ", -1},
	ShiftTest{"~FTSHIII", "SHIII~FT", 3}
));

TEST_P(ShiftFixture, ShiftTest) {
    ASSERT_EQ(GetParam().expectedAnswer, position);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}