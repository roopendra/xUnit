#include <gtest/gtest.h>
#include "data_group.hpp"

class ValueSequenceTest: public testing::Test {
};

bool isFit(int size)
{
    return size > 0 && size < 60;
}

#include <iostream>
using namespace std;

TEST_F(ValueSequenceTest, get_value_by_return_object) {
    //cout << "Expect result: ";
    DATA_GROUP GRP;

    while(GRP.getting()) {
	const char* name = GRP[name] ("kitty", "michel", "anney");
	int size = GRP[size] (42, 0, 37, -1, 45, 48);
	//int size2 = GRP[size2] (45, 98);
	bool exp_fit = GRP[exp_fit] (true, false, true, false, true);

	cout << "Data[" << GRP.current() << "]  size:" << size << " exp_fit:" << exp_fit << " name:" << name << endl;

	EXPECT_EQ(exp_fit, isFit(size))
	    //<< "*** Error at data group [" << DATA_IDX(GRP) << "] ***";
	    << "*** Error at data group [" << GRP.current() << "] ***";
    }
}

