#ifndef REQUESTTOOL_H
#define REQUESTTOOL_H
#include <QtWidgets/QMainWindow>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

class requestTool : public QObject
{
    Q_OBJECT
public:
    explicit requestTool(QObject* parent = nullptr);
    void sendRequest(const QUrl& url, const QByteArray& data);

private:
       QNetworkAccessManager* networkManager;
};

#endif // REQUESTTOOL_H
