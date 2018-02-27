#include "logger.h"

#include <QtDebug>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QtMessageHandler>

const QString Logger::infoIdentifier = "( )";
const QString Logger::warnIdentifier = "(!)";
const QString Logger::errorIdentifier = "(X)";
const QString Logger::fatalIdentifier = "(☠)";

class LoggerPrivate
{
    friend class Logger;

    static QTextStream *logStream;
    static QFile* logFile;
    static Logger::Verboseness level;

    static void _log (QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        // ignore INFO in normal mode
        if (level == Logger::Normal && type == QtDebugMsg)
            return;

        QString time = QDateTime::currentDateTime ().toString ("yyyy-MM-dd hh:mm:ss.zzz");
        QString identifier;

        switch (type)
        {
        default:
        case QtDebugMsg:
        // case QtInfoMsg:
            identifier = Logger::infoIdentifier;
            break;
        case QtWarningMsg:
            identifier = Logger::warnIdentifier;
            break;
        case QtCriticalMsg:
            identifier = Logger::errorIdentifier;
            break;
        case QtFatalMsg:
            identifier = Logger::fatalIdentifier;
            break;
        }

        if (logStream)
        {

#ifndef LOG_NO_VERBOSE
            if (level != Logger::Exhaustive)
            {
#endif

                (*logStream) << identifier << " " << time << " " << msg << "\r\n";
                logStream->flush ();

#ifndef LOG_NO_VERBOSE
            }
            else
            {
                (*logStream) << identifier << " " << time << " @" << context.function << ": " << msg << "\r\n";
            }
#endif

        }

        if (QtFatalMsg == type)
        {
            abort();
        }
    }
};

LoggerPrivate *p = nullptr;
QTextStream* LoggerPrivate::logStream = nullptr;
Logger::Verboseness LoggerPrivate::level = Logger::Normal;
QFile* LoggerPrivate::logFile = nullptr;

Logger *Logger::instance()
{
    static Logger oInstance;
    return &oInstance;
}

void Logger::debug(QString message)
{
    qDebug() << message;
}

void Logger::warning(QString messsage)
{
    qDebug() << messsage;
}

void Logger::critical(QString message)
{
    qDebug() << message;
}

void Logger::init(const QString &name, Verboseness level)
{
    if (p)
    {
        warning("Logger reinitializing, skipped");
        return;
    }
    p = new LoggerPrivate;
    QString identifier (name);
    if (identifier.isEmpty ())
        identifier = QDateTime::currentDateTime ().toString ("yyyyMMdd_hhmmss");
    p->level = level;

    QDir logDir ("logs");
    if (!logDir.exists())
        QDir::current().mkdir(logDir.dirName());

    QString filename (QString ("logs/log_%1.log").arg (identifier));
    p->logFile = new QFile(filename);

    if (p->logFile->open (QIODevice::WriteOnly | QIODevice::Append))
    {
        p->logStream = new QTextStream (p->logFile);
        debug( "Logger initialized to file:" + p->logFile->fileName () );
        qInstallMessageHandler (LoggerPrivate::_log);
    }
    else
    {
        critical( "Error opening log file" + p->logFile->fileName ());
        warning("Will redirect to console");
        delete p->logFile;
    }
}

void Logger::deinit()
{
    // restore the default one
    qInstallMessageHandler (0);
    if (p)
    {
        if (p->logFile)
        {
            p->logFile->close ();
            delete p->logFile;
            p->logFile = nullptr;
        }

        if (p->logStream)
        {
            delete p->logStream;
            p->logStream = nullptr;
        }

        delete p;
        p = nullptr;
    }
    else
    {
        warning("Logger not initialized");
    }

}
