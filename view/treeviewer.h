#ifndef TREEVIEWER_H
#define TREEVIEWER_H

#include <QPair>
#include <QPointF>
#include <QGraphicsScene>
#include <QObject>

#include "../model/genericnode.h"
#include "textposition.h"

#define YINCREASE 60.0
#define XINCREASE 90.0

typedef GenericNode<TextPosition> TPNode;

/**
 * @brief The TreeViewer class display the tree on a QGraphicsScene
 */
template <class U> class TreeViewer
{
public:
    /**
     * @brief TreeViewer construct the object
     * @param scene the scene to display on
     * @param toString convert the value of a node to a QString
     * @param parent given to the QObject
     */
    TreeViewer(QGraphicsScene * scene,std::function<QString(U&)> toString);
    /**
     * @brief drawBinaryTree draw a binary tree recursively
     * @param tree the tree to draw
     * @param x the abscissa to draw in
     * @param y the ordinate to draw in
     */
    void drawBinaryTree(GenericNode<U> * tree, double x=0, double y=0);
    /**
     * @brief drawBinaryTree2 draw a binary tree iteratively
     * @param tree the tree to draw
     * @param x the abscissa to draw in
     * @param y the ordinate to draw in
     */
    void drawBinaryTree2(GenericNode<U> * tree, double x=0, double y=0);
    /**
     * @brief saveTree save the tree, if it is too big, save it in several images
     * @param numberOfLeaves number of leaves of the tree
     * @param newFile if true ask for a file even if it has already been saved somewhere
     */
    void saveTree(QString fileName);

private:
    /**
     * @brief addText display a text
     * @param text
     * @param x
     * @param y
     * @return
     */
    QPair<QPointF, QPointF> addText(QString text,double x,double y);
    /**
     * @brief addText display the text of a node and store its position in it
     * @param node
     */
    void addText(TPNode * node);
    /**
     * @brief addLine display a line between two points
     * @param a
     * @param b
     */
    void addLine(QPointF a,QPointF b);
    /**
     * @brief drawBinaryTree auxiliary function for the recursive drawing methog
     * @param tree
     * @param x
     * @param y
     * @param depth
     * @return
     */
    QPair<QPointF,QPointF> drawBinaryTree(GenericNode<U> * tree, double x, double y, int depth);
    /**
     * @brief getNodesAndEdges get informations on the tree in order to draw it iteratively
     * @param tree the tree
     * @param layers the layers of the tree : contain each depth of the tree
     * @param links the links
     * @param depth the depth of the tree
     * @param parentNode the parent node
     * @return the resulting new form tree (used inside the function)
     */
    TPNode *getNodesAndEdges(GenericNode<U> * tree, QList< QList<TPNode*> > & layers, QList< QPair<TPNode*,TPNode*> > & links, int depth=0, TPNode * parentNode=nullptr);

private:
    QGraphicsScene * mScene;
    std::function<QString(U&)> mToString;
};

#include "treeviewerimplementation.h"

#endif // TREEVIEWER_H
