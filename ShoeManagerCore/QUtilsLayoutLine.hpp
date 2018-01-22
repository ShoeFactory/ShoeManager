#ifndef QUTILSLAYOUTLINE_HPP
#define QUTILSLAYOUTLINE_HPP

#include <QFrame>
#include "shoemanagercore_global.h"

class SHOEMANAGERCORESHARED_EXPORT QUtilsLayoutLine : public QFrame
{
public:
    QUtilsLayoutLine(QFrame::Shape shape=QFrame::HLine, QWidget *parent=0);
    void setColor(QString sixteen);
};

#endif // QUTILSLAYOUTLINE_HPP
