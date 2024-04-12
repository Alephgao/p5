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

// Test copy constructor
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

TEST(CustomCompareTest) {
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

TEST(BasicOperationsTest) {
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

TEST(InsertionIntegrityAndInvariantCheckTest) {
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


TEST(ComplexOperationsAndEdgeCases) {
    BinarySearchTree<std::string> GalaxyTree;
    GalaxyTree.insert("Andromeda");
    GalaxyTree.insert("Milky Way");
    GalaxyTree.insert("Whirlpool");
    GalaxyTree.insert("Black Eye");
    GalaxyTree.insert("Sunflower");

    ASSERT_TRUE(GalaxyTree.find("Andromeda") != GalaxyTree.end());
    ASSERT_EQUAL(GalaxyTree.size(), 5); // Ensure duplicate wasn't added

    // Testing traversals and iterator validity after operations
    std::stringstream in_order;
    GalaxyTree.traverse_inorder(in_order);
    ASSERT_EQUAL(in_order.str(), "Andromeda Black Eye Milky Way Sunflower Whirlpool ");
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

    ASSERT_EQUAL(pre_order.str(), "Alice Cheshire Cat Queen of Hearts Mad Hatter ");
    ASSERT_EQUAL(in_order.str(), "Alice Cheshire Cat Mad Hatter Queen of Hearts ");

    // Iterator increment test
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


TEST_MAIN()
