#include <gtest/gtest.h>
#include "../hdr/KMPfunc.hpp"

using ::testing::TestWithParam;
using ::testing::Values;

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