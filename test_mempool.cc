#include <gtest/gtest.h>

#include "mempool.cc"

class MemPoolTest : public ::testing::Test {
protected:
    struct alignas(16) MyStruct {};
    static constexpr unsigned int kSlots = 8;
    MemPool<MyStruct>* pool;

    void SetUp() override {
        pool = new MemPool<MyStruct>(sizeof(MyStruct) * kSlots);
    }

    void TearDown() override {
        delete pool;
    }
};

TEST_F(MemPoolTest, VerifiesStructSizeAndPoolInitialization) {
    EXPECT_EQ(sizeof(MyStruct), 16);
    EXPECT_EQ(pool->get_size(), sizeof(MyStruct) * kSlots);
}

TEST_F(MemPoolTest, ThrowsWhenAllocatingBeyondCapacity) {
    // Fill the pool
    for (unsigned int i = 0; i < kSlots; i++) {
        EXPECT_NO_THROW(pool->alloc_new());
    }

    // Attempt to allocate one more
    EXPECT_THROW(pool->alloc_new(), std::bad_alloc);
}

TEST_F(MemPoolTest, SuccessfullyFreesObject) {
    auto index = pool->alloc_new();
    EXPECT_NO_THROW(pool->free_obj(index));
    EXPECT_TRUE(pool->is_slot_free(index));
}

TEST_F(MemPoolTest, ReallocatesToSameLocationAfterFree) {
    // First allocation
    auto index1 = pool->alloc_new();
    EXPECT_EQ(index1, 0);
    auto* location1 = &(pool->get_obj(index1));
    
    // Free and reallocate
    pool->free_obj(index1);
    auto index2 = pool->alloc_new();
    auto* location2 = &(pool->get_obj(index2));
    
    // Verify same index and memory location
    EXPECT_EQ(index2, 0);
    EXPECT_EQ(location1, location2);
}