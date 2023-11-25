#ifndef MAPITEM_H
#define MAPITEM_H

#include "mapitemfwd.h"

#include <QString>
#include <QGeoPositionInfo>
#include <QColor>
#include <QString>
#include <QObject>

class QJsonObject;

class MapItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool mSelected READ selected WRITE setSelected NOTIFY selectedChanged)
public:
    explicit MapItem(QObject* parent = nullptr): QObject(parent) {}

    void fromJson(const QJsonObject&);
    QJsonObject toJson() const;

    const QGeoPositionInfo& lastCoordinate() const {return mLocations.back();}
    const QString& id() const {return mMapId;}
    const std::optional<QColor>& color() const {return mColor;}
    const QList<QGeoPositionInfo>& coordinates() const {return mLocations;}
    const std::optional<QString>& description() const {return mDescription;}

    void setlimitedCoordinate(bool oneCoordinate) {mLimitedCoordinate = oneCoordinate;}
    void addCoordinates(const QList<QGeoPositionInfo>& data);
    void setId(const QString& data) {mMapId = data;}
    void setColor(const QColor& data);
    void setDescription(const QString&);
    void mergeItem(const MapItemPtr&);

    bool selected() const {return mSelected;}
    void setSelected(const bool selected);

signals:
    void coordinateChanged(const QString&);
    void mapItemColorChanged(const QString&);
    void descriptionChanged(const QString&);
    void selectedChanged(const QString&);

private:

    const static QString MapId; // JSON field
    QString mMapId;

    const static QString MapHistory; // JSON field
    const static QString MapLatitude; // JSON field
    const static QString MapLongitude; // JSON field
    const static QString MapAltitude; // JSON field
    const static QString MapTrackTimeUtc; // JSON field
    QList<QGeoPositionInfo> mLocations;

    const static QString MapColor; // JSON field
    std::optional<QColor> mColor;

    const static QString MapDescription; // JSON field
    std::optional<QString> mDescription;

    bool mLimitedCoordinate{false}; // only keep the last coordinate (item does not move)

    bool mSelected{false};  // if the item has been selected by the operator
};

#endif // MAPITEM_H
