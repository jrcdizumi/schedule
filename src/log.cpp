
#include "log.h"

Log::Log(QString studentID,Clock* clock)
{
    this->nowclock=clock;
    this->m_studentID=studentID;
    this->FileName="../schedule/log/"+studentID+".log";
    this->m_file.setFileName(this->FileName);
    m_file.open(QIODevice::Append | QIODevice::Text);
    m_stream.setDevice(&m_file);
}
Log::~Log()
{
    m_file.close();
    qDebug()<<"日志类析构成功";
}

void Log::write(QString message, LogLevel level)
{
    QString levelStr;//选择log等级
    switch (level) {
    case Debug:
        levelStr = "[DEBUG]";
        break;
    case Info:
        levelStr = "[INFO]";
        break;
    case Warning:
        levelStr = "[WARNING]";
        break;
    case Error:
        levelStr = "[ERROR]";
        break;
    }
    QString output = QString("第%1周 星期%2 %3点%4 %5\n")
                         .arg(this->nowclock->week())
                         .arg(this->nowclock->day())
                         .arg(this->nowclock->hourOfDay()).arg(levelStr).arg(message);
    m_stream<<output;
    m_stream.flush();

}
