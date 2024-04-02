#include "Qtclient.h"
#include "showOne.h"
#include "showData.h"
#include"SerialPortView.h"
#include <QtWidgets/QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 
   // Qtclient w;
  //  w.show();
  
    //showData data;
   // data.show();
   // data.initiShow();
   
  
    showOne s;
   s.showInfo();
    s.show();

   // SerialPortView l;
   // l.show();
  

    return a.exec();
}
