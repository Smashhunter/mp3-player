import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Dialogs
import QtCore
 
ApplicationWindow {
    Material.theme: Material.System
    visible: true
    title: qsTr("Mp3-Player")
    minimumWidth: 620
    minimumHeight: 500
    property string lastFolder: ""
    property bool volumeSliderVisible: false
    property color inversive_theme: Material.theme === Material.Dark ? Material.foreground : Material.backgroundColor
    property bool isLooping: false
    signal folderSelected(string folderPath)

    function refreshPlaylist() {
        playlistModel.clear()
        var tracks = client.getPlaylist()
        for (var i = 0; i < tracks.length; ++i) {
            playlistModel.append(tracks[i])
        }
    }

    Timer {
        interval: 200; running: true; repeat: true
        onTriggered: trackProgressSlider.value = client.getProgress() * 100
    }

    FolderDialog {
        options: FolderDialog.ShowDirsOnly
        id: folderDialog
        currentFolder: lastFolder

        onAccepted: {
            folderSelected(folderDialog.folder)
            lastFolder = folderDialog.currentFolder
            currentFolderLabel.text = qsTr("Current folder: ") + lastFolder.slice(8) // Remove "file:///" from the path for display
            client.loadPlaylist(folderDialog.currentFolder)
            refreshPlaylist()
            coverImage.source = client.getCover()

        }
    }
    menuBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            
            ToolButton {
                text: qsTr("Open folder")
                onClicked: folderDialog.open()
            }
            Label {
                id: currentFolderLabel
                text: qsTr("Current folder: ") + lastFolder
                Layout.alignment: Qt.AlignRight
            }
        }
    }
    RowLayout {
        ListModel{
            id: playlistModel
        }
        anchors.fill: parent
        ListView {
            header: Label {
                text: qsTr("Songs")
                font.pixelSize: 24
                padding: 10
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 150
            model: playlistModel
            delegate: Rectangle {
                width: ListView.view.width
                height: 40
                color: index === client.currentTrackIndex ? "#1e88e5" : "transparent"
                
                Text {
                    text: name
                    font.pixelSize: 16
                    color: "#ffffff"
                    anchors.fill: parent
                    anchors.margins: 10
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        client.playTrackAtIndex(index);
                    }
                }
            }
        }
        MenuSeparator {
            Layout.fillHeight: true
            Layout.preferredWidth: 5
        }
        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            Image {
                id: placeholderImage
                source: Qt.resolvedUrl("../assets/cover-placeholder.jpeg")
                width: 300; height: 300
                Layout.maximumWidth: 300; Layout.maximumHeight: 300
                Layout.minimumWidth: 300; Layout.minimumHeight: 300
                visible: coverImage.status !== Image.Ready
                fillMode: Image.PreserveAspectCrop
                Layout.alignment: Qt.AlignHCenter
            }

            Image {
                id: coverImage
                // source: Qt.resolvedUrl(folderDialog.currentFolder + "/cover.*")
                width: 300; height: 300
                Layout.maximumWidth: 300; Layout.maximumHeight: 300
                Layout.minimumWidth: 300; Layout.minimumHeight: 300
                visible: coverImage.status === Image.Ready
                fillMode: Image.PreserveAspectCrop
                Layout.alignment: Qt.AlignHCenter
            }

            Slider {
                id: trackProgressSlider
                from: 0
                to: 100
                value: client.progress*100
                onMoved: client.seek(value)
                Layout.preferredWidth: 300
                Layout.alignment: Qt.AlignHCenter

            }
            RowLayout {
                Layout.alignment: Qt.AlignHCenter
               
                Button {
                    text: "⏮️"
                    font.pixelSize: 20
                    onClicked: client.previous()
                }
                Button {
                    text: qsTr("▶️")
                    font.pixelSize: 20
                    onClicked: client.play()
                }
                Button {
                    text: qsTr("⏸️")
                    font.pixelSize: 20
                    onClicked: client.pause()
                }
                Button {
                    text: qsTr("⏭️")
                    font.pixelSize: 20
                    onClicked: client.next()
                }
                Button {
                    text: qsTr("🔂️")
                    font.pixelSize: 20
                    background: Rectangle {
                        color: isLooping ? "#1e88e5" : "transparent"
                        border.color: isLooping ? "#1e88e5" : "transparent"
                        radius: 4
                    }
                    onClicked: {
                        client.toggleLooping()
                        isLooping = !isLooping
                    }
                }
                Button {
                    id: volumeButton
                    text: qsTr("🔉")
                    font.pixelSize: 20
                    onClicked: volumePopup.open()
                }
                
            }
            Popup {
                id: volumePopup
                visible: volumeSliderVisible
                padding: 10
                x: volumeButton.x + volumeButton.width / 2 - width / 2
                y: volumeButton.y + height - volumeButton.height - 25
                
                Slider {
                    from: 0
                    to: 100
                    value: 50
                    onMoved: client.setVolume(value/100)
                    orientation: Qt.Vertical
                    height: 150
                }
            }
        }
    }
        
}

