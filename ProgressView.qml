import QtQuick 2.15
import QtQuick.Controls 2.15


ProgressBar {
    id: root
    property real pos: 0
    property real total: 0

    visible: WordReader.isRuning
    value: pos / total

    Text{
        anchors.centerIn: parent
        text: pos + "/" + total
        font.pixelSize: 12
    }

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 6
        color: "#e6e6e6"
        radius: 3
    }

    contentItem: Item {
        implicitWidth: 200
        implicitHeight: 4

        Rectangle {
            width: root.visualPosition * parent.width
            height: parent.height
            radius: 2
            color: "#17a81a"
        }
    }
}
