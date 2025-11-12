#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key &key); // TODO


protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insert_fix(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *current);
    void rotate_left(AVLNode<Key, Value> *current);
    void rotate_right(AVLNode<Key, Value> *current);
    AVLNode<Key, Value> *insert_traverse(AVLNode<Key, Value> *curr, const std::pair<const Key, Value> &keyValuePair); 
    void remove_fix(AVLNode<Key, Value> *current, int diff);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO

    //first insert 
    if(this->root_ ==nullptr){
        AVLNode<Key, Value>* new_node = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr); 
        this->root_ = new_node;
        return;
    }
    
    AVLNode<Key, Value>* curr_node = insert_traverse(static_cast<AVLNode<Key,Value>*>(this->root_), new_item);

    if(curr_node->getKey() == new_item.first){
        curr_node->setValue(new_item.second);
    }else if(curr_node->getKey() > new_item.first){
        AVLNode<Key, Value>* new_node = new AVLNode<Key, Value>(new_item.first, new_item.second, curr_node); 
        curr_node->setLeft(new_node);

        AVLNode<Key, Value>* parent = curr_node;
        parent->updateBalance(-1);
        if(parent->getBalance() != 0){
            insert_fix(parent, new_node);
        }
        // if(parent->getBalance() == 1){
        //     parent->setBalance(0);
        // } else if(parent->getBalance() == -1){
        //     parent->setBalance(0);
        // } else if(parent->getBalance() == 0){
        //     parent->setBalance(-1);
        //     insert_fix(parent, new_node);
        // }

    }else if(curr_node->getKey() < new_item.first){
        AVLNode<Key, Value>* new_node = new AVLNode<Key, Value>(new_item.first, new_item.second, curr_node); 
        curr_node->setRight(new_node);

        AVLNode<Key, Value>* parent = curr_node;
        parent->updateBalance(1);
        if(parent->getBalance() != 0){
            insert_fix(parent, new_node);
        }
        // if(parent->getBalance() == -1){
        //     parent->setBalance(0);
        // } else if(parent->getBalance() == 1){
        //     parent->setBalance(0);
        // } else if(parent->getBalance() == 0){
        //     parent->setBalance(1);
        //     insert_fix(parent, new_node);
        // }
    }
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::insert_traverse(AVLNode<Key, Value> *curr, const std::pair<const Key, Value> &keyValuePair){
    if(curr == nullptr){
        return curr;
    }

    if(curr->getKey() == keyValuePair.first){
        return curr;
    }
    
    if(curr->getKey() > keyValuePair.first){
        if(curr->getLeft() == nullptr){
            return curr;
        }
        return insert_traverse(curr->getLeft(), keyValuePair);
    } else {
        if(curr->getRight() == nullptr){
            return curr;
        }
        return insert_traverse(curr->getRight(), keyValuePair);
    }

}

template<class Key, class Value>
void AVLTree<Key, Value>::insert_fix(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *current){
    if(parent == nullptr || parent->getParent() == nullptr){
        return;
    }

    AVLNode<Key, Value> *grand_parent = parent->getParent();

    if(grand_parent->getLeft() == parent){
        grand_parent->updateBalance(-1);
        if(grand_parent->getBalance() == 0){
            return;
        }else if(grand_parent->getBalance() == -1){
            insert_fix(grand_parent, parent);
        } else if(grand_parent->getBalance() ==-2){
            if(parent->getLeft() == current){
                //zig zig
                rotate_right(grand_parent);
                grand_parent->setBalance(0);
                parent->setBalance(0);
                return;
            } else {
                //zig zag
                rotate_left(parent); 
                rotate_right(grand_parent);
                if(current->getBalance() == -1){
                    parent->setBalance(0);
                    grand_parent->setBalance(1);
                    current->setBalance(0);
                    return;
                } else if(current->getBalance() == 0){
                    parent->setBalance(0);
                    grand_parent->setBalance(0);
                    current->setBalance(0);
                    return;
                } else if(current->getBalance() == 1){
                    parent->setBalance(-1);
                    grand_parent->setBalance(0);
                    current->setBalance(0);
                    return;
                }
            }
        }
    } else if(grand_parent->getRight() == parent){
        grand_parent->updateBalance(1);
        if(grand_parent->getBalance() == 0){
            return;
        } else if(grand_parent->getBalance() == 1){
            insert_fix(grand_parent, parent);
        } else if(grand_parent->getBalance() == 2){
            if(parent->getRight() == current){
                // zig zig
                rotate_left(grand_parent);
                grand_parent->setBalance(0);
                parent->setBalance(0);
                return;
            } else {
                // zig zag
                rotate_right(parent);
                rotate_left(grand_parent);
                if(current->getBalance() == 1){
                    parent->setBalance(0);
                    grand_parent->setBalance(-1);
                    current->setBalance(0);
                    return;
                } else if(current->getBalance() == 0){
                    parent->setBalance(0);
                    grand_parent->setBalance(0);
                    current->setBalance(0);
                    return;
                } else if(current->getBalance() == -1){
                    parent->setBalance(1);
                    grand_parent->setBalance(0);
                    current->setBalance(0);
                    return;
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotate_left(AVLNode<Key, Value> *current){
    AVLNode<Key, Value>* child = current->getRight();
    AVLNode<Key, Value>* temp = child->getLeft();
    AVLNode<Key, Value>* grand_parent = current->getParent();

    //set child
    if(grand_parent == nullptr){
        this->root_ = child;
        child->setParent(nullptr);
    } else if(grand_parent->getLeft() == current){
        child->setParent(grand_parent);
        grand_parent->setLeft(child);
    } else if(grand_parent->getRight() == current){
        child->setParent(grand_parent);
        grand_parent->setRight(child);
    }

    //set parent
    child->setLeft(current);
    current->setParent(child);
    current->setRight(temp);
    if(temp != nullptr){
        temp->setParent(current);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotate_right(AVLNode<Key, Value> *current){
    AVLNode<Key, Value>* child = current->getLeft();
    AVLNode<Key, Value>* temp = child->getRight();
    AVLNode<Key, Value>* grand_parent = current->getParent();


    //set child
    if(grand_parent == nullptr){
        this->root_ = child;
        child->setParent(nullptr);
    } else if(grand_parent->getLeft() == current){
        child->setParent(grand_parent);
        grand_parent->setLeft(child);
    } else if(grand_parent->getRight() == current){
        child->setParent(grand_parent);
        grand_parent->setRight(child);
    }

    //set parent
    child->setRight(current);
    current->setParent(child);
    current->setLeft(temp);
    if(temp != nullptr){
        temp->setParent(current);
    }

}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* remove_node = static_cast<AVLNode<Key, Value>*>(this->traverse_helper_remove(key, this->root_));
    if(remove_node == nullptr){
        return;
    }

    if(remove_node->getLeft() != nullptr && remove_node->getRight() != nullptr){
        AVLNode<Key, Value>* pred_node = static_cast<AVLNode<Key, Value>*>(this->predecessor(remove_node));
        this->nodeSwap(remove_node, pred_node);
    }

    AVLNode<Key, Value>* parent = remove_node->getParent();
    int diff = 0;

    if(parent != nullptr){
        if(parent->getLeft() == remove_node){
            diff = 1; 
        }else if(parent->getRight() ==remove_node){
            diff = -1;
        }
    }

    //delete and update pointer
    AVLNode<Key, Value>* right = remove_node->getRight();
    AVLNode<Key, Value>* left = remove_node->getLeft();

    if(right == nullptr && left == nullptr){
        if(parent == nullptr){
            this->root_ = nullptr;
        } else if(parent->getLeft() == remove_node){
            parent->setLeft(nullptr);
        } else{
            parent->setRight(nullptr);
        }
        delete remove_node;
        remove_fix(parent, diff);
        return;
    }
    
    
    if(right != nullptr && left == nullptr){
        if(parent == nullptr){
            this->root_ = right;
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
        remove_fix(parent, diff);
        return;
    } else if(left != nullptr && right == nullptr){
        if(parent == nullptr){
            this->root_ = left;
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
        remove_fix(parent, diff);
        return;
    }
    return;
    
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove_fix(AVLNode<Key,Value>* current, int diff){
    if(current == nullptr){
        return;
    }

    AVLNode<Key,Value>* parent = current->getParent();
    int ndiff = 0;
    if(parent != nullptr){
        if(parent->getLeft() ==current){
            ndiff = 1;
        } else{
            ndiff = -1;
        }
    }

    if(diff == -1){
        if(current->getBalance() + diff == -2){
            AVLNode<Key,Value>* taller_child = current->getLeft();
            if(taller_child->getBalance() == -1){
                rotate_right(current);
                current->setBalance(0);
                taller_child->setBalance(0);
                remove_fix(parent, ndiff);
            } else if(taller_child->getBalance() == 0){
                rotate_right(current);
                current->setBalance(-1);
                taller_child->setBalance(1);
            } else if(taller_child->getBalance() == 1){
                AVLNode<Key,Value>* grand_child = taller_child->getRight();
                rotate_left(taller_child);
                rotate_right(current);
                if(grand_child->getBalance() == 1){
                    current->setBalance(0);
                    taller_child->setBalance(-1);
                    grand_child->setBalance(0);
                }else if(grand_child->getBalance() == 0){
                    current->setBalance(0);
                    taller_child->setBalance(0);
                    grand_child->setBalance(0);
                } else if(grand_child->getBalance() == -1){
                    current->setBalance(1);
                    taller_child->setBalance(0);
                    grand_child->setBalance(0);
                }
                remove_fix(parent, ndiff);
            }
        }else if(current->getBalance() + diff == -1){
            current->setBalance(-1);
        }else if(current->getBalance() + diff == 0){
            current->setBalance(0);
            remove_fix(parent, ndiff);
        }
    } else if(diff == 1){
        if(current->getBalance() + diff == 2){
            AVLNode<Key,Value>* taller_child = current->getRight();
            if(taller_child->getBalance() == 1){
                rotate_left(current);
                current->setBalance(0);
                taller_child->setBalance(0);
                remove_fix(parent, ndiff);
            } else if(taller_child->getBalance() == 0){
                rotate_left(current);
                current->setBalance(1);
                taller_child->setBalance(-1);
            } else if(taller_child->getBalance() == -1){
                AVLNode<Key,Value>* grand_child = taller_child->getLeft();
                rotate_right(taller_child);
                rotate_left(current);
                if(grand_child->getBalance() == -1){
                    current->setBalance(0);
                    taller_child->setBalance(1);
                    grand_child->setBalance(0);
                }else if(grand_child->getBalance() == 0){
                    current->setBalance(0);
                    taller_child->setBalance(0);
                    grand_child->setBalance(0);
                } else if(grand_child->getBalance() == 1){
                    current->setBalance(-1);
                    taller_child->setBalance(0);
                    grand_child->setBalance(0);
                }
                remove_fix(parent, ndiff);
            }
        }else if(current->getBalance() + diff == 1){
            current->setBalance(1);
        }else if(current->getBalance() + diff == 0){
            current->setBalance(0);
            remove_fix(parent, ndiff);
        }
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
