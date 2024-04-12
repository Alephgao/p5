#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <functional>  // For std::greater


TEST(test_stub) {
    ASSERT_TRUE(true);
}

TEST(SearchTest) {
    BinarySearchTree<int> Renaissance;
    Renaissance.insert(42);
    Renaissance.insert(17);
    Renaissance.insert(68);

    ASSERT_TRUE(Renaissance.find(17) != Renaissance.end());
    ASSERT_TRUE(Renaissance.find(42) != Renaissance.end());
    ASSERT_TRUE(Renaissance.find(68) != Renaissance.end());
    ASSERT_TRUE(Renaissance.find(99) == Renaissance.end());
}


TEST(EmptyTest) {
    BinarySearchTree<int> DeepMind;
    ASSERT_TRUE(DeepMind.empty());
    ASSERT_EQUAL(DeepMind.size(), 0);
}

TEST(InsertTest) {
    BinarySearchTree<int> DeepMind;
    DeepMind.insert(21);
    DeepMind.insert(34);
    DeepMind.insert(55);
    DeepMind.insert(89);
    DeepMind.insert(144);

    ASSERT_EQUAL(DeepMind.size(), 5);
    ASSERT_TRUE(DeepMind.find(21) != DeepMind.end());
    ASSERT_TRUE(DeepMind.find(34) != DeepMind.end());
    ASSERT_TRUE(DeepMind.find(55) != DeepMind.end());
    ASSERT_TRUE(DeepMind.find(89) != DeepMind.end());
    ASSERT_TRUE(DeepMind.find(144) != DeepMind.end());
}

TEST(HeightTest) {
    BinarySearchTree<int> OpenAI;
    OpenAI.insert(10);
    OpenAI.insert(20);
    OpenAI.insert(30); 

    ASSERT_EQUAL(OpenAI.height(), 3);
}

TEST(CopyConstructorTest) {
    BinarySearchTree<int> Google;
    Google.insert(13);
    Google.insert(8);
    Google.insert(21);

    BinarySearchTree<int> GoogleCopy = Google;
    ASSERT_TRUE(GoogleCopy.find(13) != GoogleCopy.end());
    ASSERT_TRUE(GoogleCopy.find(8) != GoogleCopy.end());
    ASSERT_TRUE(GoogleCopy.find(21) != GoogleCopy.end());
    ASSERT_EQUAL(GoogleCopy.size(), 3);
}

TEST(BalancingTest) {
    BinarySearchTree<int> Nvidia;
    Nvidia.insert(50);
    Nvidia.insert(30);
    Nvidia.insert(70);
    Nvidia.insert(40);

    ASSERT_TRUE(Nvidia.check_sorting_invariant());

}




struct ReverseCompare {
  bool operator()(const int& lhs, const int& rhs) const {
    return lhs > rhs;
  }
};

TEST(CustomCompare) {
  BinarySearchTree<int, ReverseCompare> reverse_bst;
  reverse_bst.insert(50);
  reverse_bst.insert(30);
  reverse_bst.insert(70);
  reverse_bst.insert(10);
  reverse_bst.insert(90);

  ASSERT_EQUAL(reverse_bst.size(), 5);  

  std::stringstream in_order;
  reverse_bst.traverse_inorder(in_order);
  ASSERT_EQUAL(in_order.str(), "90 70 50 30 10 ");

  ASSERT_EQUAL(reverse_bst.height(), 3);  

  auto min_it = reverse_bst.min_element();
  auto max_it = reverse_bst.max_element();
  ASSERT_EQUAL(*min_it, 90); 
  ASSERT_EQUAL(*max_it, 10); 
}

TEST(BasicOperations) {
    BinarySearchTree<int> EssentialsTree;
    EssentialsTree.insert(20);
    EssentialsTree.insert(10);
    EssentialsTree.insert(40);
    EssentialsTree.insert(5);
    EssentialsTree.insert(15);
    EssentialsTree.insert(35);
    EssentialsTree.insert(45);

    ASSERT_EQUAL(*EssentialsTree.min_element(), 5);
    ASSERT_EQUAL(*EssentialsTree.max_element(), 45);
    ASSERT_EQUAL(EssentialsTree.size(), 7);
}

TEST(Insertion) {
    BinarySearchTree<int> IntegrityTree;
    IntegrityTree.insert(20);
    IntegrityTree.insert(30);
    IntegrityTree.insert(10);
    IntegrityTree.insert(25);
    IntegrityTree.insert(5);

    ASSERT_EQUAL(IntegrityTree.size(), 5);
    ASSERT_TRUE(IntegrityTree.check_sorting_invariant());
    ASSERT_EQUAL(*IntegrityTree.min_element(), 5);
    ASSERT_EQUAL(*IntegrityTree.max_element(), 30);
}


TEST(IteratorIncrementTest) {
    BinarySearchTree<int> tree;
    tree.insert(40);
    tree.insert(20);
    tree.insert(60);
    tree.insert(10);
    tree.insert(30);
    tree.insert(50);
    tree.insert(70);

    auto it = tree.begin();
    ASSERT_EQUAL(*it, 10);
    ++it;
    ASSERT_EQUAL(*it, 20);
    ++it;
    ASSERT_EQUAL(*it, 30);
}


TEST(TraversalAndIteratorTests) {
    BinarySearchTree<std::string> FableTree;
    FableTree.insert("Alice");
    FableTree.insert("Cheshire Cat");
    FableTree.insert("Queen of Hearts");
    FableTree.insert("Mad Hatter");

    std::stringstream pre_order, in_order;
    FableTree.traverse_preorder(pre_order);
    FableTree.traverse_inorder(in_order);

    ASSERT_TRUE(FableTree.find("Alice") == FableTree.begin());

    ASSERT_EQUAL(pre_order.str(), "Alice Cheshire Cat Queen of Hearts Mad Hatter ");
    ASSERT_EQUAL(in_order.str(), "Alice Cheshire Cat Mad Hatter Queen of Hearts ");

    auto it = FableTree.begin();
    ASSERT_EQUAL(*it, "Alice");
    ++it;
    ASSERT_EQUAL(*it, "Cheshire Cat");
}

TEST(CustomCompareAndToString) {
    struct ReverseCompare {
        bool operator()(const std::string& lhs, const std::string& rhs) const {
            return lhs > rhs;
        }
    };

    BinarySearchTree<std::string, ReverseCompare> UtopiaTree;
    UtopiaTree.insert("Mercury");
    UtopiaTree.insert("Venus");
    UtopiaTree.insert("Earth");
    UtopiaTree.insert("Mars");
    UtopiaTree.insert("Jupiter");

    ASSERT_EQUAL(UtopiaTree.size(), 5);
    ASSERT_EQUAL(*UtopiaTree.min_element(), "Venus");
    ASSERT_EQUAL(*UtopiaTree.max_element(), "Earth");
}

TEST(IteratorTESTS) {
    BinarySearchTree<int> Turing;
    Turing.insert(1950);
    Turing.insert(1912);
    Turing.insert(1936);
    Turing.insert(1927);
    Turing.insert(1956);
    Turing.insert(1983);
    Turing.insert(1997);

    auto Lovelace = Turing.begin();
    ASSERT_EQUAL(*Lovelace, 1912);
    ++Lovelace;
    ASSERT_EQUAL(*Lovelace, 1927);
    Lovelace++;
    ASSERT_EQUAL(*Lovelace, 1936);
    Lovelace = Turing.end();


    auto Minerva = Turing.min_element();
    ASSERT_EQUAL(*Minerva, 1912);
    auto Minsky = Turing.max_element();
    ASSERT_EQUAL(*Minsky, 1997);

    auto Shannon = Turing.find(1936);
    ASSERT_EQUAL(*Shannon, 1936);
    auto Hopper = Turing.find(2042);
    ASSERT_TRUE(Hopper == Turing.end());

    auto Neumann = Turing.min_greater_than(1936);
    ASSERT_EQUAL(*Neumann, 1950);

    ASSERT_FALSE(Turing.empty());
    ASSERT_EQUAL(Turing.size(), 7);
}
TEST(empty_sorting_invariance) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.check_sorting_invariant());
}

TEST(single_element_handling) {
    BinarySearchTree<int> bst;
    bst.insert(42);
    ASSERT_TRUE(bst.check_sorting_invariant());
    ASSERT_EQUAL(bst.size(), 1);
    ASSERT_EQUAL(*bst.begin(), 42);
    ASSERT_EQUAL(*bst.min_element(), 42);
    ASSERT_EQUAL(*bst.max_element(), 42);
    ASSERT_TRUE(bst.find(42) != bst.end());
    ASSERT_TRUE(bst.find(43) == bst.end());
}


TEST(assign_empty_to_non_empty_tree) {
    BinarySearchTree<int> bst1;
    bst1.insert(1);
    BinarySearchTree<int> bst2;
    bst2 = bst1; 
    bst1 = BinarySearchTree<int>(); 
    ASSERT_TRUE(bst1.empty());
    ASSERT_EQUAL(bst2.size(), 1);
    ASSERT_TRUE(bst2.find(1) != bst2.end());
}

TEST(combined_bst_tests) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    ASSERT_EQUAL(tree.height(), 3);
    ASSERT_TRUE(tree.check_sorting_invariant());

    BinarySearchTree<int> emptyTree;
    BinarySearchTree<int> tree2(emptyTree);
    ASSERT_TRUE(tree2.empty());

    BinarySearchTree<int> copiedTree = tree;
    ASSERT_EQUAL(copiedTree.height(), tree.height());
    BinarySearchTree<int> assignedTree;
    assignedTree = tree;
    ASSERT_EQUAL(assignedTree.height(), tree.height());

    *tree.insert(40) = 5;
    ASSERT_FALSE(tree.check_sorting_invariant()); 

    std::ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() != "10 20 30 40 "); 

    // Uncomment the following line when submit to auto!
    //tree = tree;
    ASSERT_FALSE(tree.height() == 3);

    tree = emptyTree;
    ASSERT_TRUE(tree.empty());

    BinarySearchTree<int> complexTree;
    complexTree.insert(5);
    complexTree.insert(3);
    complexTree.insert(7);
    complexTree.insert(6);
    complexTree.insert(4);
    complexTree.insert(1);
    complexTree.insert(2);
    complexTree.insert(8);
    complexTree.insert(10);
    std::ostringstream oss_complex_inorder;
    complexTree.traverse_inorder(oss_complex_inorder);
    ASSERT_EQUAL(oss_complex_inorder.str(), "1 2 3 4 5 6 7 8 10 ");
    ASSERT_TRUE(complexTree.size() == 9);
    ASSERT_TRUE(complexTree.height() == 4);
    ASSERT_TRUE(complexTree.check_sorting_invariant());
}


TEST_MAIN()


