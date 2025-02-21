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
    void sendShootRequest();
    void sendMovementCommand(const QString &direction);
    void sendTurnCommand(const QString &direction);
    void parseState(const QJsonObject &json);
    void handleMapButtonClick();
    void paintEvent(QPaintEvent *event) override;
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
    QJsonArray jsonMap;
    int mapSize;
    std::string direction;

    // Локальные переменные для хранения координат
    int xCoord = 0;
    int yCoord = 0;
};
const std::string map_items[] { "Empty", "Enemy", "Bot"};
const std::string direction_items[] {"N", "S", "W", "E"};
const QString componentId[] {"gun_manip_001", "gun_001", "torso_001", "grab_manip_001", "left_leg_001", "right_leg_001"};
int int_from_map(const std::string& map);
int int_from_direction(const std::string& direction);

#endif // MAINWINDOW_H
