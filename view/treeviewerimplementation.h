#ifndef TREEVIEWERIMPLEMENTATION_H
#define TREEVIEWERIMPLEMENTATION_H

#include <QFileDialog>
#include <QPainter>
#include <algorithm>
#include <QGraphicsTextItem>

#include "treeviewer.h"


template <class U> TreeViewer<U>::TreeViewer(QGraphicsScene *scene,std::function<QString(U&)> toString) : mScene(scene),mToString(toString)
{

}


template <class U> void TreeViewer<U>::saveTree(QString fileName)
{
    if(fileName=="") return;
    mScene->clearSelection();
    mScene->setSceneRect(mScene->itemsBoundingRect());
    auto saveScene=[this](QString fileName,QSize size,QRectF rectdest=QRectF(),QRectF rectsrc=QRectF())
    {
        QImage image(size, QImage::Format_ARGB32_Premultiplied);
        image.fill(QColor(255,255,255));
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        mScene->render(&painter,rectdest,rectsrc);
        image.save(fileName);
    };
    double width=mScene->sceneRect().width();
    if(width>32000)
    {
        double height=mScene->sceneRect().height();
        double chunkWidth=std::min(width,32000.0);
        double x=0;
        double xInit=mScene->sceneRect().x();
        double yInit=mScene->sceneRect().y();
        int i=1;
        auto save=[this,saveScene](double x,double width,double height,int i,QString fileName,double xInit,double yInit)
        {saveScene(fileName.section(".",0,-2)+"_"+QString::number(i)+".png",QSize(width,height),QRectF(0,0,width,height),QRectF(xInit+x,yInit,width,height));};
        for(x=0;x<=(width-chunkWidth);x+=chunkWidth,i++) save(x,chunkWidth,height,i,fileName,xInit,yInit);
        save(x,width-x,height,i,fileName,xInit,yInit);
    }
    else saveScene(fileName,mScene->sceneRect().size().toSize());
}


template <class U> void TreeViewer<U>::drawBinaryTree(GenericNode<U> * tree, double x, double y)
{
    mScene->clearSelection();
    mScene->clear();
    QPair<QPointF,QPointF> p=drawBinaryTree(tree,x,y,tree->depth());
    mScene->setSceneRect(mScene->itemsBoundingRect());
}

template <class U> QPair<QPointF,QPointF> TreeViewer<U>::drawBinaryTree(GenericNode<U> *tree, double x, double y, int depth)
{
    auto a=addText(mToString(tree->value()),x,y);
   // double widthIncrease=std::pow(2,tree->depth()-1)*20;
    if(tree->hasLeft())
    {
        double widthIncreaseB=std::pow(2,tree->left()->rightDepth())*20;
        auto b=drawBinaryTree(tree->left(),x-widthIncreaseB,y+50,depth-1);
        addLine(a.first,b.second);
    }
    if(tree->hasRight())
    {
        double widthIncreaseC=std::pow(2,tree->right()->leftDepth())*20;
        auto c=drawBinaryTree(tree->right(),x+widthIncreaseC,y+50,depth-1);
        addLine(a.first,c.second);
    }
    return a;
}

template <class U> TPNode * TreeViewer<U>::getNodesAndEdges(GenericNode<U> *tree, QList< QList<TPNode*> > & layers, QList< QPair<TPNode*,TPNode*> > & links, int depth, TPNode * parentNode)
{
    TPNode * node=new TPNode(mToString(tree->value()));
    layers[depth].push_back(node);
    if(parentNode!=nullptr) links.push_back(qMakePair(node,parentNode));
    if(tree->hasLeft() && tree->hasRight())
    {
        node->setLeft(getNodesAndEdges(tree->left(),layers,links,depth+1,node));
        node->setRight(getNodesAndEdges(tree->right(),layers,links,depth+1,node));
    }
    return node;
}

template <class U> void TreeViewer<U>::drawBinaryTree2(GenericNode<U> * tree,double x,double y)
{
    mScene->clearSelection();
    mScene->clear();
    // 1) store TPNodes by layer/depth with : its parent (and so on) : values
    QList< QList<TPNode*> > layers;
    QList< QPair<TPNode*,TPNode*> > links;
    int treeDepth=tree->depth();
    for(int i=0;i<treeDepth;i++)
    {
        layers.push_back(QList<TPNode*>());
    }
    getNodesAndEdges(tree,layers,links);
    // 2) print penultimate layer
    double dx=0;
    for(TPNode * node : layers[layers.size()-2])
    {
        dx+=(node->hasChildren() ? XINCREASE*2 : XINCREASE);
        node->value().setRealPosition(QPointF(x+dx,y+(layers.size()-2)*YINCREASE));
        addText(node);
    }

    // 3) print childs of penultimate layer
    for(TPNode * node : layers[layers.size()-2])
    {
        if(node->hasChildren())
        {
            node->left()->value().setRealPosition(QPointF(node->value().realPosition().x()-XINCREASE/2.0,y+(layers.size()-1)*YINCREASE));
            addText(node->left());
            node->right()->value().setRealPosition(QPointF(node->value().realPosition().x()+XINCREASE/2.0,y+(layers.size()-1)*YINCREASE));
            addText(node->right());
        }
    }


    // 4) print parents
    for(int depth=layers.size()-3;depth>=0;depth--)
    {
        for(TPNode * TPNode : layers[depth])
        {
            TPNode->value().setRealPosition(QPointF((TPNode->left()->value().realPosition().x()+TPNode->right()->value().realPosition().x())/2,y+depth*YINCREASE));
            addText(TPNode);
        }
    }

    // 5) link them
    for(QPair<TPNode*,TPNode*> p : links)
    {
        addLine(p.first->value().textPosition().second,p.second->value().textPosition().first);
    }
    mScene->setSceneRect(mScene->itemsBoundingRect());
}


template <class U> void TreeViewer<U>::addLine(QPointF a,QPointF b)
{
    mScene->addLine(QLineF(a,b));
}

template <class U> void TreeViewer<U>::addText(TPNode * node)
{
    node->value().setTextPosition(addText(node->value().text(),node->value().realPosition().x(),node->value().realPosition().y()));
}

template <class U> QPair<QPointF,QPointF> TreeViewer<U>::addText(QString text,double x,double y)
{
    QGraphicsTextItem * textItem=mScene->addText(text);
    textItem->setPos(x,y);
    QPointF center=textItem->boundingRect().center();
    return qMakePair(QPointF(center.x(),textItem->boundingRect().bottom())+QPointF(x,y),QPointF(center.x(),textItem->boundingRect().top())+QPointF(x,y));
}


#endif // TREEVIEWERIMPLEMENTATION_H
