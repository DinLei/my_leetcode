#ifndef BI_SEARCH_TREE_H
#define BI_SEARCH_TREE_H

#include <iostream>
#include <queue>

using namespace std;


template <typename Comparable>
class BinarySearchTree {
private:
  struct BinaryNode {
    Comparable element;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode( const Comparable& theElement, BinaryNode* lt, BinaryNode* rt ): element{theElement}, left{lt}, right{rt}{}
    BinaryNode( Comparable && theElement, BinaryNode* lt, BinaryNode* rt ): element{std::move(theElement)}, left{lt}, right{rt}{}
  };

  BinaryNode* root;

  void insert( const Comparable& x, BinaryNode* & t) {
    if ( t == nullptr )
      t = new BinaryNode{ x, nullptr, nullptr };
    else if( t->element < x ) 
      insert( x, t->right );
    else if( t->element > x )
      insert( x, t->left );
    else
      ;
  }

  void insert( const Comparable&& x, BinaryNode* & t) {
    if ( t == nullptr )
      t = new BinaryNode{ std::move(x), nullptr, nullptr };
    else if( t->element < x ) 
      insert( std::move(x), t->right );
    else if( t->element > x )
      insert( std::move(x), t->left );
    else
      ;
  }

  void remove( const Comparable& x, BinaryNode* & t) {
    if (t == nullptr)
      return;
    if (x < t->element) 
      remove(x, t->left);
    else if (x > t->element)
      remove(x, t->right);
    else if(t->left != nullptr && t->right != nullptr) {
      // 右子树里的最左叶子节点作为当前节点值，同时递归地查找删除这个右子树最左叶子节点
      t->element = findMin( t->right )->element;
      remove(t->element, t->right);
    } else {
      BinaryNode* oldNode = t;
      t = ( t->left != nullptr ) ? t->left : t->right;
      delete oldNode;
    }
  }

  BinaryNode* findMin( BinaryNode* t ) const {
    if (t == nullptr)
      return nullptr;
    if (t->left == nullptr)
      return t;
    return findMin(root->left);
  }

  BinaryNode* findMax( BinaryNode* t ) const {
    if (t != nullptr) {
      while (t->right != nullptr) 
        t = t->right;
    }
    return t;
  }

  bool contains( const Comparable& x, BinaryNode* t ) const {
    if (t == nullptr) 
      return false;
    else if (t->element < x) 
      return contains( x, t->right );
    else if (t->element > x)
      return contains( x, t->left );
    else 
      return true;
  }

  void makeEmpty( BinaryNode* & t ) {
    if ( t != nullptr ) {
      makeEmpty( t->left );
      makeEmpty( t->right );
      delete t;
    }
    t = nullptr;
  }
  void printTree( BinaryNode* t, ostream& out ) const;

  BinaryNode* clone( BinaryNode* t ) const {
    if (t == nullptr)
      return nullptr;
    else 
      return new BinaryNode(t->element, clone(t->left), clone(t->right));
  }

public:
  BinarySearchTree();

  BinarySearchTree( const BinarySearchTree& rhs ) {
    root = clone(rhs.root);
  }

  /*移动构造函数待查*/
  BinarySearchTree( BinarySearchTree && rhs ) {
    root = clone(std::move(rhs).root);
  }

  ~BinarySearchTree() {
    makeEmpty();
  }

  const Comparable & findMin() const;
  const Comparable & findMax() const;

  int maxDepth( BinaryNode* & t ) {
    if (t == nullptr)
      return -1;
    /*
    return max(maxDepth(t->left), maxDepth(t->right)) + 1;
    */
    int depth = -1;
    queue<BinaryNode* &> que;
    que.push(t);
    while ( !que.empty() ) {
      depth ++;
      int cnt = 0, qs = que.size();
      while ( cnt < qs ) {
        cnt ++;
        t = que.front();
        que.pop();
        if( t->left )
          que.push(t->left);
        if( t->right )
          que.push(t->right);
      }
    }
    return depth;
  }

  bool contains( const Comparable& x ) const {
    return contains( x, root );
  }

  bool isEmpty() const;

  void printTree( ostream & out = cout ) const;

  void makeEmpty() {
    makeEmpty(root);
  }
  void insert( const Comparable& x ) {
    inster( x, root );
  }

  void insert( Comparable && x );
  void remove( const Comparable& x ) {
    remove( x, root );
  }

  BinarySearchTree& operator=( const BinarySearchTree& rhs );
  BinarySearchTree& operator=( BinarySearchTree && rhs );
};

#endif