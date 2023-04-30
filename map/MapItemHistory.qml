import QtQuick
import QtQuick.Controls
import QtLocation

MapPolyline  {
    id: trackId
    line.width: 3
    line.color: roleColor
    // TODO probably a performance issue at some point - consider appending function for path
    path: rolePath
}

