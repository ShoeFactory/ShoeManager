#ifndef ICONFONT_HPP
#define ICONFONT_HPP


#include <QFont>
#include "shoemanagercore_global.h"

class SHOEMANAGERCORESHARED_EXPORT IconFont
{
public:

    enum WindowIcon {
        HideIcon = 0xe607,
        CloseIcon = 0xe608,
        MaximizeIcon = 0xe606,
        MinimizeIcon = 0xe605,
        Left = 0xe60f,
        Right = 0xe60e
    };

public:

    ~IconFont();

public:

    static IconFont* getInstance();

public:

    QFont font() const;

private:

     IconFont();
     QFont oFont;
};

#endif // ICONFONT_HPP
