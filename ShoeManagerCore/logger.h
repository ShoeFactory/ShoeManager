#ifndef LOGGER_H
#define LOGGER_H

#include "shoemanagercore_global.h"
#include <QString>

class SHOEMANAGERCORESHARED_EXPORT Logger
{
public:
    enum Verboseness
    {
        Normal,     ///< 排除 INFO 等级的调试信息， 仅记录 WARN, ERROR, FATAL
        Detailed,   ///< 全部调试信息：INFO, WARN, ERROR, FATAL
        Exhaustive  ///< 除详细信息外，还提供文件名和行号信息
    };

public:
    static Logger* instance();

    void init (const QString &name = QString(),     // 若不指定记录名称则默认为当前日期时间
               Verboseness level = Detailed);

    void deinit ();                                 // 关闭记录器 信息将不记录于记录文件中

    void debug(QString message);
    void warning(QString messsage);
    void critical(QString message);

public:
    static const QString infoIdentifier;
    static const QString warnIdentifier;
    static const QString errorIdentifier;
    static const QString fatalIdentifier;

private:
    Logger ()
    {

    }

    ~Logger ()
    {
        deinit ();
    }
};

#endif // LOGGER_H
