#include "iconloader.h"
#include <QDebug>

// preload to be shared across the app
IconLoader::IconLoader() : mIcons({
    {IconName::ZoomIn, QIcon(QPixmap(":/resources/bootstrap-icons/zoom-in.svg"))},
    {IconName::ZoomOut, QIcon(QPixmap(":/resources/bootstrap-icons/zoom-out.svg"))},
    {IconName::Globe, QIcon(QPixmap(":/resources/bootstrap-icons/globe.svg"))}
    }) {

}

IconLoader::~IconLoader() {

}
