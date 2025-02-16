#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDebug>
#include "ui_mainwindow.h" // Этот файл генерируется из вашего .ui файла

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void getState();
    void sendRepairRequest();
    void sendMoveRequest();
    void sendTurnRequest();
    void sendShootRequest();
    void parseState(const QJsonObject &json);
    void handleMapButtonClick();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QUrl serverUrl;

    // Локальные переменные для хранения координат
    int xCoord;
    int yCoord;
};
#endif // MAINWINDOW_H
