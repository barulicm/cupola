import QtQuick 2.0
import QtQuick.Controls 2.4

ApplicationWindow
{
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    minimumWidth: 350
    minimumHeight: 250
    color: "#282C34"

    onClosing: {
        persistenceManager.saveRepositoryListModel(repoListModel)
    }

    function refreshAllRepos() {
        for (var i=0; i < repoListModel.rowCount(); i++) {
            var newRepo = gitBackend.updateRepository(repoListModel.get(i))
            repoListModel.replace(i, newRepo)
        }
    }

    Component.onCompleted: {
        refreshAllRepos()
    }

    function promptForUserPass() {
        userpassDialog.open()
    }

    Connections {
        target: gitCredentialsManager
        onPromptForUserPass: {
            return promptForUserPass()
        }
    }

    Rectangle {
        id: rowRect
        height: 50
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#282C34"
        z: 2

        Row {
            id: row
            anchors.fill: parent
            Button {
                id: button
                text: "Refresh"
                onClicked: {
                    refreshAllRepos()
                }
            }
        }
    }

    DropArea {
        id: dropArea;
        z: 1
        anchors.top: rowRect.bottom
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
                repoListModel.createRepository(drop.urls)
                image.visible = false
            }
        }
    }


    Image {
        id: image
        source: "qrc:/images/AddNewRepo.png"
        width: sourceSize.width
        anchors.horizontalCenter: dropArea.horizontalCenter
        anchors.verticalCenter: dropArea.verticalCenter
        visible: repoListModel.rowCount() == 0
    }

    GridView {
        id: gridView
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: rowRect.bottom
        anchors.topMargin: 0
        cellHeight: 90
        cellWidth: 180
        z: 1
        delegate: Item {
            Column {
                Image {
                    width: sourceSize.width
                    source: "qrc:/images/FolderIcon.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Rectangle {
                        width: 20
                        height: 20
                        radius: width*0.5
                        visible: notifications.length > 0
                        color: "red"
                        anchors.right: parent.right
                        anchors.top: parent.top
                    }
                }
                Text {
                    text: name
                    font.bold: true
                    color: "#cccccc"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                spacing: 5
            }
        }
        model: repoListModel
    }

    Dialog {
        id: userpassDialog
        modal: true
        standardButtons: Dialog.Ok
    }
}
