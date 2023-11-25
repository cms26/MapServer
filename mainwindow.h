#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "metadatadisplay.h"
#include "mapitemfwd.h"

#include <QMainWindow>
#include <QGeoCoordinate>

class HttpServer;
class QToolBar;
class EarthQuakeUsgs;
class QLabel;
class MetadataDisplay;
class QDockWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onUpdateMouseLocation(QGeoCoordinate);
    void onUpdateSelectedItem(const MapItemPtr&);
    void toggleMetaData();

private:
    void setupStatusBar();

    Ui::MainWindow *ui;

    HttpServer* mServer{nullptr};
    EarthQuakeUsgs* mEarthQuakeUsgs{nullptr};

    QToolBar* mToolBar{nullptr};

    QLabel* mMouseLocationLabel{nullptr};
    QLabel* mSelectedMapItemInfo{nullptr};

    QDockWidget* mDockMetaData{nullptr};
    MetadataDisplay* mMetadataDisplay{nullptr};

};
#endif // MAINWINDOW_H
