#include <gtest/gtest.h>
#include "unionfind.cc"

class UnionFindTest : public ::testing::Test {
protected:
    void SetUp() override {
        uf = SimpleUnionFind();
    }
    SimpleUnionFind uf;
};

TEST_F(UnionFindTest, SingleElementSet) {
    uf.union_op("a", "a");
    EXPECT_EQ(uf.find_op("a"), uf.find_op("a"));
    EXPECT_EQ(uf.size_op("a"), 1);
}

TEST_F(UnionFindTest, TwoElementUnion) {
    uf.union_op("a", "b");
    EXPECT_EQ(uf.find_op("a"), uf.find_op("b"));
}

TEST_F(UnionFindTest, MultipleUnions) {
    uf.union_op("a", "b");
    uf.union_op("c", "d");
    uf.union_op("b", "c");
    
    EXPECT_EQ(uf.find_op("a"), uf.find_op("d"));
    EXPECT_EQ(uf.find_op("a"), uf.find_op("b"));
    EXPECT_EQ(uf.find_op("b"), uf.find_op("c"));
    EXPECT_EQ(uf.find_op("c"), uf.find_op("d"));
}

TEST_F(UnionFindTest, NonExistentElement) {
    EXPECT_THROW(uf.find_op("x"), std::exception);
    EXPECT_THROW(uf.size_op("x"), std::exception);
}

TEST_F(UnionFindTest, UnionSameSet) {
    uf.union_op("a", "b");
    uf.union_op("b", "c");
    
    // Union elements already in the same set
    uf.union_op("a", "c");
    
    EXPECT_EQ(uf.find_op("a"), uf.find_op("c"));
}

TEST_F(UnionFindTest, LargeSet) {
    // Create a chain of unions: a->b->c->d->e
    uf.union_op("a", "b");
    uf.union_op("b", "c");
    uf.union_op("c", "d");
    uf.union_op("d", "e");
    
    EXPECT_EQ(uf.find_op("a"), uf.find_op("e"));
    EXPECT_EQ(uf.find_op("b"), uf.find_op("d"));
    EXPECT_EQ(uf.find_op("c"), uf.find_op("e"));
}

TEST_F(UnionFindTest, DisjointSets) {
    uf.union_op("a", "b");
    uf.union_op("c", "d");
    
    EXPECT_NE(uf.find_op("a"), uf.find_op("c"));
    EXPECT_EQ(uf.find_op("a"), uf.find_op("b"));
    EXPECT_EQ(uf.find_op("c"), uf.find_op("d"));
}
