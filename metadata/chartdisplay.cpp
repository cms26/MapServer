#include "chartdisplay.h"
#include "mapitem.h"

#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QComboBox>
#include <QLabel>
#include <QDateTimeAxis>
#include <QValueAxis>

const double PlotPadding = 0.1; // precentage

ChartDisplay::ChartDisplay(QWidget *parent) : QChartView(parent),
    mSeries(new QLineSeries),
    mAxisX(new QDateTimeAxis),
    mAxisY(new QValueAxis) {

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->createDefaultAxes();
    setChart(chart);
    setRenderHint(QPainter::Antialiasing);

    chart->addSeries(mSeries);
    createAxes();

    // TODO we should use a layout to fix the size issue - for now we use this
    setMinimumHeight(300);
}

void ChartDisplay::setMetaItem(const MapItemPtr& selectedName) {
    mSeries->clear();

    if(!selectedName) {
        chart()->setTitle("");
        return;
    }

    chart()->setTitle(selectedName->id());

    for(const auto& location: selectedName->coordinates()) {
        const auto& displayTime = location.timestamp().toMSecsSinceEpoch();
        switch(mDisplayType) {
            case DisplayType::Altitude:{
                mSeries->append(displayTime, location.coordinate().altitude());
                break;
            }
            case DisplayType::Latitude:{
                mSeries->append(displayTime, location.coordinate().latitude());
                break;
            }
            case DisplayType::Longitude: {
                mSeries->append(displayTime, location.coordinate().longitude());
                break;
            }
            default: {
                qWarning() << "Display type not valid - will not display data.";
                assert(false);
            }
        }
    }

    adjustAxesRange();
    chart()->update();
}

void ChartDisplay::setDisplayType(const DisplayType& display) {
    mDisplayType = display;
    const auto& displayNames = getDisplayTypesString();
    if(static_cast<int>(display) >= displayNames.size()) {
        assert(false);
        return;
    }
    mAxisY->setTitleText(displayNames.at(static_cast<int>(display)));
};

void ChartDisplay::adjustAxesRange() {
    QPair<QDateTime, QDateTime> minMaxAxisX {QDateTime::currentDateTimeUtc(), QDateTime::fromSecsSinceEpoch(0)};
    QPair<double, double> minMaxAxisY = {std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
    for(int index = 0; index < mSeries->count(); ++index) {
        minMaxAxisX.first = std::min<>(minMaxAxisX.first, QDateTime::fromMSecsSinceEpoch(mSeries->at(index).x()));
        minMaxAxisX.second = std::max<>(minMaxAxisX.second, QDateTime::fromMSecsSinceEpoch(mSeries->at(index).x()));
        minMaxAxisY.first = std::min<>(minMaxAxisY.first, mSeries->at(index).y());
        minMaxAxisY.second = std::max<>(minMaxAxisY.second, mSeries->at(index).y());
    }

    const auto& padding = (minMaxAxisY.second  - minMaxAxisY.first) * PlotPadding;
    mAxisY->setRange(minMaxAxisY.first - padding, minMaxAxisY.second + padding);
    mAxisX->setRange(minMaxAxisX.first, minMaxAxisX.second);
}

void ChartDisplay::createAxes() {
    mAxisX->setTitleText("Time");
    chart()->addAxis(mAxisX, Qt::AlignBottom);
    mSeries->attachAxis(mAxisX);

    mAxisY->setTitleText("Altitude (m)");
    chart()->addAxis(mAxisY, Qt::AlignLeft);
    mSeries->attachAxis(mAxisY);
}


