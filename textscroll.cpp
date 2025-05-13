#include "textscroll.h"
#include <QDebug>
textScroll::textScroll( QWidget *parent) : QWidget(parent)
{

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
}

void textScroll::timeOut()
{
    qDebug()<<m_moveOffset<<m_moveSize;
    m_moveOffset+=m_pixelSize;

    if(m_moveOffset>m_moveSize)
    {
        m_moveOffset= 0;
    }

    update();
}

void textScroll::resizeEvent(QResizeEvent *event)
{

    font.setPixelSize(event->size().height()*0.75);

    m_showText = m_text;
    QFontMetrics metrics(font);
    int char_w = metrics.width(" ");
    setDelay(30,char_w*speed);

    int blankLine =width()/char_w+1;

    for(int i=0;i<blankLine;i++)
    {
        m_showText.insert(0," ");
    }
    m_moveSize=metrics.width(m_showText)+blankSuffix;
    m_moveOffset=0;

    update();
}

void textScroll::paintEvent(QPaintEvent *event)
{

      QPainter painter(this);
      painter.setFont(font);

      painter.setPen(QColor(120,120,120));
      painter.drawRect(QRect(0,0,width()-1,height()-1));    //绘制边框,方便看出

      painter.setPen(QColor(textColor));

      painter.drawText(QRect(-m_moveOffset,0,width()-1+m_moveOffset,height()-1),
                       Qt::AlignVCenter|Qt::AlignLeft,m_showText);



}


void textScroll::setDelay(int ms,int pixelSize)    //设置滚动延迟,多少ms滚动多少像素点
{

    this->m_ms=ms;
    this->m_pixelSize=pixelSize;
}


void textScroll::setText(QString text, QRgb textColor, float speed, int blankSuffix) //设置字体,调用该函数后,将会自动启动定时器来滚动字幕
{
    this->blankSuffix = blankSuffix;
    this->speed = speed;

    font.setFamily("Microsoft Yahei");
    font.setPixelSize(height()*0.75);

    this->textColor = textColor;

    m_text = text;
    m_showText = m_text;

    QFontMetrics metrics(font);
    int char_w = metrics.width(" ");
    setDelay(50,char_w*speed);

    int blankLine =width()/char_w+2;

    for(int i=0;i<blankLine;i++)
    {
        m_showText.insert(0," ");
    }


    m_moveSize=metrics.width(m_showText)+blankSuffix;

    m_moveOffset=0;
    if(!timer->isActive())
    {
        if(m_ms)
        {
            timer->start(m_ms);
        }
    }

}

void textScroll::restart()
{
    m_moveOffset=0;

    update();

}
