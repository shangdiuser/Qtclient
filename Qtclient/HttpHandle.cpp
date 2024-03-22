#include "HttpHandle.h"
#include<QDebug>
#include<QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include<QJsonObject>
#include<QJsonParseError>
#include<QJsonArray>
#include"Qtclient.h"

HttpHandle::HttpHandle(QObject *parent) :
    QObject(parent),manager(new QNetworkAccessManager(this))
{

}
//获取图片
QByteArray HttpHandle::getMusicImage(QString artist)
{
    QString musicImageUrl=QString("/")+artist+QString("/")+
            artist+QString(".png");
    QByteArray image =getRequest(musicImageUrl);
    return image;
}


//获取音乐列表
void HttpHandle::getMusicList(QString search)
{
    QByteArray jsonData = getRequest( "/musicList.json");
    qDebug()<<"void HttpHandle::getMusicList "<<search;

    QJsonParseError err;
    QJsonDocument document=QJsonDocument::fromJson(jsonData,&err);
    if(err.error==QJsonParseError::NoError){
        QJsonArray jsonArray = document.array();
        for(int i = 0;i<jsonArray.size();i++){
            QJsonObject jsonObj=jsonArray[i].toObject();
            QString name= jsonObj.value("name").toString();
            QString artist= jsonObj.value("artist").toString();
            QString album= jsonObj.value("album").toString();

            if(name == search || artist==search || album==search){
                qDebug()<<name<<artist<<album;
                QStringList musicList;
                musicList <<name<<artist<<album;
                qDebug()<<musicList;
             emit   signalMusic(musicList);
            }
        }

    }else{
        qDebug()<<"=QJsonParseError::NoError";
    }

}

//发起请求
QByteArray HttpHandle::getRequest(QString search)
{
    QString urlInt = search;
    //QString urlInt =QString("http://192.168.5.90/D%3A/%E9%9F%B3%E4%B9%90");
   // QString urlInt =QString("http://localhost/F%3A/%E4%B8%8B%E8%BD%BD/%E9%9F%B3%E4%B9%90/%E9%9F%B3%E4%B9%90");
    QString url =urlInt ;
    QNetworkRequest request;

    request.setUrl(QUrl(url));
     reply =  manager->get(request);
     QEventLoop event;

     connect(reply,&QNetworkReply::finished,&event,&QEventLoop::quit);
     event.exec(QEventLoop::ExcludeUserInputEvents);

    QByteArray buf = reply->readAll();
    qDebug()<<"reoly"<<buf;
    return buf;
}

//封装文件请求地址
QString HttpHandle::getMusicUrl(QString artist, QString name)
{
   QString musicUrl=QString("http://192.168.5.90/D%3A/%E9%9F%B3%E4%B9%90")+QString("/")
    // QString musicUrl=QString("http://localhost/F%3A/%E4%B8%8B%E8%BD%BD/%E9%9F%B3%E4%B9%90/%E9%9F%B3%E4%B9%90")+QString("/")
            +artist+QString("/")+name+QString("/")+name+QString(".mp3");
   return musicUrl;
}

//封装歌词
QString HttpHandle::getMusicLyric(QString artist, QString name)
{
    QString musicLyriUrl=QString("/")+artist+QString("/")+name+QString("/")+QString("歌词.txt");
    QByteArray lyric=getRequest(musicLyriUrl);
    return lyric;
}

void HttpHandle::ClokInfoShow(QJsonObject jsonData)
{
    
  

}

QByteArray HttpHandle::allInfo(QString id, QString name)
{
   // QString urlInt = search;
    QString urlInt =QString("http://localhost:8080/allInof");
   // QString urlInt =QString("http://localhost/F%3A/%E4%B8%8B%E8%BD%BD/%E9%9F%B3%E4%B9%90/%E9%9F%B3%E4%B9%90");
    QString url = urlInt;
    QNetworkRequest request;

    request.setUrl(QUrl(url));
    reply = manager->get(request);
    QEventLoop event;

    connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
    event.exec(QEventLoop::ExcludeUserInputEvents);

    QByteArray buf = reply->readAll();
    qDebug() << "reoly" << buf;

    return buf;
}





//打卡
QByteArray HttpHandle::Clock(const QString& employeeId)
{
  
    // 构造 JSON 数据
    QJsonObject jsonObject;
    jsonObject["employee_id"] = employeeId;
    jsonObject["punch_in_time"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    jsonObject["punch_out_time"] = QDateTime::currentDateTime().addSecs(8 * 3600).toString(Qt::ISODate);
    jsonObject["is_late"] = 0;
    jsonObject["is_absent"] = 0;
    jsonObject["fine_amount"] = 0;

    qDebug() << employeeId << "QJsonObject employeeId";

    // 转换为 JSON 文档
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();


    QString urlInt = QString("http://localhost:8080/Clock");

    QString url = urlInt;
    QNetworkRequest request;

    request.setUrl(QUrl(url));
    //reply = manager->get(request);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送 POST 请求
    QNetworkReply* reply = manager->post(request, jsonData);


    QEventLoop event;

    connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
    event.exec(QEventLoop::ExcludeUserInputEvents);

    QByteArray buf = reply->readAll();
    qDebug() << "reoly" << buf;

   

        return buf;
    }


