import QtQuick 2.15
import QtQuick.Controls 2.15

Button{
    id: root

    flat:true
    background: Rectangle{

        color: root.pressed ? "#769FCD" : "#B9D7EA"
        radius: 2
        border.width: 1
        border.color: "#D6E6F2"
    }

}
