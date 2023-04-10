import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Window {
    width: 740
    height: 580
    visible: true
    title: "Histogram"

    FileDialog{
        id:fileDialog
        onAccepted: textField.text = fileDialog.fileUrl.toString().replace("file:///", "")
    }

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 25

        Label{
            text: "top-15 повторяющихся слов"
        }


        RowLayout{
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            CustomTextField{
                id: textField
                Layout.fillWidth: true
                Layout.preferredHeight: 35
            }
            CustomButton{
                Layout.preferredWidth: 100
                Layout.preferredHeight: 35

                text: "Выбрать файл"
                onClicked: fileDialog.open()
            }
        }



        CustomButton{
            Layout.fillWidth: true
            Layout.preferredHeight: 35

            visible: textField.text.length > 0 && !WordReader.isRuning
            text: "Запустить"
            onClicked: WordReader.runReading(textField.text)
        }


        ProgressView {
            Layout.fillWidth: true
            Layout.preferredHeight: 35

            visible: WordReader.isRuning
            pos: WordReader.pos
            total: WordReader.total
        }


        HistogramView{
            Layout.fillWidth: true
            Layout.fillHeight: true

            maxValue: WordModel.maxWordCount
            maxCountElements: WordModel.limit
            columnColor: "#B9D7EA"
            lineColor: "#769FCD"
            model: WordModel
        }
    }


}
