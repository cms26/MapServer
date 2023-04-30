#ifndef MAPITEMSMODEL_H
#define MAPITEMSMODEL_H

#include "mapitemfwd.h"

#include <QAbstractListModel>
#include <QString>

class MapItemsModel : public QAbstractListModel
{
public:
    MapItemsModel();

    enum MarkerRoles{
        positionRole = Qt::UserRole + 1,
        colorRole,
        idRole,
        pathRole,
        descriptionRole
    };
    const static QHash<int, QByteArray> roles;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QJsonArray mapItems() const;

public slots:
    void addMapItem(const QList<MapItemPtr>&);

private slots:
    void coordinateChanged(const QString&);
    void colorChanged(const QString&);
    void descriptionChanged(const QString&);

private:
    int idIndex(const QString&);

    QList<MapItemPtr> mMapItems;
    QMap<QString, int> mKeyIndex;
};

#endif // MAPITEMSMODEL_H
