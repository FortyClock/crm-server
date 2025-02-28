#include "mainwindow.h"
#include "mapwidget.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkRequest>
#include <QPainter>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mapWidget = new MapWidget(this);
    ui->mapArea->setWidget(mapWidget);
    ui->mapArea->setWidgetResizable(false);
    networkManager = new QNetworkAccessManager(this);
    serverUrl = QUrl("http://localhost:3000");

    // Инициализация диалогового окна
    connectionDialog = new QDialog(this);
    connectionDialog->setWindowTitle("Ожидание подключения к серверу...");
    connectionDialog->setWindowFlags(Qt::WindowCloseButtonHint); // Add close button

    // Create label
    connectionStatusLabel = new QLabel("Подключение...", connectionDialog);
    connectionStatusLabel->setAlignment(Qt::AlignCenter);

    // Create layout
    QVBoxLayout *dialogLayout = new QVBoxLayout(connectionDialog);
    dialogLayout->addWidget(connectionStatusLabel);

    // Set fixed size
    connectionDialog->setFixedSize(300, 100);

    // Set layout
    connectionDialog->setLayout(dialogLayout);
    connectionDialog->show();

    // Инициализация таймера для проверки подключения
    connectionTimer = new QTimer(this);
    connect(connectionTimer, &QTimer::timeout, this, &MainWindow::checkServerConnection);
    connectionTimer->start(2000); // Проверяем каждые 2 секунды

    // Подключаем сигналы нажатия кнопок движения к слотам:
    connect(ui->moveForwardButton, &QPushButton::clicked, this, &MainWindow::moveForward);
    connect(ui->moveBackwardButton, &QPushButton::clicked, this, &MainWindow::moveBackward);
    connect(ui->moveLeftButton, &QPushButton::clicked, this, &MainWindow::moveLeft);
    connect(ui->moveRightButton, &QPushButton::clicked, this, &MainWindow::moveRight);

    connect(ui->getStateButton, &QPushButton::clicked, this, &MainWindow::getState);
    connect(ui->repairButton, &QPushButton::clicked, this, &MainWindow::sendRepairRequest);
    connect(ui->rotateLeftButton, &QPushButton::clicked, this, &MainWindow::rotateLeft);
    connect(ui->rotateRightButton, &QPushButton::clicked, this, &MainWindow::rotateRight);
    connect(ui->shootButton, &QPushButton::clicked, this, &MainWindow::sendShootRequest);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkServerConnection()
{
    QUrl url = serverUrl;
    url.setPath("/state"); // Используем endpoint /state

    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (jsonDoc.isObject()) {
                // Сервер доступен, можно закрыть диалоговое окно
                isConnectedToServer = true;
                connectionTimer->stop();
                connectionDialog->close();
                connectionDialog->deleteLater();
                connectionDialog = nullptr; // Set to nullptr after deleting
                connectionTimer->deleteLater();
                connectionTimer = nullptr;
                getState();
                QMessageBox::information(this, "Подключение установлено", "Успешное подключение к серверу!");
            } else {
                qDebug() << "Invalid JSON response from server";
            }
        } else {
            qDebug() << "Error connecting to server: " << reply->errorString();
        }
        reply->deleteLater();
    });
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!isConnectedToServer) {
        QMessageBox::information(this, "Предупреждение", "Не удалось подключиться к серверу. Приложение будет закрыто.");
        QApplication::quit(); // Закрываем приложение, если не подключились к серверу
    }
    event->accept(); // Разрешаем закрыть приложение, если подключились к серверу
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
    json["id"] = componentId[(ui->componentIdComboBox->currentIndex())];
    qDebug() << json;
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
        getState();
        getMap();
        reply->deleteLater();
    });
}

// **Реализуем слоты для кнопок движения:**
void MainWindow::moveForward() {
    sendMovementCommand("forward");
}

void MainWindow::moveBackward() {
    sendMovementCommand("backward");
}

void MainWindow::moveLeft() {
    sendMovementCommand("left");
}

void MainWindow::moveRight() {
    sendMovementCommand("right");
}

void MainWindow::sendMovementCommand(const QString &direction) {
    QUrl url = serverUrl;
    url.setPath("/position");  // Change path to /position

    int newX = xCoord;
    int newY = yCoord;

    if (direction == "forward") {
        newY -= 1;
    } else if (direction == "backward") {
        newY += 1;
    } else if (direction == "left") {
        newX -= 1;
    } else if (direction == "right") {
        newX += 1;
    }
    QJsonObject json;
    json["x"] = newX;
    json["y"] = newY;

    QJsonDocument jsonDoc(json);
    QByteArray postData = jsonDoc.toJson();
    qDebug() << json;

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, postData);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
        } else {
            QMessageBox::critical(this, "Error", "Move " + direction + " request failed: " + reply->errorString());
        }
        getState();
        reply->deleteLater();
    });
}

void MainWindow::sendTurnCommand(const QString &direction) {
    QUrl url = serverUrl;
    url.setPath("/turn"); // Новый endpoint для поворота

    QJsonObject json;
    json["faced_to"] = direction; // Передаем направление поворота (left или right)

    QJsonDocument jsonDoc(json);
    QByteArray postData = jsonDoc.toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    qDebug() << "JSON POST: " << jsonDoc.toJson(QJsonDocument::Compact);

    QNetworkReply *reply = networkManager->post(request, postData);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            //QMessageBox::information(this, "Success", "Rotate " + direction + " request sent");
        } else {
            QMessageBox::critical(this, "Error", "Rotate " + direction + " request failed: " + reply->errorString());
        }
    getState(); // Обновляем состояние после поворота
        reply->deleteLater();
    });
}
void MainWindow::rotateLeft()
{
    std::string direction = mapWidget->direction;
    int directionIndex = intFromDirection(mapWidget->direction);
    if (directionIndex == 0)
    {
        directionIndex = 4;
    }
    sendTurnCommand(QString::fromStdString(direction_items[directionIndex-1]));
}
void MainWindow::rotateRight()
{
    int directionIndex = intFromDirection(mapWidget->direction);
    if (directionIndex == 3)
    {
        directionIndex = -1;
    }
    sendTurnCommand(QString::fromStdString(direction_items[directionIndex+1]));

}
void MainWindow::sendShootRequest()
{
    QUrl url = serverUrl;
    url.setPath("/shoot");

    QJsonObject json;
    switch(intFromDirection(mapWidget->direction))
    {
    case 0: //North
        json["x"] = xCoord;
        json["y"] = yCoord - (ui->shootComboBox->currentText()).toInt();
        break;
    case 2: //South
        json["x"] = xCoord;
        json["y"] = yCoord + (ui->shootComboBox->currentText()).toInt();
        break;
    case 3: //West
        json["x"] = xCoord  - (ui->shootComboBox->currentText()).toInt();
        json["y"] = yCoord;
        break;
    case 1: //East
        json["x"] = xCoord + (ui->shootComboBox->currentText()).toInt();
        json["y"] = yCoord;
        break;
    }
    qDebug() << json;

    QJsonDocument jsonDoc(json);
    QByteArray postData = jsonDoc.toJson();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, postData);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(this, "Success", "Shoot request sent: " + reply->readAll());
        } else {
            QMessageBox::critical(this, "Error", "Shoot request failed: " + reply->errorString());
        }
        getState();
        reply->deleteLater();
    });
}

void MainWindow::parseState(const QJsonObject &json)
{
    if (json.contains("robot_state") && json["robot_state"].isObject()) {
        QJsonObject robot = json["robot_state"].toObject();

        // Обновление состояния торса
        if (robot.contains("torso") && robot["torso"].isObject()) {
            QJsonObject torso = robot["torso"].toObject();
            int torsoCapacity = torso["capacity"].toInt();
            ui->torsoProgressBar->setValue(torsoCapacity);
            qDebug() << "Torso capacity: " << torsoCapacity;
        }

        // Обновление координат
        if (json.contains("intelligence_inf") && json["intelligence_inf"].isObject()) {
            QJsonObject intelligence = json["intelligence_inf"].toObject();
            if (intelligence.contains("position") && intelligence["position"].isObject()) {
                mapWidget->direction = intelligence["faced_to"].toString().toStdString();
                qDebug() << mapWidget->direction;
                QJsonObject position = intelligence["position"].toObject();
                xCoord = position["x"].toInt();
                yCoord = position["y"].toInt();

                ui->xEdit->setText(QString::number(xCoord));
                ui->yEdit->setText(QString::number(yCoord));

                qDebug() << "Updated Coordinates: X=" << xCoord << ", Y=" << yCoord;
                // Обновляем карту после получения новых координат
                getMap();
            } else {
                qDebug() << "Error: 'position' object is missing in 'intelligence'";
            }
        } else {
            qDebug() << "Error: 'intelligence' object is missing in JSON";
        }

        if (robot.contains("repair_station") && robot["repair_station"].isObject()) {
            QJsonObject repairStation = robot["repair_station"].toObject();
            int repairStationCapacity = repairStation["repair_kit_num"].toInt();
            ui->repairKit->setText(QString::number(repairStationCapacity));
            qDebug() << "Repair Station capacity: " << repairStationCapacity;
        }

        // Обновление состояния орудия
        if (robot.contains("gun") && robot["gun"].isObject()) {
            QJsonObject gun = robot["gun"].toObject();
            int gunCapacity = gun["capacity"].toInt();
            int gunAmmo = gun["cartridges"].toInt(); // Получаем количество патронов
            ui->gunProgressBar->setValue(gunCapacity);
            ui->gunAmmoLabel->setText(QString::number(gunAmmo)); // Обновляем gunAmmoLabel
            qDebug() << "Gun capacity: " << gunCapacity;
            qDebug() << "Gun ammo: " << gunAmmo;
        }

        // Обновление состояния орудийного манипулятора
        if (robot.contains("gun_manip") && robot["gun_manip"].isObject()) {
            QJsonObject gunManip = robot["gun_manip"].toObject();
                int gunManipCapacity = gunManip["capacity"].toInt();
                ui->gunManipProgressBar->setValue(gunManipCapacity);
                qDebug() << "Gun Manip capacity: " << gunManipCapacity;
        }
        else{
            ui->gunManipProgressBar->setValue(0);
        }

        // Обновление состояния хватательного манипулятора
        if (robot.contains("grab_manip") && robot["grab_manip"].isObject()) {
            QJsonObject grabManip = robot["grab_manip"].toObject();
            int grabManipCapacity = grabManip["capacity"].toInt();
            ui->grabManipProgressBar->setValue(grabManipCapacity);
            qDebug() << "Grab Manip capacity: " << grabManipCapacity;
        }

        // Обновление состояния левой ноги
        if (robot.contains("left_leg") && robot["left_leg"].isObject()) {
            QJsonObject leftLeg = robot["left_leg"].toObject();
            int leftLegCapacity = leftLeg["capacity"].toInt();
            ui->leftLegProgressBar->setValue(leftLegCapacity);
            qDebug() << "Left Leg capacity: " << leftLegCapacity;
        }
        // Обновление состояния правой ноги
        if (robot.contains("right_leg") && robot["right_leg"].isObject()) {
            QJsonObject rightLeg = robot["right_leg"].toObject();
            int rightLegCapacity = rightLeg["capacity"].toInt();
            ui->rightLegProgressBar->setValue(rightLegCapacity);
            qDebug() << "Right Leg capacity: " << rightLegCapacity;
        }
    }
}

void MainWindow::getMap()
{
    QNetworkRequest request;
    QUrl url = serverUrl;
    url.setPath("/map");
    request.setUrl(url);
    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QJsonDocument root = QJsonDocument::fromJson(reply->readAll());
            QJsonObject rootObject = root.object(); // root - это ваш QJsonDocument
            QJsonObject dataObject = rootObject.value("data").toObject();
            QJsonArray itemsArray = dataObject.value("items").toArray();

            if (xCoord >= 0 && xCoord < itemsArray.size()) {
                QJsonArray rowArray = itemsArray.at(yCoord).toArray();

                if (yCoord >= 0 && yCoord < rowArray.size()) {
                    rowArray[xCoord] = QJsonValue("Bot"); // Используем оператор [] для изменения элемента
                    itemsArray[yCoord] = rowArray;       // Заменяем строку в массиве itemsArray
                    dataObject["items"] = itemsArray;       // Заменяем массив items в объекте data
                    rootObject["data"] = dataObject;       // Заменяем объект data в корневом объекте

                    root = QJsonDocument(rootObject);      // Обновляем QJsonDocument
                }
                QJsonObject map = (rootObject.value("data")).toObject();
                mapWidget->jsonMap = (map.value("items")).toArray();
                qDebug() << mapWidget->jsonMap;
            }
            else
            {
                QMessageBox::critical(this, "Error", "Network error: " + reply->errorString());
            }
            mapWidget->repaint();
            reply->deleteLater();
        }
    });
}
