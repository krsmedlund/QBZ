import QtQuick 1.0

Item {
    id: renderprogram
    width:150
    height:100
    property string name
    property string title
    property string icon

    function setColor(c) { background.color = c; }
    function setName(name) { renderprogram.name = name; }

    Rectangle {

        anchors.fill: parent
        gradient: Gradient {
                 GradientStop { position: 1.0; color: "#333" }
                 GradientStop { position: 0.0; color: "#444" }
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
                     GradientStop { position: 1.0; color: "#505555" }
                     GradientStop { position: 0.0; color: "#707575" }
                 }
            width: parent.width - 24 - 24
            height: parent.height - 2

            Text {
                y:5
                style: Text.Raised
                styleColor: "#222"
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 12
                font.family: "Lucia Grande"
                color: "#DDD"
                text: renderprogram.name
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
             }


            Text {
                y:60
                style: Text.Raised
                styleColor: "#222"
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 11
                font.family: "Lucia Grande"
                color: "#DDD"
                text: renderprogram.title
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
             }

            Image {
                y: 5
                anchors.horizontalCenter: parent.horizontalCenter
                source: "Icons/" + icon
            }
        }
    }

}
