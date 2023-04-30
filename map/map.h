#ifndef MAP_H
#define MAP_H

#include <QWidget>

class MapItemsModel;
class QQuickView;

class Map : public QWidget
{
     Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

    MapItemsModel* model() const {return mModel;}

public slots:
    void onZoomIn();
    void onZoomOut();

 private:
    int zoomLevel();
    int maxZoomLevel();
    int minZoomLevel();

    QQuickView* mQmlView{nullptr};
    MapItemsModel* mModel{nullptr};
};

#endif // MAP_H
