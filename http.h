#ifndef HTTP_H
#define HTTP_H

#include <QMap>
#include <QObject>
#include <QDebug>
//发送请求的类
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
//死循环
#include <QEventLoop>

class Http : public QObject
{
    Q_OBJECT
public:
    explicit Http(QObject *parent = nullptr);

    bool post_sync(QString Url, QMap<QString,QString> header, QByteArray requestData,QByteArray &replyData);//返回bool,参数：url，头，请求数据，应答数据

signals:

public slots:
};

#endif // HTTP_H
