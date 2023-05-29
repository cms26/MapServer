#ifndef MAPITEMSMODEL_H
#define MAPITEMSMODEL_H

#include "mapitemfwd.h"

#include <QAbstractListModel>
#include <QString>

class MapItemsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    const static QColor DefaultColor;

    MapItemsModel();

    enum MarkerRoles{
        positionRole = Qt::UserRole + 1,
        colorRole,
        idRole,
        pathRole,
        descriptionRole,
        selectedRole
    };
    const static QHash<int, QByteArray> roles;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QJsonArray mapItems() const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

signals:
    void onUpdateSelectedItem(const MapItemPtr&);

public slots:
    void addMapItem(const QList<MapItemPtr>&);

private slots:
    void coordinateChanged(const QString&);
    void colorChanged(const QString&);
    void descriptionChanged(const QString&);
    void selectionChanged(const QString&);

private:
    int idIndex(const QString&);
    void updatedSelected(const QString&, const bool);

    QList<MapItemPtr> mMapItems;
    QMap<QString, int> mKeyIndex;
};

#endif // MAPITEMSMODEL_H
