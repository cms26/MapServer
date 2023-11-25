#include "mapitem.h"

#include <QJsonObject>
#include <QJsonArray>

const QString MapItem::MapId = QStringLiteral("id");
const QString MapItem::MapLatitude = QStringLiteral("latitude_deg"); //deg
const QString MapItem::MapLongitude = QStringLiteral("longitude_deg"); // deg
const QString MapItem::MapAltitude = QStringLiteral("altitude_m"); // meters
const QString MapItem::MapTrackTimeUtc = QStringLiteral("time_utc"); // time utc string ISO 8601
const QString MapItem::MapColor = QStringLiteral("color"); // hex string, aka #34ebbd
const QString MapItem::MapHistory = QStringLiteral("location_history");
const QString MapItem::MapDescription = QStringLiteral("description");

void MapItem::fromJson(const QJsonObject& obj) {
    if (!obj.contains(MapId)) {
        mMapId = "Custom-" + QUuid::createUuid().toString(QUuid::WithoutBraces);
    } else {
        mMapId = obj.value(MapId).toString();
    }

    if(obj.contains(MapColor)) {
        mColor = QColor::fromString(obj[MapColor].toString());
    }

    const auto& tracks = obj.value(MapHistory).toArray();
    for (const auto& track: tracks) {
        const auto trackObj = track.toObject();
        QGeoCoordinate trackItem;
        if(trackObj.contains(MapLatitude) && trackObj.contains(MapLongitude)) {
            trackItem.setLatitude(trackObj[MapLatitude].toDouble());
            trackItem.setLongitude(trackObj[MapLongitude].toDouble());
        }
        if(trackObj.contains(MapAltitude)) {
            trackItem.setAltitude(trackObj[MapAltitude].toDouble());
        }

        QGeoPositionInfo position;
        position.setCoordinate(trackItem);

        if(trackObj.contains(MapTrackTimeUtc)) {
            const auto& timeObj = QDateTime::fromString(trackObj[MapTrackTimeUtc].toString(), Qt::ISODate);
            position.setTimestamp(timeObj);
        }

        if(trackItem.isValid()) {
            mLocations.push_back(position);
        }
    }

    if(obj.contains(MapDescription)) {
        mDescription = obj[MapDescription].toString();
    }

}

QJsonObject MapItem::toJson() const {
    QJsonObject obj;
    obj[MapId] = mMapId;
    QJsonArray trackObjs;
    for(const auto& track: mLocations) {
        QJsonObject trackObj;
        trackObj[MapLatitude] = track.coordinate().latitude();
        trackObj[MapLongitude] = track.coordinate().longitude();
        trackObj[MapAltitude] = track.coordinate().altitude();
        trackObjs.append(trackObj);
    }

    if(mColor) {
        obj[MapColor] = mColor.value().name();
    }

    obj[MapHistory] = trackObjs;

    if(mDescription) {
        obj[MapDescription] = mDescription.value();
    }

    return obj;
}

void MapItem::addCoordinates(const QList<QGeoPositionInfo>& data) {
    if(!data.isEmpty()) {
        if(mLimitedCoordinate) {
            mLocations = {data.last()};
        } else {
            mLocations.append(data);
        }
        emit coordinateChanged(mMapId);
    }
}

void MapItem::setColor(const QColor& data) {
    if(mColor != data) {
        mColor = data;
        emit mapItemColorChanged(mMapId);
    }
}

void MapItem::setDescription(const QString& data) {
    if(mDescription != data) {
        mDescription = data;
        emit descriptionChanged(mMapId);
    }
}

void MapItem::mergeItem(const MapItemPtr& otherData) {
    if(otherData->color() && otherData->color()->isValid()) {
        setColor(otherData->color().value());
    }

    if(otherData->description()) {
        setDescription(otherData->description().value());
    }

    if(!otherData->coordinates().isEmpty()) {
        addCoordinates(otherData->coordinates());
    }
}

void MapItem::setSelected(const bool data) {
    if(mSelected != data) {
        mSelected=data;
        emit selectedChanged(mMapId);
    }
}
