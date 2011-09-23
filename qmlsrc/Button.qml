import Qt 4.7

Rectangle {
    id: button

    property alias text: textItem.text
    property alias font: textItem.font

    signal clicked


    width: textItem.width + 40; height: textItem.height + 10
    border.width: 1
    border.color: "white"
    radius: 5
    smooth: true

    gradient: Gradient {
        GradientStop { id: topGrad; position: 1.0; color: "#303030" }
        GradientStop { id: bottomGrad; position: 0.0; color: "#c06090" }
    }

    Text {
        id: textItem
        x: parent.width/2 - width/2; y: parent.height/2 - height/2
        font.pointSize: 11
        font.family: "Lucia Grande"
        color: "white"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: button.clicked()
    }

    states: State {
        name: "pressed"; when: mouseArea.pressed && mouseArea.containsMouse
        PropertyChanges { target: bottomGrad; color: "#70a0d0" }
        PropertyChanges { target: topGrad; color: "#404040" }
        PropertyChanges { target: textItem; x: textItem.x + 1; y: textItem.y + 1; explicit: true }
    }
}
