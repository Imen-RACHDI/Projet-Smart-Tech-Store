#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class client
{
    QString nom, prenom, adresse_client, email_client;
    int id;
public:
   //constructeurs
        client(){}
        client(int,QString,QString,QString,QString);
        //getters
        QString getNom(){return nom;}
        QString getPrenom(){return prenom;}
        QString getAdresse(){return adresse_client;}
        QString getEmail(){return email_client;}
        int getId(){return id;}
        //stters
        void setNom(QString n){nom=n;}
        void setprenom(QString p){prenom=p;}
        void setadresseclient(QString ad){adresse_client=ad;}
        void setemailclient(QString em){email_client=em;}
        void setId(int id){this->id=id;}
        //fonctionnalites de base
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int , QString , QString , QString , QString );

        //metier
                QSqlQueryModel * recherche(QString);

                  QSqlQueryModel * triParId();
                  QSqlQueryModel * triParNom();
                  QSqlQueryModel * triParNom_Nbr();
                  QSqlQueryModel * triParNbr();

                  QString getClasse(QString);

};


#endif // CLIENT_H
