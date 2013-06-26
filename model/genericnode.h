#ifndef GENERICNODE_H
#define GENERICNODE_H

/**
 * @brief The GenericNode class is a generic binary tree implementation
 */
template <class T> class GenericNode
{
public:
    GenericNode();
    GenericNode(T value);
    void setLeft(GenericNode<T> * left);
    void setRight(GenericNode<T> * right);
    GenericNode<T> * left();
    GenericNode<T> * right();
    bool hasLeft() const;
    bool hasRight() const;
    int depth() const;
    int rightDepth() const;
    int leftDepth() const;
    bool hasChildren() const;


    void setValue(T value);
    T & value() const;
    T & value();

private:
    T mValue;
    GenericNode<T> * mLeft;
    GenericNode<T> * mRight;

};


#include "genericnodeimplementation.h"

#endif // GENERICNODE_H
