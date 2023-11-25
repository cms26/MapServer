
#include "metadatadisplay.h"
#include "ui_metadatadisplay.h"
#include "chartdisplay.h"

// #include <QLabel>
// #include <QComboBox>


MetadataDisplay::MetadataDisplay(QWidget *parent)
    : ui(new Ui::MetadataDisplay)
{
    ui->setupUi(this);

    ui->selectionCb->addItems(ChartDisplay::getDisplayTypesString());

    mChartWidget = new ChartDisplay(this);
    ui->gridLayout->addWidget(mChartWidget, 1, 0);

    connect(ui->antialiasCheckBox, &QCheckBox::clicked,
            this, &MetadataDisplay::onAntialiasing);
    connect(ui->antialiasCheckBox, &QCheckBox::clicked,
            this, &MetadataDisplay::onAntialiasing);
    connect(ui->selectionCb, static_cast<void (QComboBox::*)(int index)>(&QComboBox::currentIndexChanged),
            this, &MetadataDisplay::onDisplayChange);
}

void MetadataDisplay::onDisplayChange(const int index) {
    mChartWidget->setDisplayType(static_cast<ChartDisplay::DisplayType>(index));
     mChartWidget->setMetaItem(mSelectedName);
}

void MetadataDisplay::onAntialiasing(const bool checked) {
    mChartWidget->setRenderHint(QPainter::Antialiasing, checked);
}

void MetadataDisplay::setMetaItem(const MapItemPtr& selectedName) {
     mChartWidget->setMetaItem(selectedName);
     mSelectedName = selectedName;
}
