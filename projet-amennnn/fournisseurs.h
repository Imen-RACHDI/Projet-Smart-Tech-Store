#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H
#include<QString>
#include<QSqlQueryModel>
#include<QFileDialog>
#include<QPrintDialog>
#include<QPrinter>

#include<QPdfWriter>

class produit
{
public:
    produit();
  produit(int,QString,int,int,int,QString,QString);
  int getid();
      QString getlib();
      int getprix_achat();
      int getprix_vente();
      int getqte();
      QString getdatee();
      QString getid_cat();
     void setid(int );
     void setlib(QString);
      void setprix_achat(int);
       void setprix_vente(int);
        void setqte(int);
     void setdatee(QString);
     void setid_cat(QString);
     bool ajouter();
     QSqlQueryModel* afficher();
     bool supprimer(int);
      int rech(int);
     bool modifier(int,QString,int,int,int,QString,QString);
     int stat_moins();
        int stat_plus();
        int alerttt();
         QString  apercu_pdf();


QSqlQueryModel * rechercher(int );
QSqlQueryModel * tridesc();
















private:
    int id;
    QString lib;
    int prix_achat;
    int prix_vente;
    int qte;
    QString datee;
    QString id_cat;

};

#endif // FOURNISSEURS_H
