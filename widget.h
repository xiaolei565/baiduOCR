#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "lpr.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    Lpr lpr;
};

#endif // WIDGET_H
