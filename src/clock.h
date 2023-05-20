#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include "messagebox.h"

class Clock : public QObject
{
    Q_OBJECT

public:
    explicit Clock(QObject *parent = nullptr);
    void start();
    void pause();
    void setSpeed(int speed);
    void setHour(int hour);
    QTime time() const;
    int hour() const;
    int week() const;
    int day() const;
    int hourOfDay() const;
    void saveTime();
    int m_speed;
    messagebox* myclock;
    bool isBoxshow=0;

signals:
    void timeChanged(QTime time);
    void weekChanged(int week);

private slots:
    void onTimeout();

private:
    QTime m_time;
    QTimer *m_timer;
    int m_hour;
    int m_week;
    bool m_paused;
    int m_state=2;//0,暂停 1，暂停后重新开始 2，正常计时
    int m_remainingTime;
};

#endif // CLOCK_H
