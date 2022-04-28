#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QWidget>

class piechartwidget : public QWidget
{
    Q_OBJECT
public:
    explicit piechartwidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *);


signals:

public slots:
};

#endif // PIECHARTWIDGET_H
