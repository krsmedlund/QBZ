import QtQuick 1.0

Item {
    id: renderprogram
    width:250
    height:100
    property string name

    function setColor(c) { background.color = c; }
    function setName(name) { renderprogram.name = name; }

    Rectangle {

        anchors.fill: parent
        gradient: Gradient {
                 GradientStop { position: 1.0; color: "#101010" }
                 GradientStop { position: 0.0; color: "#202020" }
             }
        border.color: "lightgrey"
        border.width: 1
        radius: 5
        smooth: true

        Rectangle {
            x: 24
            y:1
            id: background
            smooth: true
            border.width: 1

            gradient: Gradient {
                     GradientStop { position: 1.0; color: "#306090" }
                     GradientStop { position: 0.0; color: "#6090C0" }
                 }
            width: parent.width - 24 - 24
            height: parent.height - 2

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 11
                font.family: "Lucia Grande"
                color: "white"
                text: renderprogram.name
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
             }
        }
    }

}
