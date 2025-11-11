#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:

    BinarySearchTree();          // TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    Node<Key, Value> *traverse_smallest(Node<Key, Value> *current) const;
    static Node<Key, Value> *predecessor(Node<Key, Value> *current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void  BinarySearchTree<Key, Value>::helper_clear(Node<Key, Value>* current);
    int helper_balanced(Node<Key, Value> *current) const;
    Node<Key, Value>* traverse_helper(Node<Key, Value>* curr, const std::pair<const Key, Value> &keyValuePair);
    static Node<Key, Value>* traverse_helper_pred(Node<Key, Value>* current, Node<Key, Value>* parent, int classifer);
    static Node<Key, Value> *traverse_helper_succ(Node<Key, Value> *current, Node<Key, Value> *parent, int classifer);
    Node<Key, Value>* traverse_helper_remove(const Key& key, Node<Key, Value>* current) const;


protected:
    Node<Key, Value>* root_;
    AVLNode<Key, Value> *traverse_remove(const Key &key, AVLNode<Key, Value> *current) const;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    current_ = ptr;

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = nullptr;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if(current_ == rhs->current_){
        return true; 
    } else{
        return false; 
    }
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if(current_ != rhs->current_){
        return true;
    } else{
        return false;
    }

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    if(current_ == nullptr){
        return *this;
    }
    if(current_->getRight() != nullptr){
        //need to put getleft in the argument!!!
        return traverse_helper_succ(current_->getRight(), current_, 1);
    } else {
        return traverse_helper_succ(current_, current_->getParent(), 2);
    }

}

template<class Key, class Value>
Node<Key, Value>* 
BinarySearchTree<Key, Value>::traverse_helper_succ(Node<Key, Value>* current, Node<Key, Value>* parent, int classifer){
    if(classifer == 1){
        if(current->getLeft() == nullptr){
            return current;
        } else{
            return traverse_helper_succ(current->getLeft(), current, 1);
        }

    } else if(classifer == 2){
        if(parent == nullptr){
            return nullptr;
        } else if(parent->getLeft() == current){
            return parent;
        }
        return traverse_helper_succ(parent, parent->getParent(), 2);
    }
}




/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    if(root_ ==NULL){
        Node<Key, Value>* new_node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL); 
        root_ = new_node;
        return;
    }
    
    Node<Key, Value>* curr_node = traverse_helper(root_, keyValuePair);

    if(curr_node->getKey() == keyValuePair.first){
        curr_node->setValue(keyValuePair.second);
    }else if(curr_node->getKey() > keyValuePair.first){
        Node<Key, Value>* new_node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, curr_node); 
        curr_node->setLeft(new_node);
    }else if(curr_node->getKey() < keyValuePair.first){
        Node<Key, Value>* new_node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, curr_node); 
        curr_node->setRight(new_node);
    }

}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::traverse_helper(Node<Key, Value>* curr, const std::pair<const Key, Value> &keyValuePair)
{
    if(curr == NULL){
        return curr;
    }

    if(curr->getKey == keyValuePair.first){
        return curr;
    }

    if(curr->getKey() > keyValuePair.first){
        if(curr->getLeft() == NULL){
            return curr;
        }
        return traverse_helper(curr->getLeft(), keyValuePair);
    } else {
        if(curr->getRight() == NULL){
            return curr;
        }
        return traverse_helper(curr->getRight(), keyValuePair);
    }

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* remove_node = traverse_helper_remove(key, root_);
    if(remove_node == nullptr){
        return;
    }

    if(remove_node->getLeft() != nullptr && remove_node->getRight() != nullptr){
        Node<Key, Value>* pred_node = predecessor(remove_node);
        nodeSwap(remove_node, pred_node);
    }

    Node<Key, Value>* parent = remove_node->getParent();
    Node<Key, Value>* right = remove_node->getRight();
    Node<Key, Value>* left = remove_node->getLeft();

    if(right == nullptr && left == nullptr){
        if(parent == nullptr){
            root_ = nullptr;
        } else if(parent->getLeft() == remove_node){
            parent->setLeft(nullptr);
        } else{
            parent->setRight(nullptr);
        }
        delete remove_node;
        return;
    }
    
    
    if(right != nullptr && left == nullptr){
        if(parent == nullptr){
            root_ = right;
            right->setParent(nullptr);
        } else{
            if(parent->getLeft() == remove_node){
                parent->setLeft(right);
            } else {
                parent->setRight(right);
            }
            right->setParent(parent);
        }

        delete remove_node;
        return;
    } else if(left != nullptr && right == nullptr){
        if(parent == nullptr){
            root_ = left;
            left->setParent(nullptr);
        } else{
            if(parent->getLeft() == remove_node){
                parent->setLeft(left);
            } else {
                parent->setRight(left);
            }
            left->setParent(parent);
        }

        delete remove_node;
        return;
    } 
}


template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::traverse_helper_remove(const Key& key, Node<Key, Value>* current) const {
    if(current == nullptr){
        return nullptr;
    }
    if(current->getKey() == key){
        return current;
    } else if(current->getKey() > key){
        return traverse_helper_remove(key, current->getLeft());
    } else if(current->getKey() < key){
        return traverse_helper_remove(key, current->getRight());
    }
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    if(current == nullptr){
        return nullptr;
    }
    if(current->getLeft() != nullptr){
        //need to put getleft in the argument!!!
        return traverse_helper_pred(current->getLeft(), current, 1);
    } else {
        return traverse_helper_pred(current, current->getParent(), 2);
    }
}


//1 if has left subtree (rightmost node of the left subtree); 2 if no left subtree (traverse up to the first right child and find the parent who's child is the first node that is the right child)

template<class Key, class Value>
Node<Key, Value>* 
BinarySearchTree<Key, Value>::traverse_helper_pred(Node<Key, Value>* current, Node<Key, Value>* parent, int classifer){
    if(classifer == 1){
        if(current->getRight() == nullptr){
            return current;
        } else{
            return traverse_helper_pred(current->getRight(), current, 1);
        }

    } else if(classifer == 2){
        if(parent == nullptr){
            return nullptr;
        } else if(parent->getRight() == current){
            return parent;
        }
        return traverse_helper_pred(parent, parent->getParent(), 2);
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    helper_clear(root_);
    root_ = nullptr;
}

template<typename Key, typename Value>
void  BinarySearchTree<Key, Value>::helper_clear(Node<Key, Value>* current){
    if(current == nullptr){
        return;
    }

    helper_clear(current->getRight());
    helper_clear(current->getLeft());
    delete current;
    return;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    return traverse_smallest(root_);
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::traverse_smallest(Node<Key, Value>* current) const{
    if(current == nullptr){
        return nullptr;
    }
    if(current->getLeft() != nullptr){
        return traverse_smallest(current->getLeft());
    }
    return current;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    return traverse_helper_remove(key, root_);
}

/**
 * Return true if the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    if(helper_balanced(root_) == -1){
        return false; 
    } else{
        return true;
    }
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::helper_balanced(Node<Key, Value>* current) const{
    if(current == nullptr){
        return 0;
    }

    int left_height = helper_balanced(current->getLeft());

    int right_height = helper_balanced(current->getRight());

    if(left_height == -1 || right_height == -1){
        return -1; 
    }

    if(std::abs(left_height - right_height) > 1){
        return -1;
    }

    return 1 + std::max(left_height, right_height);

}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
