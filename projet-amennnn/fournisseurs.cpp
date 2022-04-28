#include "fournisseurs.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QDebug>
#include <QSqlQueryModel>
#include<QLineEdit>
#include<QString>
#include<QComboBox>
#include<QObject>
#include <QMediaPlayer>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>



#include "arduino.h"


produit::produit()
{
    id=0;
    prix_achat=0;
    prix_vente=0;
    qte=0;

}
produit::produit(int id,QString lib,int prix_achat,int prix_vente,int qte,QString datee,QString id_cat)
{
    this->id=id;
    this->lib=lib;
    this->prix_achat=prix_achat;
    this->prix_vente=prix_vente;
    this->qte=qte;
    this->datee=datee;
    this->id_cat=id_cat;

}

int produit:: getid()
{
    return id;
}
    QString produit:: getlib()
    {
    return lib;
    }
    int produit:: getprix_achat()
    {
    return prix_achat;
    }

    int produit:: getprix_vente()
    {
    return prix_vente;
    }
    int produit:: getqte()
    {
    return qte;
    }
    QString produit:: getdatee()
    {
        return datee;
    }
    QString produit:: getid_cat()
    {
        return id_cat;
    }


    void produit:: setid(int id )
    {
        this->id=id;
    }
    void produit:: setlib(QString lib )
    {
        this->lib=lib;
    }
    void produit:: setprix_achat(int prix_achat )
    {
        this->prix_achat=prix_achat;
    }

    void produit:: setprix_vente(int prix_vente )
    {
        this->prix_vente=prix_vente;
    }

    void produit:: setqte(int qte )
    {
        this->qte=qte;
    }
    void produit:: setdatee(QString datee )
    {
        this->datee=datee;
    }
    void produit:: setid_cat(QString id_cat )
    {
        this->id_cat=id_cat;
    }


    bool produit::ajouter()
    {
        QString num_idf=QString::number(id);
             QString num_achat=QString::number(prix_achat);
             QString num_vente=QString::number(prix_vente);
             QString num_qte=QString::number(qte);

            QSqlQuery query;
                  query.prepare("INSERT INTO produit (id,lib,prix_achat,prix_vente,qte,datee,id_cat) "
                                "VALUES (:id, :libe, :prxa, :prxv, :qtee, :date, :cat)");

                  query.bindValue(":id", num_idf);
                  query.bindValue(":libe", lib);
                  query.bindValue(":prxa", num_achat);
                  query.bindValue(":prxv", num_vente);
                  query.bindValue(":qtee", num_qte);
                   query.bindValue(":date", datee);
                   query.bindValue(":cat", id_cat);
                   return query.exec();


    }
    int produit::rech(int id)
    {
         QSqlQuery query;
         int t=0;


         query.exec("select from produit where id=:id");

         while(query.next())
                     {
                         t = t + 1;

                     }

        return t;

    }

    bool produit::supprimer(int id)
    {
         QSqlQuery query;
        query.prepare("Delete from produit where id=:id");

        query.bindValue(0, id);

        return query.exec();

    }

    QSqlQueryModel* produit::afficher()
    {
        QSqlQueryModel* model=new QSqlQueryModel();
              model->setQuery("SELECT* FROM produit");
              model->setHeaderData(0, Qt::Horizontal,QObject::tr("id"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("libelle"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix achat"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix vente"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("qantité"));
              model->setHeaderData(5, Qt::Horizontal, QObject::tr("date"));
              model->setHeaderData(6, Qt::Horizontal, QObject::tr("categorie"));


       return model;

    }

    bool produit::modifier(int id, QString lib , int prix_achat, int prix_vente, int qte, QString datee, QString id_cat )
    {
        QSqlQuery query;

            QString id_string= QString::number(id);
            QString achat_string= QString::number(prix_achat);
            QString vente_string= QString::number(prix_vente);
            QString qte_string= QString::number(qte);


            query.prepare("UPDATE produit SET  LIB = :LIB, PRIX_ACHAT= :PRIX_ACHAT, PRIX_VENTE= :PRIX_VENTE, QTE= :QTE, DATEE= :datee, ID_CAT= :ID_CAT WHERE ID = :ID ");
            query.bindValue(":ID", id_string);
            query.bindValue(":LIB", lib);
            query.bindValue(":PRIX_ACHAT", prix_achat);
            query.bindValue(":PRIX_VENTE", vente_string);
            query.bindValue(":QTE", qte_string);
            query.bindValue(":datee", datee);
            query.bindValue(":ID_CAT", id_cat);
            return query.exec();


    }
    QSqlQueryModel * produit::  rechercher(int id )
       {
           QString id_string=QString::number(id);
           QSqlQueryModel * model= new QSqlQueryModel();
           model-> setQuery("SELECT * FROM produit  where ID = "+id_string);


           return model;

       }
    QSqlQueryModel * produit::tridesc()
    {
        QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from produit order by  ID");

        return model;
    }
    int produit::stat_plus()
    {   int plus =0;
        int total =0;
        QSqlQuery query0;
         query0.exec("SELECT * FROM produit ");
         while(query0.next())
                     {
                         total = total + 1;

                     }
        QSqlQuery query;
         query.exec("SELECT * FROM produit WHERE qte > 10");
         while(query.next())
                     {
                         plus = plus + 1;

                     }
         return ((plus*100)/total);

    }
    int produit::stat_moins()
    {   int moins =0;
        int total =0;
        QSqlQuery query0;
         query0.exec("SELECT * FROM produit ");
         while(query0.next())
                     {
                         total = total + 1;

                     }
        QSqlQuery query;
         query.exec("SELECT * FROM produit WHERE qte < 10");
         while(query.next())
                     {
                         moins = moins + 1;

                     }
         return ((moins*100)/total);

    }

    int produit::alerttt()
    {
        int i=0 ;
        QSqlQuery query;
         query.exec("SELECT * FROM produit WHERE qte < 5");
         while(query.next())
                     {
             i=i+1 ;


                     }

         return i;

    }
    QString produit:: apercu_pdf()
              {
                  QString text="             * tous les produits  *       \n \n " ;
                  QSqlQuery query ;
                  QString i,x,z,m,n,b,a,c,d;


                   query.exec("select * from produit  ");
                   while (query.next())
                   {
                      i=query.value(0).toString();
                       x=query.value(1).toString();
                       z=query.value(2).toString();
                     m=query.value(3).toString();
                     n=query.value(4).toString();
                     b=query.value(5).toString();
                     a=query.value(6).toString();
                     c=query.value(7).toString();
                     d=query.value(8).toString();

             text += "\n id produit: "+z+"\n\n - libelle : "+ x+"\n  - - prix achat: "+ i+"\n--  prix vente:"+m+"\n__ qte :"+n+"\n--- date : "+b+"\n____categorie:   "+a+"______________\n";

                  }
                          return text ;




              }

