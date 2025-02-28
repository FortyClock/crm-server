#include "mapwidget.h"

MapWidget::MapWidget(QWidget *parent) : QWidget(parent) {
    // Инициализация данных для отрисовки (если необходимо)
    // points.append(QPoint(10, 10));
    // points.append(QPoint(50, 50));
}

void MapWidget::paintEvent(QPaintEvent *event) {
    int i = 0;
    QPainter painter(this);
    for(i = 0; i < jsonMap.size(); i++)
    {
        QJsonArray tmpArray = jsonMap.at(i).toArray();
        resize(tmpArray.size()*60, jsonMap.size()*45);
        int x_rect = 44;
        int y_rect = 34;
        int y = 10+i*(y_rect+10);
        for(int j = 0; j < tmpArray.size(); j++)
        {
            int x = x_rect+j*(x_rect+10);
            switch(intFromMap(tmpArray.at(j).toString().toStdString()))
            {
            case 0:
                painter.setPen(Qt::black);
                painter.setBrush(Qt::gray);
                painter.drawRoundedRect(x, y, x_rect, y_rect, 5, 5);
                break;
            case 1:
                painter.setPen(Qt::black);
                painter.setBrush(Qt::red);
                painter.drawRoundedRect(x, y, x_rect, y_rect, 5, 5);
                break;
            case 2:
                QPolygon polygon;
                painter.setPen(Qt::blue);
                painter.setBrush(Qt::blue);
                switch(intFromDirection(direction))
                {
                case 0: //North
                    polygon << QPoint(x + x_rect/2, y) << QPoint(x,y+y_rect) << QPoint(x + x_rect, y + y_rect);
                    painter.drawPolygon(polygon);
                    break;
                case 2: //South
                    polygon << QPoint(x + x_rect/2, y + y_rect) << QPoint(x, y) << QPoint(x + x_rect, y);
                    painter.drawPolygon(polygon);
                    break;
                case 3: //West
                    polygon << QPoint(x, y + y_rect/2) << QPoint(x + x_rect, y ) << QPoint(x + x_rect, y + y_rect);
                    painter.drawPolygon(polygon);
                    break;
                case 1: //East
                    polygon << QPoint(x + x_rect, y + y_rect/2) << QPoint(x, y) << QPoint(x, y + y_rect);
                    painter.drawPolygon(polygon);
                    break;
                }
                break;

            }
        }
    }
    painter.end();
}
void MapWidget::getJson(QJsonArray Map)
{
    jsonMap = Map;
}
int intFromMap(const std::string& map)
{
    for (int i = 0; i < std::size(map_items); i++)
    {
        if (map == map_items[i])
            return i;
       }
    return 10;
}
int intFromDirection(const std::string& direction)
{
    for (int i = 0; i < std::size(direction_items); i++)
    {
        if (direction == direction_items[i])
            return i;
    }
    return 10;
}
