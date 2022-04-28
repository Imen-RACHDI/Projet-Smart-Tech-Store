#include "amenn.h"
#include "ui_amenn.h"
#include "statistique.h"
#include "fournisseurs.h"
#include "reclamation.h"
#include <QDate>
#include <QProcess>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include <QQuickItem>

#include <QMessageBox>
#include <QTableWidget>
#include <QTableView>
#include <QMediaPlayer>
#include <QMessageBox>
#include<QString>
#include<QPdfWriter>
#include<QPainter>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QDesktopServices>
#include "arduino.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QComboBox>
#include<QObject>
#include <QMediaPlayer>
#include <QtWidgets/QMessageBox>
#include "smtp.h"
#include "qrcode.h"


using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{





    player = new QMediaPlayer(this);

    ui->setupUi(this);
     ui->tabWidget_2->setCurrentIndex(0);
    QTimer *timer=new QTimer(this);
    connect(timer ,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start();

    QDate date=QDate::currentDate();
    QString datetext=date.toString();
    ui->date_time->setText(datetext);

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->sendBtn1, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn1, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->sendBtn1_2, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn1_2, SIGNAL(clicked()),this, SLOT(close()));
       player1 = new QMediaPlayer(this);
       vw= new QVideoWidget(this);
       player1->setVideoOutput(vw);
       ui->server->setText("smtp.gmail.com");
           ui->port->setText("465");
           /*
           ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
           ui->quickWidget->show();

       auto obj = ui->quickWidget->rootObject();
           connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
           connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

           emit setCenter(36.102, 9.863);
           emit addMarker(36.102, 9.863);*/







ui->id->setValidator(new QIntValidator(0, 99999999, this));
ui->idrech->setValidator(new QIntValidator(0, 99999999, this));
ui->id2->setValidator(new QIntValidator(0, 99999999, this));
ui->qte->setValidator(new QIntValidator(0, 999, this));
ui->prix_achat->setValidator(new QIntValidator(0, 9999, this));
ui->prix_vente->setValidator(new QIntValidator(0, 9999, this));


int ret=a.connect_arduino();
       switch(ret){
       case(0):qDebug()<<"arduino is available and  connected  to :"<<a.getarduino_port_name();
           timerId = startTimer(1000);
           break;
       case(1):qDebug()<<"arduino is available but not connected to"<<a.getarduino_port_name();
           break;
       case(-1):qDebug()<<"arduino is not available";
       }

       QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));




    ui->tabfourn->setModel(f.afficher());
     ui->tableRec->setModel(tmpr.afficher());

}
void MainWindow::showtime()
{

   QTime time=QTime::currentTime();

 QString time_text=time.toString("hh : mm : ss");
 if((time.second()%2) == 0)
 {
     time_text[3] = ' ';
     time_text[8] = ' ';

 }
ui->digital_clock->setText(time_text);
}


void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
//***********************************************************************
     smtp = new Smtp(ui->uname_2->text(), ui->paswd_2->text(), ui->server_2->text(), ui->port_2->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname_2->text(), ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText());
    //***********************************************************************
    smtp = new Smtp(ui->uname_3->text(), ui->paswd_3->text(), ui->server_3->text(), ui->port_3->text().toInt());
   connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


   smtp->sendMail(ui->uname_3->text(), ui->rcpt_3->text() , ui->subject_3->text(),ui->msg_3->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_f_clicked()
{

        int id=ui->id->text().toInt();
        QString lib=ui->lib->text();
        int prix_achat=ui->prix_achat->text().toInt();
        int prix_vente=ui->prix_vente->text().toInt();
        int qte=ui->qte->text().toInt();
        QString date=ui->date->text();
        QString id_cat=ui->idcataj->text();
        produit f(id,lib,prix_achat,prix_vente,qte,date,id_cat);


        //partie controle saisie :
        bool verif_code,verif_libelle,verif_prix,verif_qt;
       verif_code=true;
       bool verif_categ=true;
      bool verif_date=true;
       verif_libelle=true;
       verif_qt=true;
       verif_prix=true;

       //verif id
        QString code = ui->id->text();
             QString numbers = "0123456789";
               bool verifHedhi = false;
               for(int i = 0; i < code.length(); i++){
                   for(int j = 0; j < numbers.length(); j++){
                       if(code[i] == numbers[j]){
                           verifHedhi = true;
                       }
                   }
                   if(verifHedhi == false ){
                       verif_code = false;
                       QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                   QObject::tr("Erreur id invalide .\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);

                       break;
                   }
               }
               // verif lib

               QString libb = ui->lib->text();
                      QString alphab = "azertyuiopqsdfghjklmwxcvbnéàçAZERTYUIOPQSDFGHJKLMWXCVBN";
                       verifHedhi = false;
                      for(int i = 0; i < libb.length(); i++){
                          for(int j = 0; j < alphab.length(); j++){
                              if(libb[i] == alphab[j]){
                                  verifHedhi = true;
                              }
                          }
                          if(verifHedhi == false ){
                              verif_libelle = false;
                              QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                          QObject::tr("libelle doit etre sous forme caractére .\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);

                              break;
                          }
                      }
                      // verif date

                      QString dat = ui->date->text();
                             QString alphabe = "0123456789/";
                              verifHedhi = false;
                             for(int i = 0; i < dat.length(); i++){
                                 for(int j = 0; j < alphabe.length(); j++){
                                     if(date[i] == alphabe[j]){
                                         verifHedhi = true;
                                     }
                                 }
                                 if(verifHedhi == false ){
                                     verif_date = false;
                                     QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                                 QObject::tr("date doit etre sous forme:   jj/mm/aaaa .\n"
                                                             "Click Cancel to exit."), QMessageBox::Cancel);

                                     break;
                                 }
                             }
                             // code_categ
                             QString id_catag = ui->idcataj->text();
                                    QString alphabbb = "azertyuiopqsdfghjklmwxcvbnéàçAZERTYUIOPQSDFGHJKLMWXCVBN";
                                     verifHedhi = false;
                                    for(int i = 0; i < id_catag.length(); i++){
                                        for(int j = 0; j < alphabbb.length(); j++){
                                            if(id_catag[i] == alphabbb[j]){
                                                verifHedhi = true;
                                            }
                                        }
                                        if(verifHedhi == false ){
                                            verif_categ = false;
                                            QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                                        QObject::tr("code categorie doit etre sous forme caractére .\n"
                                                                    "Click Cancel to exit."), QMessageBox::Cancel);

                                            break;
                                        }
                                    }






// démarrer la requête
 if((verif_code )&&(verif_libelle)&&( verif_date)&&(verif_categ)){
        QMessageBox msg;
        bool test=f.ajouter();
                        if((test))
                        {
ui->tabfourn->setModel(f.afficher());

             //  ui->tabconsu->setModel(c_temp.afficher());
                 msg.setText("Ajout avec succes");
            }

                else {
                msg.setText("Echec au niveau d ajout");
            }
            msg.exec();}

}

void MainWindow::on_supprimer_f_clicked()
{
int id2=ui->id2->text().toInt();
    produit f1; f1.setid(ui->id2->text().toInt());
    bool test1=f1.rech(id2);
    bool test=f1.supprimer(f1.getid());

     QMessageBox msg;
     if(test1==0){
         msg.setText("Monsieur ce produit n existe pas !!");}
    if(test)
    {



msg.setText("suppression avec succes");
ui->tabfourn->setModel(f.afficher());
}

else {
msg.setText("Echec au niveau de fournisseur supp");
}
msg.exec();
     }


void MainWindow::on_pushButton_2_clicked()
{
    int id=ui->id->text().toInt();
    QString lib=ui->lib->text();
    int prix_achat=ui->prix_achat->text().toInt();
    int prix_vente=ui->prix_vente->text().toInt();
    int qte=ui->qte->text().toInt();
    QString datee=ui->date->text();
    QString id_cat=ui->idcataj->text();


    QMessageBox msg;
    bool test=f.modifier(id,lib,prix_achat,prix_vente,qte,datee,id_cat);
                    if(test){

ui->tabfourn->setModel(f.afficher());
          //  ui->tabdossier->setModel(d_temp.afficher());
QMessageBox::information(nullptr,QObject::tr("modif bien"),
                  QObject::tr("biennnnnnnn \n"),QMessageBox::Cancel);
        }

                    else {
                        QMessageBox::information(nullptr,QObject::tr("modifier !!!!!!!!!!!!!!!"),
                                                  QObject::tr("*************************** \n"),QMessageBox::Cancel);
                        }
}

void MainWindow::on_rechercher_clicked()
{
    int id = ui->idrech->text().toInt();

        ui->tabfourn->setModel(f.rechercher(id));
}

void MainWindow::on_trier_clicked()
{
    ui->tabfourn->setModel(f.tridesc());
}

void MainWindow::on_pushButton_3_clicked()
{
    produit p;
     int test1=p.alerttt();

    if(test1==0)
        {
            QMessageBox::information(nullptr, QObject::tr("alert!!!!!!"),
                        QObject::tr("etat de stock : bien\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

    }
        else

    QMessageBox::information(nullptr,
         QString("il ya %1 quantité presque fini  !!!!")

             .arg(test1), " appeler le fournisseur svp num :+216 58 410 185 !!!!");
}

void MainWindow::on_image_clicked()
{

    QString filename=QFileDialog::getOpenFileName(this,tr("choose"),"",tr("Image (*.png *.jpg *.mp4)"));
    if(  QString::compare(filename,  QString())!=0) {
        QImage image;
        bool valid=image.load(filename);
        if(valid){
    image=image.scaledToHeight(ui->image1->height(),Qt::FastTransformation);
    image=image.scaledToHeight(ui->image1->height(),Qt::FastTransformation);
            ui->image1->setPixmap(QPixmap::fromImage(image));
        }
    }


}

void MainWindow::on_musique_clicked()
{

    player->setMedia(QUrl::fromLocalFile("C:/Users/tha3leb/Desktop/musique/George Wassouf Khsert Kol El Nas - خسرت كل الناس - جورج وسوف - (kurdish Lyric).mp3"));
       player->play();
       qDebug() << player ->errorString();
}

void MainWindow::on_video_clicked()
{
     QString filenamee=QFileDialog::getOpenFileName(this,tr("choose"),"",tr("video (*.avi *.mpg *.mp4)"));

player1->setMedia(QUrl::fromLocalFile(filenamee));
player1->play();
ui->statusbar->showMessage(("video yekhdem"));
}

void MainWindow::on_sendBtn_clicked()
{

}

void MainWindow::on_pushButton_4_clicked()
{

        QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->tabfourn);

        //colums to export
        obj.addField(0, "Code", "char(20)");
        obj.addField(1, "Prix", "char(20)");
        obj.addField(2, "Quantite", "char(20)");
        obj.addField(3, "Nom", "char(20)");
        obj.addField(4, "Type", "char(20)");

/*
        obj.addField(0, "id produit", "char(20)");
        obj.addField(1, "libelle", "char(20)");
        obj.addField(2, "Prix achat", "char(20)");
        obj.addField(3, "prix vente", "char(20)");
        obj.addField(4, "Quantite", "char(20)");
        obj.addField(5, "Date", "char(20)");
         obj.addField(6, "categorie", "char(20)");*/

        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }


}







void MainWindow::on_imprimer_1_clicked()
{
    produit ds;
                         QString text=ds.apercu_pdf();
                         ui->imprimer->setText(text);

                         QPrinter printer ;
                         printer.setPrinterName("imprim");
                         QPrintDialog dialog (&printer,this);
                         if(dialog.exec()==QDialog::Rejected) return ;
                         ui->imprimer->print(&printer);
}


void MainWindow::on_qr_code_clicked()
{
    int tabeq=ui->tabfourn->currentIndex().row();
           QVariant id=ui->tabfourn->model()->data(ui->tabfourn->model()->index(tabeq,0));
           QString idd= id.toString();
           QSqlQuery qry;
           qry.prepare("select * produit where CIN=:id");
           qry.bindValue(":CIN",idd);
           qry.exec();
              QString  lib,idcataj, prix_vente, prix_achat ,qte ,date;
           while(qry.next()){

               id=qry.value(1).toString();
               lib=qry.value(2).toString();
               idcataj=qry.value(3).toString();
              prix_vente=qry.value(4).toString();
               prix_achat=qry.value(5).toString();
              qte=qry.value(6).toString();
               date=qry.value(7).toString();


           }
           id=QString(idd);


           QrCode qr = QrCode::encodeText(idd.toUtf8().constData(), QrCode::Ecc::HIGH);

           // Read the black & white pixels
           QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
           for (int y = 0; y < qr.getSize(); y++) {
               for (int x = 0; x < qr.getSize(); x++) {
                   int color = qr.getModule(x, y);  // 0 for white, 1 for black

                   // You need to modify this part
                   if(color==0)
                       im.setPixel(x, y,qRgb(254, 254, 254));
                   else
                       im.setPixel(x, y,qRgb(0, 0, 0));
               }
           }
           im=im.scaled(200,200);
           ui->qrcodecommande->setPixmap(QPixmap::fromImage(im));
}



void MainWindow::on_pushButton_5_clicked()
{


    QString p="ariana";
    QDesktopServices::openUrl(QUrl("http://maps.google.com.sg/maps?q="+p+"&oe=utf-8&rls=org.mozilla:en-US:official&client=firefox-a&um=1&ie=UTF-8&hl=en&sa=N&tab=wl"));

}
/*
void MainWindow::timerEvent(QTimerEvent *event)
{

   QString ss=QString::fromUtf8(a.read_from_arduino()); // 9rina mel arduino

   int i=0;
   for(int j=0;j<4;j++)
   {
       if(ss[j].isNumber())
       {

           i=i*10+ss[j].digitValue();
       }

   }
   qDebug() << i;
   if(i<40)
       QMessageBox::information(nullptr, QObject::tr("database is open"),
                   QObject::tr("alarme de feu .\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

*/

void MainWindow::on_arduino_clicked()
{


    if(ui->tet->text().toInt()>=60)
        a.write_to_arduino("1");

}

void MainWindow::on_ajouter_clicked()
{
    int id=ui->lineEditID->text().toInt();
    QString nom=ui->linenom->text();
     QString prenom=ui->lineEdit_prenom->text();
      QString adresse_client=ui->lineEdit_ad->text();
       QString email_client =ui->lineEdit_mail->text();

       client c(id,nom, prenom, adresse_client, email_client);
       bool test=c.ajouter();
       if (test)
       {
           ui->tableView->setModel(cl.afficher());//refresh

           QMessageBox::information(nullptr, QObject::tr("ok"),
                   QObject::tr("ajout effectué "),QMessageBox::Cancel);

       }
       else

           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                   QObject::tr("ajout non effectué "),QMessageBox::Cancel);
}

void MainWindow::on_modifier_clicked()
{
    int id=ui->lineEditID->text().toInt();
    QString nom=ui->linenom->text();
     QString prenom=ui->lineEdit_prenom->text();
      QString adresse_client=ui->lineEdit_ad->text();
       QString email_client =ui->lineEdit_mail->text();

        QMessageBox msg;
        client c(id,nom, prenom, adresse_client, email_client);
        bool test=c.modifier(id,nom,prenom,adresse_client,email_client);
                        if(test){

    ui->tableView->setModel(cl.afficher());
              //  ui->tabdossier->setModel(d_temp.afficher());
    QMessageBox::information(nullptr,QObject::tr("modif bien"),
                      QObject::tr("biennnnnnnn \n"),QMessageBox::Cancel);
            }

                        else {
                            QMessageBox::information(nullptr,QObject::tr("modifier !!!!!!!!!!!!!!!"),
                                                      QObject::tr("*************************** \n"),QMessageBox::Cancel);
                            }

}

void MainWindow::on_supprimer_clicked()
{
    int id=ui->lineEdit_IDS->text().toInt();
    bool test=cl.supprimer(id);
    if (test)
    {
        ui->tableView->setModel(cl.afficher());

        QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("suppresion effectué "),QMessageBox::Cancel);

    }
    else

        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("suppresion non effectué "),QMessageBox::Cancel);
}



void MainWindow::on_pushButton_6_clicked()
{
    if(ui->checkBox_parnom->isChecked() && !ui->checkBox_nbr->isChecked())
         ui->tableView->setModel(cl.triParNom());
    else if (!ui->checkBox_parnom->isChecked() && ui->checkBox_nbr->isChecked())
         ui->tableView->setModel(cl.triParNbr());
    else if (ui->checkBox_parnom->isChecked() && ui->checkBox_nbr->isChecked())
         ui->tableView->setModel(cl.triParNom_Nbr());
    else
         ui->tableView->setModel(cl.triParId());

}

void MainWindow::on_pushButton_7_clicked()
{
    QPrinter print;
     print.setPrinterName("imprmer");
     QPrintDialog dialog(&print,this);
     if(dialog.exec()==QDialog ::Rejected) return;
     ui->tableView->render(&print);
}

void MainWindow::on_tabWidget2_currentChanged()
{
     ui->tableView->setModel(cl.afficher());
}
/*
void MainWindow::on_rechercher_2_textChanged()
{
   client cl;


 ui->tableView->setModel(cl.afficher());

               ui->tableView->setModel(cl.recherche(ui->rechercher->text()));





}*/

void MainWindow::on_tableView_doubleClicked(const QModelIndex index)
{
    QString rechercher=ui->tableView->model()->data(index).toString();

    QString Classe=cl.getClasse(rechercher);
    ui->label_classe->setText(Classe);

}



void MainWindow::on_sendBtn_2_clicked()
{
    // Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
      //   connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


     //Smtp *newMail  = new Smtp("nasreddine.elmadhkour@gmail.com","nasreddine1234@gmail.com","helolo","how are u");
     //delete newMail;

        // smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());

         QMessageBox::information(nullptr, QObject::tr("Succès"),
                     QObject::tr("Le mail a été envoyé avec succès.\n"
                                 "Cliquer sur Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_merier1_2_clicked()
{
    statistique s;
    s.exec();
}


////////////////////

void MainWindow::on_tabWidget2_tabCloseRequested(int index)
{
    ui->tabWidget2->removeTab(index);
}

void MainWindow::on_produitt_clicked()
{ ui->tabWidget->setCurrentIndex(0);//loutania
     ui->tabWidget_2->setCurrentIndex(1);//foukani

}
void MainWindow::on_pushButton_14_clicked()
{
    ui->tabWidget_3->setCurrentIndex(0);
        ui->tabWidget_2->setCurrentIndex(3);

}

void MainWindow::on_pushButton_9_clicked()
{
     ui->tabWidget2->setCurrentIndex(0);
     ui->tabWidget_2->setCurrentIndex(2);

}

void MainWindow::on_btnAjouter_clicked()
{
    int id=ui->ID->text().toInt();
    QString type=ui->TYPE->text();
    QString date=ui->DATE->text();
    QString description=ui->DESCRIPTION->toPlainText();







    reclamation r(id,type,date,description);
    bool test=r.ajouter();
    if(test)
    {



      ui->tableRec->setModel(tmpr.afficher());
        QMessageBox::information(nullptr,QObject::tr("Ajouter reclamation"),
                               QObject::tr("reclamation ajouté"),QMessageBox::Ok);

    }else
        QMessageBox::critical(nullptr,QObject::tr("Ajouter reclamation"),
                                      QObject::tr("reclamation non ajouté"),QMessageBox::Ok);
}

void MainWindow::on_Modifier_clicked()
{
    int id=ui->ID->text().toInt();
    QString type=ui->TYPE->text();
    QString date=ui->DATE->text();
    QString description=ui->DESCRIPTION->toPlainText();





    reclamation r(id,type,date,description);
    bool test=r.modifier(id);
    if(test)
    {  QString message2="\nVous avez modifié une reclamation";
        ;

       ui->tableRec->setModel(tmpr.afficher());
        QMessageBox::information(nullptr,QObject::tr("Modifier reclamation"),
                               QObject::tr("reclamation modifié"),QMessageBox::Ok);

    }else
        QMessageBox::critical(nullptr,QObject::tr("Modifier reclamation"),
                                      QObject::tr("reclamation non modifié"),QMessageBox::Ok);
}

void MainWindow::on_rechercher_3_clicked()
{
    ui->tableRec->setModel(tmpr.afficherRech(ui->comboBoxTri->currentText(),ui->lineEditRech->text()));
}

void MainWindow::on_trier_2_clicked()
{
    ui->tableRec->setModel(tmpr.afficherTri(ui->comboBoxTri->currentText()));
}

void MainWindow::on_pushButton_11_clicked()
{
    QPrinter printer;

       QPrintDialog dialog(&printer, this);
       dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
       if(dialog.exec()!=QDialog::Accepted){
           return;}
}

void MainWindow::on_Recuperer_clicked()
{
    int row =ui->tableRec->selectionModel()->currentIndex().row();
           QString id=ui->tableRec->model()->index(row,0).data().toString();
           QSqlQuery q("select * from reclamation where id="+id);


            while(q.next())
            {
                ui->ID->setText(q.value(0).toString());
                 ui->TYPE->setText(q.value(1).toString());
                   ui->DESCRIPTION->setPlainText(q.value(3).toString());

            }
            ui->tabWidget_3->setCurrentIndex(0);
}

void MainWindow::on_Supprimer_clicked()
{
    int row =ui->tableRec->selectionModel()->currentIndex().row();
           int id=ui->tableRec->model()->index(row,0).data().toInt();



           tmpr.supprimer(id);
           QString message2="\nVous avez supprimé une reclamation";


            ui->tableRec->setModel(tmpr.afficher());
}

void MainWindow::on_pushButton_10_clicked()
{
    QString fin=QString::number(ui->page_3->text().toInt());
     ui->tableRec->setModel(tmpr.afficherPg(fin));
}

void MainWindow::on_pushButton_12_clicked()
{
    data.clear();
    data=a.read_from_arduino();
   /* if(data.length()>0){*/
    ui->label_tmp->setText(data);
    QSqlQuery q;
    q.prepare("insert into temp values('"+data+"')");
    q.exec();/*}*/
}

void MainWindow::on_pushButton_15_clicked()
{
    QString id = ui->rechercher_2->text();

        ui->tableView->setModel(cl.recherche(id));
}


