#include "Http.h"

Http::Http(QObject *parent) : QObject(parent)
{

}

bool Http::post_sync(QString Url, QMap<QString, QString> header, QByteArray requestData, QByteArray &replyData)
{
    //发送请求对象
    QNetworkAccessManager manager;

    //请求对象
    QNetworkRequest request;
    request.setUrl(Url);//设置请求的url

    QMapIterator<QString, QString> it(header);//遍历header
    while(it.hasNext()){
        it.next();
        request.setRawHeader(it.key().toLatin1(),it.value().toLatin1());
    }
    QNetworkReply *reply =  manager.post(request,requestData);
    QEventLoop l;
    //一旦服务器返回，reply会发出信号
    connect(reply,&QNetworkReply::finished,&l,&QEventLoop::quit);
    l.exec();  //死循环，reply发出信号，结束循环
    if(reply!=nullptr && reply->error()==QNetworkReply::NoError){
        replyData = reply->readAll();//读取服务器返回的数据
        qDebug()<<replyData; //这里replyData有数据，但是怎么没传过去
        return true;
    }else {
        qDebug()<<"请求失败";
        return false;
    }
}
