#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class HttpServer;
class QToolBar;
class EarthQuakeUsgs;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    HttpServer* mServer{nullptr};
    EarthQuakeUsgs* mEarthQuakeUsgs{nullptr};

    QToolBar* mToolBar{nullptr};

};
#endif // MAINWINDOW_H
