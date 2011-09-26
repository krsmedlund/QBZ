import QtQuick 1.0

Item {
    y: 30
    width:  1000
    height: 120
    visible: false
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
                 GradientStop { position: 1.0; color: "#252525" }
                 GradientStop { position: 0.0; color: "#050505" }
             }
    }
}
