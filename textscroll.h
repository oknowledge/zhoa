#ifndef TEXTSCROLL_H
#define TEXTSCROLL_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QFontMetrics>
#include <QResizeEvent>
class textScroll : public QWidget
{
    Q_OBJECT

private:

    QTimer* timer;          //时间定时器
    QRgb   textColor;
    QString m_text;
    QString m_showText;
    QFont font;
    int m_ms;
    int m_pixelSize;
    int m_moveOffset;
    int m_moveSize;
    int blankSuffix;
    float speed;        //滑动速度,取值在0.1~0.9之间,值越大越快

    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

public:

    explicit textScroll(QWidget *parent = 0);    //qRgb(int r, int g, int b)

    void setDelay(int ms,int pixelSize);    //设置滚动延迟,多少ms滚动多少像素点

    void setText(QString text,QRgb textColor,float speed=0.70,int blankSuffix=20); //设置字体,调用该函数后,将会自动启动定时器来滚动字幕
                                                   //blankSuffix:显示空白后缀长度,值越大,那么等待下一帧开头越久


    void restart();


signals:

public slots:
    void timeOut();


};

#endif // TEXTSCROLL_H
