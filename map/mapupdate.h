#ifndef MAPUPDATE_H
#define MAPUPDATE_H


class MapUpdate
{
public:
    MapUpdate();


private:
    const static QString MapId; // JSON field
    QString mMapId;

    const static QString MapHistory; // JSON field
    const static QString MapLatitude; // JSON field
    const static QString MapLongitude; // JSON field
    const static QString MapAltitude; // JSON field
    const static QString MapTrackTime; // JSON field
    QList<QGeoCoordinate> mLocations; // key is time in secs (utc)

    const static QString MapColor; // JSON field
    QColor mColor;
};

#endif // MAPUPDATE_H
