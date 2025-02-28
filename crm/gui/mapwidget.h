#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QJsonArray>

class MapWidget : public QWidget {
    Q_OBJECT

public:
    MapWidget(QWidget *parent = nullptr);
    void getJson(QJsonArray Map);
    QJsonArray jsonMap;
    std::string direction;


protected:
    void paintEvent(QPaintEvent *event) override;

private:
         // Здесь могут быть ваши данные для отрисовки
         // Например, QVector<QPoint> points;
};
const std::string map_items[]{"Empty", "Enemy", "Bot"};
const std::string direction_items[]{"N", "E", "S", "W"};
int intFromMap(const std::string& map);
int intFromDirection(const std::string& direction);
#endif // MAPWIDGET_H
