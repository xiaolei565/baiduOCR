#ifndef OPENFILE_H
#define OPENFILE_H

#include <QObject>

class OpenFile : public QObject
{
    Q_OBJECT
public:
    explicit OpenFile(QObject *parent = nullptr);

    void openFile(QString fileName);//打开文件
    void closeFile();//关闭文件

signals:

public slots:
};

#endif // OPENFILE_H
