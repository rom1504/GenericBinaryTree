#ifndef GENERICNODEIMPLEMENTATION_H

#include "genericnode.h"
#include <algorithm>

template <class T> GenericNode<T>::GenericNode() : mLeft(nullptr),mRight(nullptr)
{

}

template <class T> GenericNode<T>::GenericNode(T value) : mValue(value),mLeft(nullptr),mRight(nullptr)
{

}

template <class T> void GenericNode<T>::setValue(T value)
{
    mValue=value;
}

template <class T> T & GenericNode<T>::value() const
{
    return mValue;
}

template <class T> T & GenericNode<T>::value()
{
    return mValue;
}

template <class T> void GenericNode<T>::setLeft(GenericNode<T> * left)
{
    mLeft=left;
}

template <class T> void GenericNode<T>::setRight(GenericNode<T> * right)
{
    mRight=right;
}


template <class T> bool GenericNode<T>::hasChildren() const
{
    return mLeft!=nullptr && mRight!=nullptr;
}

template <class T> int GenericNode<T>::depth() const
{
    return 1+std::max(hasLeft() ? mLeft->depth() : 0,hasRight() ? mRight->depth() : 0);
}


template <class T> int GenericNode<T>::rightDepth() const
{
    return 1+(hasRight() ? mRight->rightDepth() : 0);
}


template <class T> int GenericNode<T>::leftDepth() const
{
    return 1+(hasLeft() ? mLeft->leftDepth() : 0);
}

template <class T> GenericNode<T> * GenericNode<T>::left()
{
    return mLeft;
}

template <class T> GenericNode<T> * GenericNode<T>::right()
{
    return mRight;
}


template <class T> bool GenericNode<T>::hasLeft() const
{
    return mLeft!=nullptr;
}

template <class T> bool GenericNode<T>::hasRight() const
{
    return mRight!=nullptr;
}


#define GENERICNODEIMPLEMENTATION_H

#endif // GENERICNODEIMPLEMENTATION_H
