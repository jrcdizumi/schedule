#ifndef LOG_H
#define LOG_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include "src/clock.h"

class Log
{
public:
    enum LogLevel {
        Debug,
        Info,
        Warning,
        Error
    };

    Log(QString studentID,Clock* clock);
    ~Log();

    void init(QString studentID);
    void write(QString message, LogLevel level = Info);

private:
    QString m_studentID;
    QFile m_file;
    QTextStream m_stream;
    Clock* nowclock;
    QString FileName;
};

#endif // LOG_H
