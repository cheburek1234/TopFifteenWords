import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle{
    id: root
    property alias model: listView.model
    property int maxValue: 1
    property int maxCountElements: 1

    property color columnColor: "yellow"
    property color lineColor: "yellow"

    readonly property int bloackNamesHeight: 100
    readonly property int histogramViewRectLeftMargin: 20


    readonly property int countStep: 10

    onMaxValueChanged: {
        if(maxValue % 10 === 0){
            mycanvas.requestPaint();
            mycanvas.update();
        }
    }



    Canvas {
        id: mycanvas
        width: parent.width
        height: parent.height - bloackNamesHeight


        onPaint: {

            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);
            ctx.strokeStyle = lineColor;

            //X
            ctx.beginPath();
            ctx.moveTo(0, height);
            ctx.lineTo(width, height);
            ctx.stroke();

            //Y
            ctx.beginPath();
            ctx.moveTo(histogramViewRectLeftMargin, 0);
            ctx.lineTo(histogramViewRectLeftMargin, height);
            ctx.stroke();

            var stepSize = height /countStep

            for (var j = 1; j < countStep; j++) {

                ctx.beginPath();
                ctx.moveTo(histogramViewRectLeftMargin, stepSize * j);
                ctx.lineTo(width, stepSize * j);
                ctx.stroke();

                ctx.fillText((Math.floor(maxValue / j)).toString(), histogramViewRectLeftMargin - 15, stepSize * j + 2 );
            }

        }


    }

    ListView{
        id: listView
        anchors.fill: parent
        anchors.leftMargin: histogramViewRectLeftMargin
        clip: true
        orientation: ListView.Horizontal

        spacing: 5

        delegate:
            Item{
            id: rootDelegate
            width : (listView.width / maxCountElements) - listView.spacing
            height: listView.height
            ColumnLayout{
                spacing: 0
                anchors.fill: parent
                Item{

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Rectangle{
                        anchors{
                            left: parent.left
                            right: parent.right
                            bottom: parent.bottom
                        }

                        Text{
                            text: model.count
                            anchors.centerIn: parent
                        }

                        color: columnColor
                        height: parent.height * (model.count / maxValue)

                    }
                }

                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: 100
                    Text{
                        id: label
                        text: model.word
                        anchors.centerIn: parent
                        font.pixelSize: 12
                        rotation: -70
                    }
                }

            }

        }

    }

}


