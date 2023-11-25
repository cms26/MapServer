#ifndef METADATADISPLAY_H
#define METADATADISPLAY_H

#include "mapitemfwd.h"
#include <QWidget>

class ChartDisplay;

QT_BEGIN_NAMESPACE
namespace Ui { class MetadataDisplay; }
QT_END_NAMESPACE

class MetadataDisplay: public QWidget
{
    Q_OBJECT
public:
    explicit MetadataDisplay(QWidget *parent = nullptr);
    void setMetaItem(const MapItemPtr&);

public slots:
    void onAntialiasing(const bool);
    void onDisplayChange(const int);

private:
    Ui::MetadataDisplay *ui;
    ChartDisplay* mChartWidget{nullptr};
    MapItemPtr mSelectedName{nullptr};
};

#endif // METADATADISPLAY_H
