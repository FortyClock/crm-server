#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::replyFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();

    QMessageBox msgBox;                 // диалоговое окно
    msgBox.setText(answer);             // устанавливаем текст
    msgBox.exec();                      // отображаем диалоговое окно
}

void MainWindow::on_pushButton_clicked()
{
    QNetworkRequest request(QUrl("https://cs1.htmlacademy.ru/content/blog/1331/index.html"));
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    manager->get(request);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(replyFinished(QNetworkReply*)));
}

