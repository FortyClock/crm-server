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
    int int_from_map(const std::string& map);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QUrl serverUrl;
    QJsonDocument document;
    QJsonArray jsonMap;
    int mapSize;

    // Локальные переменные для хранения координат
    int xCoord;
    int yCoord;
};
const std::string map_items[] { "Empty", "Enemy", "Bot"};
int int_from_map(const std::string& map);
#endif // MAINWINDOW_H

