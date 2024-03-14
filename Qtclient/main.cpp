#include "Qtclient.h"
#include "showOne.h"
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

    showOne s;
    s.showInfo();
    s.show();


  

    return a.exec();
}
