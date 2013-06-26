#ifndef TEXTPOSITION_H
#define TEXTPOSITION_H

#include <QString>
#include <QPair>
#include <QPointF>

/**
 * @brief The TextPosition class store the text and positions of a node
 */
class TextPosition
{
public:
    TextPosition(QString text);
    void setRealPosition(QPointF realPosition);
    void setTextPosition(QPair<QPointF, QPointF> position);
    QString text() const;
    QPair<QPointF,QPointF> textPosition() const;
    QPointF realPosition() const;
private:
    QString mText;
    QPair<QPointF,QPointF> mTextPosition;
    QPointF mRealPosition;
};

#endif // TEXTPOSITION_H
