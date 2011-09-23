import QtQuick 1.0

Item {

    id: model

    property string name
    property string mesh
    property string colorTexture
    property string normalTexture
    property string specularTexture

    Rectangle {
        width: 100
        height: 100
    }


    InPort {
        id: inport0
        width: 16; height: 16
        y: 10
        anchors.horizontalCenter: parent.left
        anchors.horizontalCenterOffset: width/2 + 4
        name: "Rotation"
        type: "vec3"
        portid: "IN.Model.Rotation"
    }

    InPort {
        id: inport1
        width: 16; height: 16
        y: 30
        anchors.horizontalCenter: parent.left
        anchors.horizontalCenterOffset: width/2 + 4
        name: "Position"
        type: "vec3"
        portid: "IN.Model.Position"


    }

    InPort {
        id: inport2
        width: 16; height: 16
        y: 50
        anchors.horizontalCenter: parent.left
        anchors.horizontalCenterOffset: width/2 + 4
        name: "Scale"
        type: "vec3"
        portid: "IN.Model.Scale"
    }


}
