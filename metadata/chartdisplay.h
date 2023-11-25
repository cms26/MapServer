#ifndef CHARTDISPLAY_H
#define CHARTDISPLAY_H

#include "mapitemfwd.h"
#include <QChartView>

class QLineSeries;
class QChart;
class QDateTimeAxis;
class QValueAxis;

class ChartDisplay : public QChartView
{
     Q_OBJECT
public:
    ChartDisplay(QWidget *parent = nullptr);

    QChartView* getWidget() const {return mChartView;}
    void setMetaItem(const MapItemPtr&);

    // Display type should match getDisplayTypesString
    enum struct DisplayType {
        Altitude,
        Latitude,
        Longitude
    };
    static QStringList getDisplayTypesString() {return {"Altitude (m)", "Latitude (deg)", "Longitude (deg)"};}
    void setDisplayType(const DisplayType& display);

private:
    QChartView *mChartView{nullptr};
    DisplayType mDisplayType{DisplayType::Altitude};
    QLineSeries *mSeries{nullptr};
    QDateTimeAxis* mAxisX{nullptr};
    QValueAxis* mAxisY{nullptr};

    void createAxes();
    void adjustAxesRange();
};

#endif // CHARTDISPLAY_H
