#include "piechartwidget.h"
#include "fournisseurs.h"

#include <QPainter>

piechartwidget::piechartwidget(QWidget *parent) : QWidget(parent)
{

}

void piechartwidget::paintEvent(QPaintEvent *)
{
        produit tmpp;
        QPainter painter(this);
        QRectF size = QRectF(5,5, this->width()-10,this->width()-10);

        int moins = tmpp.stat_moins();
        moins= ((moins * 360) / 100);
        painter.setBrush(Qt::darkCyan);
        painter.drawPie(size, 0, (moins*16));

        int plus = tmpp.stat_plus();
        plus= ((plus * 360) / 100);
        painter.setBrush(Qt::cyan);
        painter.drawPie(size, ((360-plus)*16),(plus*16));

        setWindowTitle(tr("Chart"));
 resize(200,600);



}
