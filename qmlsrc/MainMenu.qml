import QtQuick 1.0

Item {

    width: 1000
    height: 40

    Rectangle {
        id: bg
        anchors.fill: parent
        gradient:
            Gradient {
                GradientStop { position: 1.0; color: Qt.rgba(0.5, 0.5, 0.5, 0.4) }
                GradientStop { position: 0.0; color: Qt.rgba(0.9, 0.9, 0.9, 0.4) }
            }

        Button {
            y: 5
            x: 5
            id: addComponent
            toggleButton: true
            text: "nodes"
            onClicked: {
                nodeListWindow.visible = !nodeListWindow.visible
            }
        }

        Button {
            y: 5
            x: 105
            id: addInput
            text: "inputs"
            onClicked: {
                inputListWindow.visible = !inputListWindow.visible
            }
        }

        Button {
            y: 5
            x: 205
            id: audio
            text: "audio"
            onClicked: {
                inputListWindow.visible = !inputListWindow.visible
            }
        }

        Button {
            y: 5
            x: 305
            id: settings
            text: "gfx"
            onClicked: {
                inputListWindow.visible = !inputListWindow.visible
            }
        }
    }
}
