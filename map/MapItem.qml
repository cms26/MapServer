import QtQuick
import QtQuick.Controls
import QtLocation

MapQuickItem  {
    id: mapItem
    coordinate: rolePosition
    anchorPoint.x: circleId.width / 2
    anchorPoint.y: circleId.height / 2

    sourceItem: Rectangle {
        id: circleId
        width: 20
        height: 20
        radius: 10.0
        color: roleColor

        ToolTip.text: roleDescription
        ToolTip.visible: mouseId.containsMouse && roleDescription !== ''
        MouseArea {
            id: mouseId
            anchors.fill: parent
            hoverEnabled: true
        }
    }

}

