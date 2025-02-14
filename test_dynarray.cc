#include <gtest/gtest.h>
#include "dynarray.cc"  // Include implementation directly for templates

class DynArrTest : public ::testing::Test {
protected:
    DynArrTest() : arr(0) {}  // Initialize with dummy size
    
    void SetUp() override {
        arr = DynArr<int>(5);  // Proper initialization
        for(int i = 0; i < 5; i++) {
            arr[i] = i + 1;
        }
    }

    DynArr<int> arr;
};

TEST_F(DynArrTest, ConstructorTest) {
    DynArr<int> a(3);
    EXPECT_EQ(a[0], int()); // Verify default initialization
    EXPECT_EQ(a.getSize(), 3);
}

TEST_F(DynArrTest, MoveConstructorTest) {
    DynArr<int> moved(std::move(arr));
    
    EXPECT_EQ(moved.getSize(), 5);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[4], 5);
    
    // Original should be in valid empty state
    EXPECT_EQ(arr.getSize(), 0);
    // Can't test ptr directly, but access should throw
    EXPECT_THROW(arr[0], std::out_of_range);
}

TEST_F(DynArrTest, MoveAssignmentTest) {
    DynArr<int> moved = std::move(arr);
    
    EXPECT_EQ(moved.getSize(), 5);
    EXPECT_EQ(moved[2], 3);
    
    // Original should be empty
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_THROW(arr[0], std::out_of_range);
}

TEST_F(DynArrTest, ResizeTest) {
    // Test enlarging
    arr.resize(7);
    EXPECT_EQ(arr.getSize(), 7);
    EXPECT_EQ(arr[4], 5);  // Existing elements preserved
    EXPECT_EQ(arr[6], 0);  // New elements default initialized
    
    // Test shrinking
    arr.resize(3);
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[2], 3);
    
    // Test resize to 0
    EXPECT_NO_THROW(arr.resize(0));
    EXPECT_EQ(arr.getSize(), 0);
}

TEST_F(DynArrTest, AccessOperatorTest) {
    // Non-const version
    arr[2] = 10;
    EXPECT_EQ(arr[2], 10);
    
    // Const version
    const DynArr<int>& const_arr = arr;
    EXPECT_EQ(const_arr[3], 4);
    
    // Out of bounds access
    EXPECT_THROW(arr[5], std::out_of_range);
    EXPECT_THROW(arr[-1], std::out_of_range);
}

TEST_F(DynArrTest, ExceptionTest) {
    // Invalid resize
    EXPECT_THROW(arr.resize(-1), std::bad_array_new_length);
    
    // Invalid access
    EXPECT_THROW(arr[100], std::out_of_range);
    EXPECT_THROW(arr[-5], std::out_of_range);
}