#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:


    void on_checkBox_clicked(bool checked);

    void on_action1_clicked();

    void on_action2_clicked();

    void on_action3_clicked();


private:
    Ui::Widget *ui;
    QTcpSocket *socket;
};

#endif // WIDGET_H
