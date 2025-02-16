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
    void sendMoveRequest();
    void sendTurnRequest();
    void sendShootRequest();
    void parseState(const QJsonObject &json);
    void handleMapButtonClick();
    void paintEvent(QPaintEvent *event) override;
    void getMap();

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

