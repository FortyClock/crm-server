#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDebug>
#include <QJsonArray>
#include <QPaintEvent>
#include <QPainter>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QCloseEvent>
#include "ui_mainwindow.h"
#include "mapwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class MapWidget;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void getState();
    void sendRepairRequest();
    void sendShootRequest();
    void sendMovementCommand(const QString &direction);
    void sendTurnCommand(const QString &direction);
    void parseState(const QJsonObject &json);
    void getMap();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void rotateLeft();
    void rotateRight();


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QUrl serverUrl;
    QJsonDocument document;
    int mapSize;
    MapWidget* mapWidget;

    // Локальные переменные для хранения координат
    int xCoord = 0;
    int yCoord = 0;

    // Добавляем переменные для диалогового окна
    QDialog *connectionDialog;
    QLabel *connectionStatusLabel;
    QTimer *connectionTimer;
    bool isConnectedToServer = false;


    void checkServerConnection();
    void closeEvent(QCloseEvent *event) override;
};
const QString componentId[]{"gun_manip_001", "gun_001", "torso_001",
                            "grab_manip_001", "left_leg_001", "right_leg_001"};
int intFromDirection(const std::string& direction);

#endif // MAINWINDOW_H
