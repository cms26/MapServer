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
        width: roleSelected ? 25 : 20
        height: roleSelected ? 25 : 20
        radius: roleSelected ? 15 : 10
        color: roleColor
        ToolTip.text: roleDescription
        ToolTip.visible: mouseId.containsMouse && roleDescription !== ''
        MouseArea {
            id: mouseId
            anchors.fill: parent
            hoverEnabled: true
            onClicked: () => roleSelected = !roleSelected;
        }
        border.color: roleSelected ? Qt.darker(roleColor)  : 'transparent'
        border.width:  roleSelected ? 5 : 0
    }
}

