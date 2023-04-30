#include "map.h"
#include "mapitemsmodel.h"
#include "mapitem.h"

#include <QQuickWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QTimer>

Map::Map(QWidget *parent) : QWidget(parent)
    , mQmlView(new QQuickView)
    , mModel(new MapItemsModel){

    QWidget* container = QWidget::createWindowContainer(mQmlView);
    // needed before setSource is called
    mQmlView->rootContext()->setContextProperty("mapItemsModel", mModel);
    mQmlView->setSource(QUrl("qrc:/map/MapOverlay.qml"));

    setLayout(new QVBoxLayout);
    layout()->addWidget(container);

//    MapItemPtr newItem(new MapItem());
//    newItem->addCoordinates({QGeoCoordinate(39.4227, -77.4187, 546)});
//    newItem->addCoordinates({QGeoCoordinate(39.45, -77.45, 555)});
//    newItem->setColor(QColorConstants::Svg::blueviolet);
//    mModel->addMapItem(newItem);

//    QTimer::singleShot(5000, [&, newItem]() {
//        MapItemPtr testItem(new MapItem());
//        testItem->addCoordinates({QGeoCoordinate(39.55, -77.55, 546)});
//        testItem->addCoordinates({QGeoCoordinate(39.99, -77.8, 555)});
//        testItem->setColor(QColorConstants::Svg::azure);
//        mModel->addMapItem(testItem);

//        newItem->addCoordinates({QGeoCoordinate(39.99, -77.8, 555)});
//    });
}

Map::~Map() {
    delete mModel;
    delete mQmlView;
}

int Map::zoomLevel() {
    return mQmlView->rootObject()->property("mapZoomLevel").toInt();
}

int Map::maxZoomLevel() {
    return mQmlView->rootObject()->property("maxZoomLevel").toInt();
}

int Map::minZoomLevel() {
    return mQmlView->rootObject()->property("minZoomLevel").toInt();
}

void Map::onZoomIn() {
    mQmlView->rootObject()->setProperty("mapZoomLevel",
                                        std::min<int>(maxZoomLevel(), zoomLevel() + 1));
}

void Map::onZoomOut() {
    mQmlView->rootObject()->setProperty("mapZoomLevel",
                                        std::max<int>(minZoomLevel(), zoomLevel() - 1));
}

