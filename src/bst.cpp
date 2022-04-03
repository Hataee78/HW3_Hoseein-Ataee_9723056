#include "bst.h"
#include<iostream>
#include<optional>
#include <algorithm>
#include <vector>
#include <queue>
#include <list>

//   BST::~BST()
//  {
//  	std::vector<Node*> nodes;
//  	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
//  	for(auto& node: nodes)
//  		delete node;
//  }
//  -----------------------------------------------------------
BST::Node::Node(int value, Node* left, Node* right):value(value),left(left),right(right){};
// -----------------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const BST::Node &node) {
    os << "value: " << node.value << " left: " << node.left << " right: " << node.right;
    return os;
}
// -----------------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const BST &bst) {
    os << "root: " << bst.root;
    return os;
}
// -----------------------------------------------------------------------------------------
BST::Node *&BST::get_root() {
    return root;
}
// -----------------------------------------------------------------------------------------
bool operator<(const BST::Node &rhs,int value)  {
    if (value > rhs.value)
        return true;
    return false ;      
}

bool operator>(const BST::Node &rhs,int value)  {
    return rhs.value > value;
}

bool operator<=(const BST::Node &rhs,int value)  {
    return !(rhs.value > value);
}

bool operator>=(const BST::Node &rhs, int value)  {
    return !(value > rhs.value);
}
bool operator==(const BST::Node &rhs, int value)  {
    return (value == rhs.value);
}
//------------------------------------------------------------
bool operator<(int value, const BST::Node &rhs)  {
    if (value < rhs.value)
        return true;
    return false ;      
}

bool operator>(int value, const BST::Node &rhs)  {
    return rhs.value < value;
}

bool operator<=(int value, const BST::Node &rhs)  {
    return !(rhs.value < value);
}

bool operator>=(int value, const BST::Node &rhs)  {
    return !(value < rhs.value);
}
bool operator==(int value, const BST::Node &rhs)  {
    return (value == rhs.value);
}

// ------------------------------------------------------------------
bool BST::insert(Node *node, int value)
{
    
    if (value > node->value)
    {
        // Higher value than node
        if ((node->right)==nullptr){
            // Insert on the right of the node
            node->right = new Node(value,nullptr,nullptr);
            counter++;
            return true;
            
        }    
        else
            // Go deeper
            return insert(node->right, value);
    }
    else if (value < node->value)
    {
        // Lower value than node

        if (node->left==nullptr)
        {
            // Insert on the left of the node
            node->left = new Node(value,nullptr,nullptr);
            counter++;
            return true;
            
        }     
        else
            // Go deeper
            return insert(node->left, value);
           
    }
    else 
        return false;        
}

// // --------------------------------------------------------------------------------------
  bool BST::add_node(int value) {
      if (this->root==nullptr){
          this->root = new Node(value,nullptr,nullptr);
          counter++;
          return true;
          

      }
      return insert(root,value);
      

     }

//---------------------------------------------------------------------------------------
   size_t BST::length() {
       return counter;
    
}  
//----------------------------------------------------------------------------------------
void BST::bfs(std::function<void(Node * &)> func) {
std::queue<Node*> q;

    q.push (root);

    while (not q.empty ()) { 
      auto&& current = q.front ();
      q.pop ();

      func (current);
        std::list<Node*> my_list = { current->right,current->left };
        // Node* adjacent = my_list;

      for (auto&& a: my_list) {
      if (a!=nullptr)    
          q.push (a);
      }

    }
}
//--------------------------------------------------------------------------------------------
BST::Node **BST::find_node(int value) {
    Node **current = &root;
    while ((*current)!=nullptr)
    {   
        if ((*current)->value == value)
            break;
        
        if (value > (*current)->value)
            current = &((*current)->right);
        else
            current = &((*current)->left);

    }
    if ((*current)==nullptr)
        return nullptr;
    else {   
        return current;
    }
}


// -----------------------------------------------------------------------------------------------------------------------
BST::Node **BST::find_parrent(int value) {
   Node **current = &root;
    while ((*current)!=nullptr)
    {   
        if ((((*current)->right)->value)==value || (((*current)->left)->value) == value)
            return current; 
        
        if (value > (((*current)->right)->value))
            current = &((*current)->right);
        else
            current = &((*current)->left);

    }
    if ((*current)==nullptr)
        return nullptr;
    else {   
        return current;
    }

}
// -----------------------------------------------------------------------------------------------------------
BST::Node **BST::find_successor(int value) { 
    Node **current = &root; 
    Node  **s; 
    while((*current)!=nullptr) 
    { 
        // if the value is greater than root, go to the right sub-tree 
        if((*current)->value<value) 
        { 
            current=&((*current)->right); 
        } 
        // if the value is smaller than root, go to the left sub-tree 
        else if(value<(*current)->value) 
        { 
            current=&((*current)->left); 
        } 
        // if the value is found in a node, the leftmost node of the right sub-tree 
        // is the  successor of the value 
        else if((*current)->value==value) 
        { 
            // finds the rightmost node of the left sub-tree 
            if((*current)->left!=nullptr) 
            { 
                current=&((*current)->left); 
                while((*current)->right!=nullptr) 
                    current=&((*current)->right); 
            } 
            // if there exist no left sub-tree, then successor 
            // will be the node, from where last right turn is taken 
            else  
            {  
                // traversing starts from root to that node  
                Node* tmp_root = root; 
                while(tmp_root->value!=value)  
                {  
                    // if value is bigger than root, goes to right sub-tree  
                    // s stores the node, from where right  turn is taken  
                    if(value>tmp_root->value)  
                    {  
                        s = find_node(tmp_root->value);  
                        tmp_root=tmp_root->right;  
                    }  
                    // else, to the left sub-tree  
                    else  
                       tmp_root=tmp_root->left;  
                }  
                current=s;  
            }  
            return current;  
        } 
    } 
}
    

// --------------------------------------------------------------------------------------------------------------------------
BST::Node* BST::minValueNode(BST::Node* node)
{
     Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != nullptr)
        current = current->left;
 
    return current;
}
 
// --------------------------------------------------------------------------------------------------------------------------
BST::Node* BST::deleteNode(BST::Node* root, int value)
{
    // base case
    if (root == nullptr){
        return root;
        isDeleted=0;
    }
    // If the value to be deleted is
    // smaller than the root's
    // value, then it lies in left subtree
    if (value < root->value){
        root->left = deleteNode(root->left, value);
        isDeleted=1;
    }
    // If the value to be deleted is
    // greater than the root's
    // value, then it lies in right subtree
    else if (value > root->value){
        root->right = deleteNode(root->right, value);
        isDeleted=1;
    }
 
    // if value is same as root's value, then This is the node
    // to be deleted
    else {
        // node has no child
        if (root->left==nullptr and root->right==nullptr){
            isDeleted=0;
            return nullptr;
            
        }
        // node with only one child or no child
        else if (root->left == nullptr) {
            BST:: Node* temp = root->right;
            free(root);
            isDeleted=1;
            return temp;
            
        }
        else if (root->right == nullptr) {
             BST::Node* temp = root->left;
            free(root);
            isDeleted=1;
            return temp;
            
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        BST:: Node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->value = temp->value;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->value);
    }
    isDeleted=1;
    return root;
    
}
// --------------------------------------------------------------------------------------------------------------------------
bool BST::delete_node(int value) {
    deleteNode( root,  value);
    if ( isDeleted==1){
        counter--;
        return true;
        
    }
    if ( isDeleted==0){
        return false;
        
    }
    
    
} 
// ----------------------------------------------------------------------------------------------
BST::BST (std::initializer_list<int> list):root(nullptr){ 
    
    for (auto i = list.begin(); i != list.end(); i++) { 
                add_node(*i); 
            } 
        }
// ------------------------------------------------------------------------------------------------
 
BST& BST::operator++(){ 
    return *this; 
} 
BST BST::operator ++(int){ 
    return *this; 
}
