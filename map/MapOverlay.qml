import QtQuick
import QtQuick.Window
import QtLocation
import QtPositioning
import QtQuick.Controls

Rectangle {
    property alias mapZoomLevel: mainMap.zoomLevel
    property alias minZoomLevel: mainMap.minimumZoomLevel
    property alias maxZoomLevel: mainMap.maximumZoomLevel

    // fill the full center widget
    anchors.fill: parent

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: mainMap
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(39.426294, -77.420403) // Frederick, MD
        zoomLevel: 14


        MapItemGroup {
            MapItemView{
               model: mapItemsModel
               delegate: MapItemHistory {}
           }
            MapItemView{
               model: mapItemsModel
               delegate: MapItem {}
           }
        }
    }
}
