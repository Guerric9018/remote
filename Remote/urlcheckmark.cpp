#include "urlcheckmark.h"
#include "notifiable.h"

#include <QPainter>

#include <QDebug>

UrlCheckMark::UrlCheckMark(QWidget *parent, Notifiable *output)
    : QWidget(parent)
    , output(output)
{
    backgroundPixmap = QPixmap(":/res/dots.png");
    setFixedSize(35, 35);
    if (backgroundPixmap.isNull()) {
        qWarning("PNG image failed to load");
    }
}

void UrlCheckMark::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap scaledPixmap = backgroundPixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledPixmap);
    QWidget::paintEvent(event);
}

void UrlCheckMark::updateState(bool validate)
{
    if (validate) {
        backgroundPixmap = QPixmap(":/res/url_checkmark.png");
        if (backgroundPixmap.isNull()) {
            qWarning("PNG image failed to load");
        }
        output->notify(":/res/info_icon.ico", "Connected", "Successfully connected to your phone");
        update();
    }
    else {
        backgroundPixmap = QPixmap(":/res/dots.png");
        if (backgroundPixmap.isNull()) {
            qWarning("PNG image failed to load");
        }
        update();
    }
}
