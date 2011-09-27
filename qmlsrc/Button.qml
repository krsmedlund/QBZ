import Qt 4.7

Rectangle {
    id: button

    property alias text: textItem.text
    property alias font: textItem.font
    property bool toggleButton: false
    property bool toggled: false
    signal clicked


    width: textItem.width + 40; height: textItem.height + 15
    border.width: 1
    border.color: "white"
    radius: 5
    smooth: true

    gradient: Gradient {
        GradientStop { id: topGrad; position: 1.0; color: "#555" }
        GradientStop { id: bottomGrad; position: 0.0; color: "#888" }
    }

    Text {
        id: textItem
        x: parent.width/2 - width/2; y: parent.height/2 - height/2
        font.pointSize: 13
        font.family: "Lucia Grande"
        color: "white"
        style: Text.Raised;
        styleColor: "#111"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            if (button.toggleButton) { button.toggled = !button.toggled }
            button.clicked()
        }
    }

    states: [
        State {
            name: "pressed"; when: mouseArea.pressed && mouseArea.containsMouse
            PropertyChanges { target: bottomGrad; color: "#70a0d0" }
            PropertyChanges { target: topGrad; color: "#404040" }
            PropertyChanges { target: textItem; x: textItem.x + 1; y: textItem.y + 1; explicit: true }

        },
        State {
            name: "toggled"; when: button.toggled
            PropertyChanges { target: bottomGrad; color: "#666" }
            PropertyChanges { target: topGrad; color: "#333" }
            PropertyChanges { target: textItem; x: textItem.x + 1; y: textItem.y + 1; explicit: true }

        }]

}
