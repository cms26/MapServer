#include "mapitemsmodel.h"
#include "mapitem.h"
#include "qjsonobject.h"

#include <QJsonArray>

const QColor MapItemsModel::DefaultColor = Qt::red;

const QHash<int, QByteArray> MapItemsModel::roles = {
    {MapItemsModel::positionRole, "rolePosition"},
    {MapItemsModel::colorRole, "roleColor"},
    {MapItemsModel::idRole, "roleId"},
    {MapItemsModel::pathRole, "rolePath"},
    {MapItemsModel::descriptionRole, "roleDescription"},
    {MapItemsModel::selectedRole, "roleSelected"},
};

QVariantList toList(QList<QGeoCoordinate> data) {
    QVariantList list;
    list.reserve(data.size());
    for (const auto& d: data) {
        list.append(QVariant::fromValue(d));
    }
    return list;
}

MapItemsModel::MapItemsModel() {

}

void MapItemsModel::addMapItem(const QList<MapItemPtr>& newItems) {
    for(const auto& newItem: newItems) {
        if(mKeyIndex.contains(newItem->id())) {
            // update data
            mMapItems[mKeyIndex[newItem->id()]]->mergeItem(newItem);
            return;
        }

        qDebug() << "Map item" << newItem->id() << "added to map at" << newItem->coordinates().last();
        // new item
        connect(newItem.get(), &MapItem::coordinateChanged,
                this, &MapItemsModel::coordinateChanged);
        connect(newItem.get(), &MapItem::mapItemColorChanged,
                this, &MapItemsModel::colorChanged);
        connect(newItem.get(), &MapItem::descriptionChanged,
                this, &MapItemsModel::descriptionChanged);
        connect(newItem.get(), &MapItem::selectedChanged,
                this, &MapItemsModel::selectionChanged);

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        mMapItems.append(newItem);
        endInsertRows();

        // track map id with index - not great but works for now
        mKeyIndex[newItem->id()] = rowCount() - 1;
    }
}

int MapItemsModel::rowCount(const QModelIndex& parent) const {
    return mMapItems.count();
}

QVariant MapItemsModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= rowCount()) {
            return QVariant();
    }

    switch(role) {
        case MapItemsModel::positionRole:
            return QVariant::fromValue(mMapItems[index.row()]->lastCoordinate());
        case MapItemsModel::colorRole:
            return QVariant::fromValue(mMapItems[index.row()]->color() ? mMapItems[index.row()]->color().value() : DefaultColor);
        case MapItemsModel::idRole:
            return QVariant::fromValue(mMapItems[index.row()]->id());
        case MapItemsModel::pathRole:
            return toList(mMapItems[index.row()]->coordinates());
        case MapItemsModel::descriptionRole:
            return QVariant::fromValue(mMapItems[index.row()]->description() ? mMapItems[index.row()]->description().value() : "");
        case MapItemsModel::selectedRole:
            return QVariant::fromValue(mMapItems[index.row()]->selected());
        default:
            return QVariant();
    }
}


bool MapItemsModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.row() < 0 || index.row() >= rowCount()) {
            return false;
    }

    switch(role) {
        case MapItemsModel::selectedRole:
            updatedSelected(mMapItems[index.row()]->id(), value.toBool());
    }

    return true;
}

QHash<int, QByteArray> MapItemsModel::roleNames() const {
    return roles;
}

int MapItemsModel::idIndex(const QString& id) {
    auto index = 0;
    for(; index < mMapItems.size(); ++index) {
        if(mMapItems[index]->id() == id) {
            break;
        }
    }
    return index; // return last if index not found
}

void MapItemsModel::coordinateChanged(const QString& id) {
    const auto& index = idIndex(id);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0),
                     {MapItemsModel::pathRole, MapItemsModel::positionRole});
}

void MapItemsModel::colorChanged(const QString& id) {
    const auto& index = idIndex(id);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0),
                     {MapItemsModel::colorRole});
}

void MapItemsModel::descriptionChanged(const QString& id) {
    const auto& index = idIndex(id);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0),
                     {MapItemsModel::descriptionRole});
}

void MapItemsModel::selectionChanged(const QString& id) {
    const auto& index = idIndex(id);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0),
                     {MapItemsModel::selectedRole});
}

QJsonArray MapItemsModel::mapItems() const {
    QJsonArray newData;
    for(const auto& item: mMapItems) {
        newData << item->toJson();
    }
    return newData;
}

void MapItemsModel::updatedSelected(const QString& id, const bool selected) {
    for(const auto& item: mMapItems) {
        const auto& index = idIndex(id);
        const bool selectedState = (item->id() == id) ? selected : false;
        item->setSelected(selectedState);
    }

    const auto& iter = std::find_if(mMapItems.begin(), mMapItems.end(),
                                    [](const auto& item) {return item->selected();});
    if(iter != mMapItems.end()) {
        emit onUpdateSelectedItem(*iter);
        return;
    }

    // didn't find any active - clear out the current display data
    emit onUpdateSelectedItem(nullptr);
}
