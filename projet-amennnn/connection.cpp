#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_projet2a");//inserer le nom de la source de données ODBC
    db.setUserName("bejaoui");//inserer nom de l'utilisateur system troism2a
    db.setPassword("troism2a");//inserer mot de passe de cet utilisateur

    if (db.open())
    test=true;





        return  test;



}
