#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"


TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST(RenaissanceSearch) {
    BinarySearchTree<int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);

    ASSERT_TRUE(tree.find(3) != tree.end());
    ASSERT_TRUE(tree.find(8) != tree.end());
    ASSERT_TRUE(tree.find(10) != tree.end());
    ASSERT_TRUE(tree.find(99) == tree.end());
}


// Test empty tree properties
TEST(DeepMindEmpty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0);
}

// Test tree height calculation
TEST(OpenAIHeights) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);  // This should make a straight line (unbalanced tree)

    ASSERT_EQUAL(tree.height(), 3);
}

// Test copy constructor
TEST(GoogleDeepCopy) {
    BinarySearchTree<int> original;
    original.insert(4);
    original.insert(2);
    original.insert(6);

    BinarySearchTree<int> copy = original;
    ASSERT_TRUE(copy.find(4) != copy.end());
    ASSERT_TRUE(copy.find(2) != copy.end());
    ASSERT_TRUE(copy.find(6) != copy.end());
    ASSERT_EQUAL(copy.size(), 3);
}

// Test tree balance invariant (custom check for this example)
TEST(NvidiaBalancingAct) {
    BinarySearchTree<int> tree;
    // Insert elements in a way that requires balancing if AVL was implemented
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    tree.insert(2);
    // This is a simple check assuming no self-balancing is done
    ASSERT_TRUE(tree.check_sorting_invariant());
    // The height would not be minimal for AVL or Red-Black trees
}


TEST_MAIN()
