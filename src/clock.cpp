#include "clock.h"
#include <QFile>
#include <QTextStream>
Clock::Clock(QObject *parent)
    : QObject(parent)
    , m_time(QTime(0, 0))
    , m_timer(new QTimer(this))
    , m_speed(1)
    , m_hour(0)
    , m_week(1)
    , m_paused(false)
    , m_remainingTime(0)
{
    connect(m_timer, &QTimer::timeout, this, &Clock::onTimeout);
    QFile file("../schedule/data/time.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString data = stream.readAll();
        qDebug() << "文件内容：" << data;
        m_hour=data.toInt();
        if(m_hour>=2688)m_hour%=2688;
        file.close();
        qDebug()<<m_hour;
    }
    else
    {
        m_hour=0;
         qDebug()<<6666;
    }
    qDebug()<<m_hour;
}

void Clock::start()
{

    if (m_timer->isActive()||isBoxshow) {
          qDebug()<<"不可重复开启";
         return;
    }
    if (m_state==0) {
        m_timer->start(m_remainingTime);
    } else {
        m_time = QTime(0, 0);
        m_timer->start(10000 / m_speed); // 每10秒模拟1小时
    }
    m_state=1;
}

void Clock::pause()
{
    if(m_state==0||isBoxshow)
    {
        qDebug()<<"不可重复暂停";
        return;
    }
    m_state=0;
    m_remainingTime = m_timer->remainingTime();
    m_timer->stop();
}

void Clock::setSpeed(int speed)
{
    m_speed = speed;
    if (m_timer->isActive()) {
        m_timer->setInterval(10000 / m_speed);
    }
    qDebug()<<m_speed;
}

void Clock::setHour(int hour)
{
    m_hour = hour;
    m_time = QTime(0, 0).addSecs(m_hour * 3600);

    int newWeek = week();
    if (newWeek != m_week) {
        m_week = newWeek;
        emit weekChanged(m_week);
    }

    emit timeChanged(m_time);
}

QTime Clock::time() const
{
    return m_time;
}

int Clock::hour() const
{
    return m_hour;
}

int Clock::week() const
{
    return m_hour / 168 + 1;
}

int Clock::day() const
{
    return (m_hour % 168) / 24 + 1;
}

int Clock::hourOfDay() const
{
    return m_hour % 24;
}

void Clock::onTimeout()
{
    if(isBoxshow)
    {
        qDebug()<<"有闹钟提醒，无法进行下一次计时";
        return;
    }
    m_time = m_time.addSecs(3600); // 增加1小时
    m_hour++;
    if(m_hour>=2688)m_hour=0;
    int newWeek = week();
    if (newWeek != m_week) {
        m_week = newWeek;
        emit weekChanged(m_week);
    }
    qDebug() << "当前小时数：" << this->hour();
    qDebug() << "当前是第" << this->week() << "周，第" << this->day() << "天，第" << this->hourOfDay() << "小时";

    myclock=new messagebox();
    myclock->setMessage("当前是第"+QString::number(this->week())+"周，第"+QString::number(this->day())+ "天，第"+QString::number(this->hourOfDay())+ "小时");
    myclock->open();
    emit timeChanged(m_time);
    qDebug()<<"关闭成功";
        isBoxshow=true;
    m_state=2;
    connect(myclock, &messagebox::windowClosed, this, [=]() {
        isBoxshow=false;
        m_timer->start(10000 / m_speed);
    });




}
void Clock::saveTime()
{
    QFile file("../schedule/data/time.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream stream(&file);
        stream.setEncoding(QStringConverter::Utf8); // 设置编码格式为 UTF-8
        stream << this->m_hour;
        file.close();
    } else {
        // 文件无法打开
    }
}
