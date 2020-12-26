#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

using namespace std;

/**
 * 
 * AVL tree is a self-balancing Binary Search Tree 
 * where the difference between heights of left and right subtrees 
 * cannot be more than one for all nodes.
 * 
 * Tree rotation is an operation that changes the structure without interfering with 
 * the order of the elements on an AVL tree. It moves one node up in the tree and one node down. 
 * It is used to change the shape of the tree, 
 * and to decrease its height by moving smaller subtrees down and larger subtrees up, 
 * resulting in improved performance of many tree operations. 
 * The direction of a rotation depends on the side which the tree nodes 
 * are shifted upon whilst others say that it depends on which child takes the root’s place. 
 * This is a C++ Program to Implement AVL Tree.
 * 
 */


template<typename Comparable>
class AvlTree {
private:
  struct AvlNode {
    Comparable element;
    AvlNode* left;
    AvlNode* right;
    int height;

    AvlNode( const Comparable& ele, AvlNode* lt, AvlNode* rt, int h=0 )
      :element{ele}, left{lt}, right{rt}, height{h} {}

    AvlNode( const Comparable&& ele, AvlNode* lt, AvlNode* rt, int h=0 )
      :element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
  };

  /**
   * 返回节点高度，如果是nullptr则返回-1  
   */
  int height( AvlNode* t ) const {
    return t == nullptr ? -1 : t->height;
  }

  void insert( const Comparable& x, AvlNode* & t ) {
    if( t == nullptr )
      t = new AvlNode{ x, nullptr, nullptr };
    else if(t->element < x)
      insert(x, t->right);
    else
      insert(x, t->left);
    
    balance( t );
  }

  static const int ALLOWED_IMBALANCE = 1;

  // 假设t是平衡的，或与平衡相差不超过1
  void balance( AvlNode* & t ) {
    if(t == nullptr)
      return ;
    if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
      if( height(t->left->left) >= height(t->left->right) )
        rotateWithLeftChild( t );
      else 
        doubleWithLeftChild( t );
    } else if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
      if(heigt(t->right->right) >= height(t->right->left))
        rotateWithRightChild( t );
      else
        doubleWithRightChild( t );
    }
  
    t->height = max(height(t->left), height(t->right)) + 1;
  }

  /**
   * 把左边的树变成右边的树，RR
   * 用左儿子旋转二叉树的节点，
   * 这是对AVL树在情形1的一次单旋转。
   * 更新高度，然后设置新根。 
   */
  void rotateWithLeftChild( AvlNode* & k2 ) {
    AvlNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
  }

  /**
   * 双旋转二叉树的节点，首先左儿子和它的右儿子进行，
   * 然后节点k3和新的左儿子进行，
   * 这是对AVL树情形2的一次双旋转
   * 更新高度然后设置新根
   */
  void doubleWithLeftChild( AvlNode* & k3 ) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
  }

  void rotateWithRightChild( AvlNode* & k2 ) {
    AvlNode* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;
    k2 = k1;
  }

  void doubleWithRightChild( AvlNode* & k3 ) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
  }

  /**
   * 从子树实施删除的内部方法，
   * x 是要被删除的项，
   * t 为孩子树的根节点，
   * 设置孩子树的新根。
   */
  void remove( const Comparable& x, AvlNode* & t ) {
    if( t == nullptr) 
      return ;          // 没发现要删除的项，什么也不做

    if( x < t->element )
      remove( x, t->left );
    else if( x > t->element)
      remove( x, t->right );
    else if( t->left != nullptr && t->right != nullptr ) {
      t->element = findMin( t->right )->element;
      remove( t->element, t->right );
    } else {
      AvlNode* oldNode = t;
      t = (t->left != nullptr) ? t->left : t->right;
      delete oldNode;
    }

    balance( t );
  }

  AvlNode* findMin( AvlNode* t ) {
    if( t != nullptr ) {
      while ( t->left != nullptr ) 
        t = t->left;
    }
    return t;
  }
};

#endif