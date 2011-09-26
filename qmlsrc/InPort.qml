import QtQuick 1.0

Item {

    id: inport
    width: 16
    height: 16

    property string name: "Inport #1"
    property string type: "float"
    property string portid: "IN.Component.PortName"
    property double min: 0.0
    property double max: 1.0
    property variant colors: { "float":"red", "texture":"green", "model":"blue", "renderprogram":"purple" }
    property variant dC


    Rectangle {
        smooth:true
        gradient: Gradient {
                 GradientStop { position: 1.0; color: inport.colors[inport.type] }
                 GradientStop { position: 0.0; color: "#404040" }
             }
        anchors.fill: inport
        border.color: "#888"
        border.width: 1
        radius: 8

    }
}
