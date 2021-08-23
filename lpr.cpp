#include "lpr.h"
#include <iostream>
#include <QRegExp>

Lpr::Lpr(QObject *parent) : QObject(parent)
{

}

QString Lpr::plateRecognition(QString fileName)
{
    //1. 获取access_token
    QString accessToken;
    QString tokenUrl = QString(baiduTokenUrl).arg(client_id).arg(client_secret);
    //2.
    QMap<QString, QString> header;
    header.insert(QString("Content-Type"),QString("application/x-www-form-urlencoded"));
    QByteArray requestData; //发送的内容
    QByteArray replyData;   //服务器返回的内容


    Http m_http;
    bool result = m_http.post_sync(tokenUrl,header,requestData,replyData);
    if(result){
        QString key1 = "access_token";
        accessToken = getJsonValue(replyData,key1,"");
        qDebug()<<"accesstoken:"+accessToken;
    }else{
        //退出
//        this->close();
    }

    //组合url
    QString lprUrl = QString(baiduLprUrl).arg(accessToken);
//    qDebug()<<"1";
//    qDebug()<<lprUrl;

    QImage image(fileName);//已测试，不空

    QByteArray imgData;
    QBuffer buf(&imgData);
    image.save(&buf,"jpg");
    QByteArray imgDataBase64 = imgData.toBase64().simplified();
    buf.close();

    imgDataBase64= imgDataBase64.toPercentEncoding();//这里测试过都有数据
    requestData.append(QString("image=").toLatin1()+imgDataBase64);
    //再次请求
    replyData.clear();//用过了，清除
    result = m_http.post_sync(lprUrl,header,requestData,replyData);
    if(result){
        QString key1 = "words_result";
        QString key2 = "number";
        QString text = getJsonValue(replyData,key1,key2);
//        return text;
        qDebug()<<text;
    }
    else{
        QMessageBox::warning(NULL,"提示","识别失败");
    }
    return "";

}

QString Lpr::getJsonValue(QByteArray ba, QString key1,QString key2)
{
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(ba,&parseError);
    if(parseError.error == QJsonParseError::NoError)//如果没错
    {
        qDebug()<<"1";
        if(jsonDocument.isObject()){
            qDebug()<<"2";
            //jsonDocument转换成json对象
            QJsonObject jsonObj = jsonDocument.object();
            qDebug()<<"3";
            if(jsonObj.contains(key1)){
                QJsonValue jsonVal = jsonObj.value(key1);
                //下面判断类型
                qDebug()<<"4";
                if(jsonVal.isString()){//字符串
                    qDebug()<<"5";
                    qDebug()<<jsonVal.toString();
                    return jsonVal.toString();
                }else if(jsonVal.isArray()){//数组
                    qDebug()<<"6";
                    QJsonArray arr = jsonVal.toArray();//转换成jsonArray
                    QJsonValue jv = arr.at(0);//获取第一个元素
                    qDebug()<<jv.toString();
                    return jv.toString();
                }else if(jsonVal.isObject()){
                    qDebug()<<"7";
                    QJsonObject qso = jsonVal.toObject();
                    QJsonValue jsv = qso.value(key2);
                    qDebug()<<jsv.toString();
                }
            }
        }
    }
    return "";
}
