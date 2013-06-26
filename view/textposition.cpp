#include "textposition.h"

TextPosition::TextPosition(QString text) : mText(text)
{
}

QString TextPosition::text() const
{
    return mText;
}

QPair<QPointF, QPointF> TextPosition::textPosition() const
{
    return mTextPosition;
}

QPointF TextPosition::realPosition() const
{
    return mRealPosition;
}


void TextPosition::setTextPosition(QPair<QPointF,QPointF> textPosition)
{
    mTextPosition=textPosition;
}

void TextPosition::setRealPosition(QPointF realPosition)
{
    mRealPosition=realPosition;
}
