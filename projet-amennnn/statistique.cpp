#include "statistique.h"
#include "ui_statistique.h"
#include "ui_amenn.h"
#include<iostream>
#include "amenn.h"


statistique::statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);
}

statistique::~statistique()
{
    delete ui;
}
int statistique::Statistique_partie2()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from client where adresse_client = 'Tunis'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}

int statistique::Statistique_partie3()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from client where adresse_client = 'Sousse'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}
int statistique::Statistique_partie4()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from client where adresse_client = 'Sfax'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}
int statistique::Statistique_partie5()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from client where adresse_client = 'Nabeul'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}

void statistique::paintEvent(QPaintEvent *)
{

    int b=Statistique_partie2();
    cout<<b<<endl ;
    int c=Statistique_partie3();
    cout<<c<<endl ;
    int d=Statistique_partie4();
    cout<<c<<endl ;
    int e=Statistique_partie5();
    cout<<c<<endl ;



        float s2= b*100 ;
        float s3=c*100;
        float s4=d*100;
        float s5=e*100;
        float nb = b+c+d+e ;
        float q2 ;
        q2 = s2/nb ;
        float q3;
        q3=s3/nb;
        float q4;
        q4=s4/nb;
        float q5;
        q5=s5/nb;

        float y  ;
        y = (q2*360)/100 ;
        float m;
        m= (q3*360)/100;
        float p;
        p= (q4*360)/100;
        float v;
        v= (q5*360)/100;

    QPainter painter(this);
    QRectF size=QRectF(150,40,this->width()-600,this->width()-600);

    painter.setBrush(Qt::yellow);
    painter.drawPie(size,0,16*y);
    ui->label_2->setText(" Tunis") ;
    painter.setBrush(Qt::green);
    painter.drawPie(size,16*y,16*m);
    painter.setBrush(Qt::red);
    painter.drawPie(size,16*(m+y),16*p);
    painter.setBrush(Qt::blue);
    painter.drawPie(size,16*(m+y+p),16*v);


}

