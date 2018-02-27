#include "QUtilsLayoutLine.hpp"

QUtilsLayoutLine::QUtilsLayoutLine(QFrame::Shape shape, QWidget *parent)
{
    setFrameShape(shape);
    setFrameShadow(QFrame::Plain);
    setLineWidth(1);
}

void QUtilsLayoutLine::setColor(QString sixteen)
{
    setStyleSheet(QString("color:%1").arg(sixteen));
}
