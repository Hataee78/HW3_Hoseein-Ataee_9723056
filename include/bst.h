
#ifndef BST_H
#define BST_H
#include<functional>
#include <ostream>
#include<optional>
#include <algorithm>
#include <vector>
#include <queue>
#include <list>
class BST
{
public:
 class Node
    {
    public:
        Node(int value, Node* left, Node* right);
        Node()=default;
        Node(const Node& node)=default;

        int value;
        Node* left;
        Node* right;
    };
    //  ~BST();
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    bool insert(Node *node, int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    Node* minValueNode(BST::Node* node);
    Node* deleteNode(BST::Node* root, int value);
    bool delete_node(int value);
    friend std::ostream &operator<<(std::ostream &os, const BST::Node &node);
    friend::std::ostream &operator<<(std::ostream &os, const BST &bst);
    friend bool operator<(const BST::Node &rhs,int value);
    friend bool operator>(const BST::Node &rhs, int value);
    friend bool operator<=(const BST::Node &rhs, int value);
    friend bool operator>=(const BST::Node &rhs, int value);
    friend bool operator==(const BST::Node &rhs, int value);
    // BST& operator++(const BST &bst);
    // // BST operator ++(BST& bst, int);
    BST& operator++(); 
    BST operator ++(int);
    BST (std::initializer_list<int> list);
     

    //----------------------------------------------------------
    friend bool operator<(int value, const BST::Node &rhs);
    friend bool operator>(int value, const BST::Node &rhs);
    friend bool operator<=(int value, const BST::Node &rhs);
    friend bool operator>=(int value, const BST::Node &rhs);
    friend bool operator==(int value, const BST::Node &rhs);


   
private:
    Node* root;
    size_t counter{};
    bool isDeleted;
};

#endif //BST_H