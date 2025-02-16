#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    networkManager = new QNetworkAccessManager(this);
    serverUrl = QUrl("https://checkrobo4.free.beeceptor.com");
    connect(ui->getStateButton, &QPushButton::clicked, this, &MainWindow::getState);
    connect(ui->repairButton, &QPushButton::clicked, this, &MainWindow::sendRepairRequest);
    connect(ui->moveButton, &QPushButton::clicked, this, &MainWindow::sendMoveRequest);
    connect(ui->turnButton, &QPushButton::clicked, this, &MainWindow::sendTurnRequest);
    connect(ui->shootButton, &QPushButton::clicked, this, &MainWindow::sendShootRequest);
    connect(ui->mapWidget, &QPushButton::clicked, this, &MainWindow::handleMapButtonClick); // Подключение для mapWidget

    // Заполнение directionComboBox
    ui->directionComboBox->addItem("N");
    ui->directionComboBox->addItem("S");
    ui->directionComboBox->addItem("W");
    ui->directionComboBox->addItem("E");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getState()
{
    QUrl url = serverUrl;
    url.setPath("/state");

    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (jsonDoc.isObject()) {
                QJsonObject json = jsonDoc.object();
                parseState(json);
            } else {
                QMessageBox::critical(this, "Error", "Invalid JSON response");
            }
        } else {
            QMessageBox::critical(this, "Error", "Network error: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::sendRepairRequest()
{
    QUrl url = serverUrl;
    url.setPath("/repair");

    QJsonObject json;
    json["id"] = ui->componentIdComboBox->currentText(); // Используем первый ComboBox

    QJsonDocument jsonDoc(json);
    QByteArray postData = jsonDoc.toJson();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, postData);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(this, "Success", "Repair request sent");
        } else {
            QMessageBox::critical(this, "Error", "Repair request failed: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::sendMoveRequest()
{
    QUrl url = serverUrl;
    url.setPath("/position");

    QJsonObject json;
    json["x"] = ui->xEdit->text().toInt();
    json["y"] = ui->yEdit->text().toInt();

    QJsonDocument jsonDoc(json);
    QByteArray postData = jsonDoc.toJson();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, postData);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(this, "Success", "Move request sent");
        } else {
            QMessageBox::critical(this, "Error", "Move request failed: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::sendTurnRequest()
{
    QUrl url = serverUrl;
    url.setPath("/turn");

    QJsonObject json;
    json["face_to"] = ui->directionComboBox->currentText();

    QJsonDocument jsonDoc(json);
    QByteArray postData = jsonDoc.toJson();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, postData);
    connect(reply, &QNetworkReply::finished, this,[=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(this, "Success", "Turn request sent");
        } else {
            QMessageBox::critical(this, "Error", "Turn request failed: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::sendShootRequest()
{
    QUrl url = serverUrl;
    url.setPath("/shoot");

    QJsonObject json;
    json["x"] = ui->xEdit->text().toInt();
    json["y"] = ui->yEdit->text().toInt();

    QJsonDocument jsonDoc(json);
    QByteArray postData = jsonDoc.toJson();
    QNetworkRequest request;

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, postData);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(this, "Success", "Shoot request sent");
        } else {
            QMessageBox::critical(this, "Error", "Shoot request failed: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::parseState(const QJsonObject &json)
{
    if (json.contains("robot") && json["robot"].isObject()) {
        QJsonObject robot = json["robot"].toObject();

        ui->robotIdLabel->setText("Robot ID: " + robot["id"].toString());
        qDebug() << "Robot ID:" << robot["id"].toString();

        // Обновление состояния торса
        if (robot.contains("torso") && robot["torso"].isObject()) {
            QJsonObject torso = robot["torso"].toObject();
            int torsoCapacity = torso["capacity"].toInt();
            ui->torsoProgressBar->setValue(torsoCapacity);
            qDebug() << "Torso capacity:" << torsoCapacity;
        }

        if (robot.contains("repair_station") && robot["repair_station"].isObject()) {
            QJsonObject repairStation = robot["repair_station"].toObject();
            int repairStationCapacity = repairStation["capacity"].toInt();
            ui->repairStationLabel_2->setValue(repairStationCapacity);
            qDebug() << "Repair Station capacity:" << repairStationCapacity;
        }

        // Обновление состояния орудия
        if (robot.contains("gun") && robot["gun"].isObject()) {
            QJsonObject gun = robot["gun"].toObject();
            int gunCapacity = gun["capacity"].toInt();
            int gunAmmo = gun["ammo"].toInt(); // Получаем количество патронов
            ui->gunProgressBar->setValue(gunCapacity);
            ui->gunAmmoLabel->setText(QString::number(gunAmmo)); // Обновляем gunAmmoLabel
            qDebug() << "Gun capacity:" << gunCapacity;
            qDebug() << "Gun ammo:" << gunAmmo;
        }

        // Обновление состояния орудийного манипулятора
        if (robot.contains("gun_manip") && robot["gun_manip"].isObject()) {
            QJsonObject gunManip = robot["gun_manip"].toObject();
            int gunManipCapacity = gunManip["capacity"].toInt();
            ui->gunManipProgressBar->setValue(gunManipCapacity);
            qDebug() << "Gun Manip capacity:" << gunManipCapacity;
        }

        // Обновление состояния хватательного манипулятора
        if (robot.contains("grab_manip") && robot["grab_manip"].isObject()) {
            QJsonObject grabManip = robot["grab_manip"].toObject();
            int grabManipCapacity = grabManip["capacity"].toInt();
            ui->grabManipProgressBar->setValue(grabManipCapacity);
            qDebug() << "Grab Manip capacity:" << grabManipCapacity;
        }

        // Обновление состояния левой ноги
        if (robot.contains("left_leg") && robot["left_leg"].isObject()) {
            QJsonObject leftLeg = robot["left_leg"].toObject();
            int leftLegCapacity = leftLeg["capacity"].toInt();
            ui->leftLegProgressBar->setValue(leftLegCapacity);
            qDebug() << "Left Leg capacity:" << leftLegCapacity;
        }

        // Обновление состояния правой ноги
        if (robot.contains("right_leg") && robot["right_leg"].isObject()) {
            QJsonObject rightLeg = robot["right_leg"].toObject();
            int rightLegCapacity = rightLeg["capacity"].toInt();
            ui->rightLegProgressBar->setValue(rightLegCapacity);
            qDebug() << "Right Leg capacity:" << rightLegCapacity;
        }

        // Обновление координат из локальных переменных
        ui->xEdit->setText(QString::number(xCoord));
        ui->yEdit->setText(QString::number(yCoord));

        if (json.contains("intelligence") && json["intelligence"].isObject()) {
            QJsonObject intelligence = json["intelligence"].toObject();
            ui->directionComboBox->setCurrentText(intelligence["faced_to"].toString());
        }

        // Заполнение componentIdComboBox
        ui->componentIdComboBox->clear();
        if (robot.contains("gun") && robot["gun"].isObject()) {
            ui->componentIdComboBox->addItem(robot["gun"].toObject()["ID"].toString());
        }
        if (robot.contains("gun_manip") && robot["gun_manip"].isObject()) {
            ui->componentIdComboBox->addItem(robot["gun_manip"].toObject()["ID"].toString());
        }
        if (robot.contains("grab_manip") && robot["grab_manip"].isObject()) {
            ui->componentIdComboBox->addItem(robot["grab_manip"].toObject()["ID"].toString());
        }
        if (robot.contains("torso") && robot["torso"].isObject()) {
            ui->componentIdComboBox->addItem(robot["torso"].toObject()["ID"].toString());
        }

        // Заполнение componentIdComboBox_2
        ui->componentIdComboBox->clear();
        if (robot.contains("gun") && robot["gun"].isObject()) {
            ui->componentIdComboBox->addItem(robot["gun"].toObject()["ID"].toString());
        }
        if (robot.contains("gun_manip") && robot["gun_manip"].isObject()) {
            ui->componentIdComboBox->addItem(robot["gun_manip"].toObject()["ID"].toString());
        }
        if (robot.contains("grab_manip") && robot["grab_manip"].isObject()) {
            ui->componentIdComboBox->addItem(robot["grab_manip"].toObject()["ID"].toString());
        }
        if (robot.contains("torso") && robot["torso"].isObject()) {
            ui->componentIdComboBox->addItem(robot["torso"].toObject()["ID"].toString());
        }
        if (robot.contains("repair_station") && robot["repair_station"].isObject()) {
            ui->componentIdComboBox->addItem(robot["repair_station"].toObject()["ID"].toString());
        }
    }
}

void MainWindow::handleMapButtonClick()
{
    getMap();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    int i = 0;
    QPainter painter(this);
    for(i = 0; i < jsonMap.size(); i++)
    {
        QJsonArray tmpArray = jsonMap.at(i).toArray();
        int x_rect = 45;
        int y_rect = 35;
        int y = 320+i*(y_rect+10);
        for(int j = 0; j < tmpArray.size(); j++)
        {
            int x= 45+j*(x_rect+10);
            switch(int_from_map(tmpArray.at(j).toString().toStdString()))
            {
            case 0:
                painter.setPen(Qt::darkGreen);
                painter.drawRect(x, y, x_rect, y_rect);
                break;
            case 1:
                painter.setPen(Qt::yellow);
                painter.drawRect(x, y, x_rect, y_rect);
                break;
            case 2:
                painter.setPen(Qt::blue);
                painter.drawRect(x, y, x_rect, y_rect);
            }
        }
    }
    if(i == 0) {
        painter.drawText(45,320,"НАЖМИТЕ НА КНОПКУ КАРТА");
    }
    painter.end();
}
void MainWindow::getMap()
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://qmaptest5.free.beeceptor.com/map"));
    networkManager->get(request);
    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject root = document.object();
            QJsonObject map = (root.value("map")).toObject();
            mapSize = map.value("size").toInt();
            jsonMap = (map.value("items")).toArray();
            qDebug() << document;
            reply->deleteLater();
            QWidget::repaint();
        }
        else
        {
            QMessageBox::critical(this, "Error", "Network error: " + reply->errorString());
        }
        reply->deleteLater();
    });
}
int int_from_map(const std::string& map)
{
    for (int i = 0; i < std::size(map_items); i++)
    {
        if (map == map_items[i])
            return i;
    }
    return 10;
}


