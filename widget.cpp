#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()
{
    //车牌识别按钮
    //开始识别

    QString text = lpr.plateRecognition("D:\\tetete.jpg");//车牌识别


    ui->plainTextEdit->setPlainText(text);
}

void Widget::on_pushButton_clicked()
{
    QImage image("D:\\test1.jpg");//已测试，不空
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label->setPixmap(pixmap);
}
