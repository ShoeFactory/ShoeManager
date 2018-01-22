#include "IconFont.hpp"

#include <QFontDatabase>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QCoreApplication>
#include <QFileInfo>

IconFont::IconFont()
{
    QString fontFullPath(":/iconfont.ttf");
    QFileInfo fontFile(fontFullPath);
    int id = 0;
    //如果字体文件存在，则加载文件，否则从资源中查找
    if (fontFile.isFile()){
        id = QFontDatabase::addApplicationFont(fontFullPath);
    }else{
        id = QFontDatabase::addApplicationFont(":/font/iconfont.ttf");
    }
    auto strFontNames= QFontDatabase::applicationFontFamilies(id);
    if(strFontNames.size() > 0)
    {
        auto strFontName = strFontNames.at(0);
        oFont = QFont(strFontName);
    }
}


IconFont::~IconFont()
{
}


IconFont* IconFont::getInstance()
{
    static IconFont oIconFont;
    return &oIconFont;
}

QFont IconFont::font() const
{
    return oFont;
}
