#include <gtest/gtest.h>

#include "mempool.cc"

TEST(AllocTest, CanAllocFull) {
    struct MyStruct {

    };

    unsigned int slots = 8;
    MemPool<MyStruct> pool(sizeof(MyStruct) * slots);
    EXPECT_EQ(pool.get_size(), sizeof(MyStruct) * slots);
}

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
