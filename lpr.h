#ifndef LPR_H
#define LPR_H

#include <QObject>
#include "Http.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QImage>
#include <QBuffer>
#include <QMessageBox> //提示用



//获取access_token相关
const QString baiduTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString client_id = "ccGGZjbHrC5w5erxS4AdqmOy";
const QString client_secret = "HSpFgCvwrilZ9hjEo2DLfKX2y1dch0wF";

//车牌识别相关
const QString baiduLprUrl = "https://aip.baidubce.com/rest/2.0/ocr/v1/license_plate?access_token=%1";

class Lpr : public QObject
{
    Q_OBJECT
public:
    explicit Lpr(QObject *parent = nullptr);

    QString plateRecognition(QString fileName);//车牌识别
    QString getJsonValue(QByteArray ba,QString key1,QString key2);//解析返回的json数据

signals:

public slots:
};

#endif // LPR_H
