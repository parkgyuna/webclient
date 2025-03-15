#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket_.readyRead();
    QObject::connect(&socket_, &QAbstractSocket::connected, this, &Widget::doConnected);
    QObject::connect(&socket_, &QAbstractSocket::disconnected, this, &Widget::doDisconnected);
    QObject::connect(&socket_, &QIODevice::readyRead, this, &Widget::doReadyRead);

}




Widget::~Widget()
{
    delete ui;
}
void Widget::doConnected()
{
    ui->pteMesseage->insertPlainText("Connected");
}
void Widget::doDisconnected(){

    ui->pteMesseage->insertPlainText("Disconnected");
}
void Widget::doReadyRead()
{
    ui->pteMesseage->insertPlainText(socket_.readAll());

}

void Widget::on_pbConnect_clicked()
{
    if(ui->ckssl->isChecked()){
        socket_.connectToHostEncrypted(ui->leHost->text(), ui->lePort->text().toUShort());}
    else{
        socket_.connectToHost(ui->leHost->text(), ui->lePort->text().toUShort());}

}


void Widget::on_pbDisconnect_clicked()
{
    socket_.disconnectFromHost();
}


void Widget::on_pbClear_clicked()
{
    ui->pteMesseage->clear();
}


void Widget::on_pbSend_clicked()
{
    socket_.write(ui->pteSend->toPlainText().toUtf8());
}



void Widget::on_ckssl_checkStateChanged ()
{
    if(ui->ckssl->isChecked()){ui->lePort->setText("443"); }
    else{ui->lePort->setText("80");}
}


