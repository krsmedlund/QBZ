import QtQuick 1.0

Item {

    id: outport
    width: 16
    height: 16

    property string name: "Outport #1"
    property string type: "float"
    property string portid: "component.portName"
    property double min: 0.0
    property double max: 1.0

    property bool connected: false

    property variant colors: { "float":"red", "texture":"green" }


    Rectangle {
        smooth:true
        gradient: Gradient {
                 GradientStop { position: 1.0; color: outport.colors[outport.type] }
                 GradientStop { position: 0.0; color: "#404040" }
             }
        anchors.fill: outport
        border.color: "black"
        border.width: 1
        radius: 8

    }

}
