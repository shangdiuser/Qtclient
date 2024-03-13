#ifndef HTTPHANDLE_H
#define HTTPHANDLE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class HttpHandle : public QObject
{
    Q_OBJECT
public:
    explicit HttpHandle(QObject *parent = nullptr);
    QByteArray getMusicImage(QString artist);
    void getMusicList(QString search);
    QByteArray getRequest(QString search);
    QString getMusicUrl(QString artist,QString name);
    QString getMusicLyric(QString artist,QString name);

    QByteArray Clock(const QString& employeeId);

signals:
//explicit HttpHandle(QObject *parent=nullptr);
 void signalMusic( QStringList musicList);
 void stateChanged();
public slots:

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

};

#endif // HTTPHANDLE_H
