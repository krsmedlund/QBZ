import QtQuick 1.0

Item {
    id: musicChannel
    height: 20
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { id: topGrad; position: 0.0; color: Qt.rgba(1.0, 0.2, 0.85, 0.4) }
            GradientStop { id: bottomGrad; position: 1.0; color: Qt.rgba(0.95, 0.1, 0.55, 0.4) }
        }
        Text {
            x: 5
            y: parent.height/2 - height/2
            font.pointSize: 14
            style: Text.Raised
            styleColor: "#222"
            color: "white"
            text: "Timer"
        }
    }
}
