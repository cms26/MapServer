#include "mainwindow.h"
#include "qgeocoordinate.h"
#include "qlabel.h"
#include "ui_mainwindow.h"
#include "httpserver.h"
#include "iconloader.h"
#include "mapitemsmodel.h"
#include "earthquakeusgs.h"
#include "mapitem.h"

#include <QQuickWidget>
#include <QLayout>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include <QGridLayout>
#include <QDockWidget>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mToolBar = new QToolBar(this);
    addToolBar(Qt::ToolBarArea::TopToolBarArea, mToolBar);
    mToolBar->addAction(IconLoader::getInstance().getIcon(IconLoader::IconName::ZoomIn),
                        "Zoom In", ui->centralwidget, &Map::onZoomIn);
    mToolBar->addAction(IconLoader::getInstance().getIcon(IconLoader::IconName::ZoomOut),
                        "Zoom Out", ui->centralwidget, &Map::onZoomOut);
    auto metaAction = mToolBar->addAction(IconLoader::getInstance().getIcon(IconLoader::IconName::MetaData),
                        "Meta Data", this, &MainWindow::toggleMetaData);
    metaAction->setCheckable(true);

    setupStatusBar();

    // connect interfaces to map
    mServer = new HttpServer(this, ui->centralwidget->model());
    connect(mServer, &HttpServer::updateMapItem, ui->centralwidget->model(), &MapItemsModel::addMapItem);

    mEarthQuakeUsgs = new EarthQuakeUsgs(this);
    connect(mEarthQuakeUsgs, &EarthQuakeUsgs::updateMapItem, ui->centralwidget->model(), &MapItemsModel::addMapItem);

    mMetadataDisplay = new MetadataDisplay(this);

    mDockMetaData = new QDockWidget(tr("chart"), this);
    mDockMetaData->setAllowedAreas( Qt::NoDockWidgetArea );
    mDockMetaData->setFeatures(QDockWidget::NoDockWidgetFeatures);
    mDockMetaData->setWidget(mMetadataDisplay);
    mDockMetaData->setHidden(true);
    addDockWidget(Qt::BottomDockWidgetArea, mDockMetaData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupStatusBar() {
    QStatusBar* status = statusBar();

    mSelectedMapItemInfo = new QLabel();
    status->addWidget(mSelectedMapItemInfo, 0);
    connect(ui->centralwidget,  &Map::onUpdateSelectedItem,
            this, &MainWindow::onUpdateSelectedItem);

    mMouseLocationLabel = new QLabel();
    status->addWidget(mMouseLocationLabel, 1);
    mMouseLocationLabel->setAlignment(Qt::AlignRight);
    connect(ui->centralwidget,  &Map::onUpdateMouseLocation,
            this, &MainWindow::onUpdateMouseLocation);
}

void MainWindow::onUpdateMouseLocation(QGeoCoordinate loc) {
    mMouseLocationLabel->setText(QGeoCoordinate(loc.latitude(), loc.longitude()).toString(
                                    QGeoCoordinate::CoordinateFormat::Degrees));
}

void MainWindow::onUpdateSelectedItem(const MapItemPtr& selectedName) {
    if(selectedName) {
        mSelectedMapItemInfo->setText(selectedName->id());
    } else {
        mSelectedMapItemInfo->setText("");
    }

    mMetadataDisplay->setMetaItem(selectedName);
}

void MainWindow::toggleMetaData() {
    mDockMetaData->setHidden(!mDockMetaData->isHidden());
}
