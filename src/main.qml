import QtQuick 2.0
import QtQuick.Controls 1.0

ApplicationWindow
{
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    minimumWidth: 350
    minimumHeight: 250
    color: "#282C34"

    Row {
        id: row
        height: 50
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Button {
            id: button
            text: qsTr("Refresh")
        }
    }


    DropArea {
        id: dropArea;
        z: 1
        anchors.top: row.bottom
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        onEntered: {
            drag.accept(Qt.CopyAction);
        }
        onDropped: {
            if(drop.hasUrls) {
                console.log(drop.urls)
            }
        }
    }


    Image {
        id: image
        source: "qrc:/images/AddNewRepo.png"
        width: sourceSize.width
        anchors.horizontalCenter: dropArea.horizontalCenter
        anchors.verticalCenter: dropArea.verticalCenter
    }

    GridView {
        id: gridView
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: row.bottom
        anchors.topMargin: 0
        cellHeight: 70
        delegate: Item {
            x: 5
            height: 80
            Column {
                Image {
                    width: sourceSize.width
                    source: "qrc:/images/FolderIcon.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Rectangle {
                        width: 20
                        height: 20
                        radius: width*0.5
                        color: statusColor
                        anchors.right: parent.right
                        anchors.top: parent.top
                    }
                }
                Text {
                    x: 5
                    text: name
                    font.bold: true
                    color: "#cccccc"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                spacing: 5
            }
        }
        model: repoListModel
        cellWidth: 70
    }
}
