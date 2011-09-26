import QtQuick 1.0

Item {

    width: 1000
    height: 40

    Rectangle {
        id: bg
        anchors.fill: parent
        gradient:
            Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(0.5, 0.25, 0.5, 0.4) }
                GradientStop { position: 1.0; color: Qt.rgba(0.0, 0.0, 0.0, 0.4) }
            }

        Button {
            y: 5
            x: 5
            id: addComponent
            text: "add node"
            onClicked: {
                nodeListWindow.visible = !nodeListWindow.visible
            }
        }

        Button {
            y: 5
            x: 10
            id: addInput
            text: "add input"
            onClicked: {
                inputListWindow.visible = !inputListWindow.visible
            }
        }
    }
}
