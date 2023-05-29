#include "map.h"
#include "mapitemsmodel.h"

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
    mQmlView->setSource(QUrl("qrc:/map/MapOverlay.qml"));;

    connect(mQmlView->rootObject(), SIGNAL(mousePositionChangedEvent(QVariant)),
                        this, SLOT(onMouseLocationChanged(QVariant)));

    connect(mModel, &MapItemsModel::onUpdateSelectedItem, this, &Map::onSelectedItemChanged);

    setLayout(new QVBoxLayout);
    layout()->addWidget(container);
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

void Map::onMouseLocationChanged(QVariant loc) {
    emit onUpdateMouseLocation(loc.value<QGeoCoordinate>());
}

void Map::onSelectedItemChanged(const MapItemPtr& data) {
    emit onUpdateSelectedItem(data);
}
