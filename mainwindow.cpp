#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httpserver.h"
#include "iconloader.h"
#include "mapitemsmodel.h"
#include "earthquakeusgs.h"

#include <QQuickWidget>
#include <QLayout>
#include <QToolBar>

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

    // connect interfaces to map
    mServer = new HttpServer(this, ui->centralwidget->model());
    connect(mServer, &HttpServer::updateMapItem, ui->centralwidget->model(), &MapItemsModel::addMapItem);

    mEarthQuakeUsgs = new EarthQuakeUsgs(this);
    connect(mEarthQuakeUsgs, &EarthQuakeUsgs::updateMapItem, ui->centralwidget->model(), &MapItemsModel::addMapItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

