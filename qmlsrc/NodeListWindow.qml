import QtQuick 1.0

Item {
    y: 40
    width: 100
    visible: false
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
                 GradientStop { position: 1.0; color: "#aaa" }
                 GradientStop { position: 0.0; color: "#777" }
             }
        Rectangle {
            x: 98
            height: 750
            width: 1
            color: "#333"
        }
    }

}
