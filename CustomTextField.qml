import QtQuick 2.15
import QtQuick.Controls 2.15

TextField{
    id: root
    selectByMouse: true
    background: Rectangle {
        implicitHeight: root.height
        implicitWidth: root.width
        border.color: "#B9D7EA"
        border.width: 1
    }
}
