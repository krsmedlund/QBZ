import QtQuick 1.0

Item {
    id: animation
    width:75
    height:75
    property string name

    Rectangle {
        id: background
        gradient: Gradient {
                 GradientStop { position: 1.0; color: "#603090" }
                 GradientStop { position: 0.0; color: "#b090FF" }
             }
        width: parent.width
        height: parent.height
        border.color: "white"
        border.width: 3
        radius: 5

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 12
            font.family: "Lucia Grande"
            color: "white"
            text: animation.name
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
         }
    }

    MouseArea {
        anchors.fill: parent
        drag.target: parent
        drag.axis: "XandYAxis"
        drag.minimumX: 0
        drag.maximumX: page.width - background.width
        drag.minimumY: 0
        drag.maximumY: page.height - background.height
    }
}
