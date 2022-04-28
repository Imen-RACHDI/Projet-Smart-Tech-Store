#include "client.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>
client::client(int id, QString nom, QString prenom, QString adresse_client, QString email_client)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->adresse_client=adresse_client;
    this->email_client=email_client;
}
bool client::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("INSERT INTO CLIENT (id, nom, prenom, adresse_client, email_client)" "VALUES (:id, :nom, :prenom, :adresse_client, :email_client)");
    //creation des variable
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":adresse_client",adresse_client);
    query.bindValue(":email_client",email_client);
    return query.exec(); //execute
}
QSqlQueryModel * client::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre d'achat"));




    return model;
}
bool client::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from client where id= :id");
    query.bindValue(":id",res);
    return query.exec();
}


bool client::modifier(int id, QString nom, QString prenom, QString adresse_client, QString email_client )
    {
        QSqlQuery query;

            QString id_string= QString::number(id);


            query.prepare("UPDATE client SET  id = :id, nom= :nom, prenom= :prenom, adresse_client= :adresse_client, email_client= :email_client WHERE id = :id ");
            query.bindValue(":id", id_string);
            query.bindValue(":nom", nom);
            query.bindValue(":prenom", prenom);
            query.bindValue(":adresse_client", adresse_client);
            query.bindValue(":email_client", email_client);

            return query.exec();


    }
//fonction recherche*****************

QSqlQueryModel * client::recherche(QString recherche)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client WHERE id LIKE '"+recherche+"%' OR nom LIKE '"+recherche+"%' OR prenom LIKE '"+recherche+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre d'achat"));

    return model;
}

//fonction tri*********
QSqlQueryModel * client::triParId()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from client ORDER BY CAST(id AS number)");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre d'achat"));

    return model;
}
QSqlQueryModel * client::triParNom()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from client ORDER BY nom");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre d'achat"));

    return model;
}
QSqlQueryModel * client::triParNbr()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from client ORDER BY nbr_achat DESC ;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre d'achat"));

    return model;
}

QSqlQueryModel * client::triParNom_Nbr()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from client ORDER by  nbr_achat DESC,nom ASC;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre d'achat"));

    return model;
}

QString client::getClasse(QString id)
{

    QSqlQuery query;

    QString req="SELECT nbr_achat from client where id="+id;
    query.prepare(req);
    query.exec();
    query.next();

    QVariant count=query.value(0);
    int nbr_achat = QVariant(count).toInt();

    if(nbr_achat>=200)
        return "Classe A";
    else if(nbr_achat>=100)
        return "Classe B";
    else if(nbr_achat>=0)
        return "Classe C";
    else return "";
}
