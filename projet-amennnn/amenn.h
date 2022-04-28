#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMediaPlayer>
#include <QMainWindow>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QtWidgets/QMessageBox>
#include "exportexcelobjec.h"
#include "client.h"
#include <QQuickItem>
#include <QVariant>

#include "arduino.h"
#include "reclamation.h"

#include "fournisseurs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_f_clicked();

    void on_supprimer_f_clicked();



    void on_pushButton_2_clicked();

    void on_rechercher_clicked();

    void on_trier_clicked();

    void on_pushButton_3_clicked();

    void on_image_clicked();

    void on_musique_clicked();

    void on_pushButton_4_clicked();

    void on_video_clicked();
    void sendMail();
    void mailSent(QString);

    void on_sendBtn_clicked();
    void showtime();



    void on_imprimer_1_clicked();

    void on_pushButton_5_clicked();

    void on_qr_code_clicked();



    void on_arduino_clicked();


    void on_ajouter_clicked();

    void on_modifier_clicked();

    void on_supprimer_clicked();



    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_rechercher_2_textChanged();

    void on_tableView_doubleClicked(const QModelIndex index);

    void on_tabWidget2_currentChanged();

    void on_sendBtn_2_clicked();

    void on_pushButton_merier1_2_clicked();








    void on_tabWidget2_tabCloseRequested(int index);

    void on_produitt_clicked();

    void on_pushButton_9_clicked();

    void on_btnAjouter_clicked();

    void on_Modifier_clicked();

    void on_rechercher_3_clicked();

    void on_trier_2_clicked();

    void on_pushButton_11_clicked();

    void on_Recuperer_clicked();

    void on_Supprimer_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

private:
    Ui::MainWindow *ui;
    produit f;
      QMediaPlayer* player;
       QMediaPlayer* player1;
      QVideoWidget * vw;
      QProgressBar *bar;
      QSlider *slider;
      Arduino a;
       QByteArray data;
        int timerId;
       /*  void timerEvent(QTimerEvent *event);*/
         client cl;
          reclamation tmpr;
     signals:
         void setCenter(QVariant, QVariant);
         void addMarker(QVariant, QVariant);
};
#endif // MAINWINDOW_H
