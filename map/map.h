#ifndef MAP_H
#define MAP_H

#include "mapitemfwd.h"

#include <QWidget>
#include <QGeoCoordinate>


class MapItemsModel;
class QQuickView;


class Map : public QWidget
{
     Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

    MapItemsModel* model() const {return mModel;}

signals:
    void onUpdateMouseLocation(QGeoCoordinate);
    void onUpdateSelectedItem(const MapItemPtr&);

public slots:
    void onZoomIn();
    void onZoomOut();
    void onMouseLocationChanged(QVariant);

private slots:
    void onSelectedItemChanged(const MapItemPtr&);


 private:
    int zoomLevel();
    int maxZoomLevel();
    int minZoomLevel();

    QQuickView* mQmlView{nullptr};
    MapItemsModel* mModel{nullptr};
};

#endif // MAP_H
