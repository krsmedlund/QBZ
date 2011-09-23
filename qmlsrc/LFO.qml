import QtQuick 1.0

Item {
    id: lfo
    property string name

    Animator {
        id: renderer
        name: parent.name
    }

    OutPort {
        x: 5
        anchors.verticalCenter: renderer.bottom
        anchors.verticalCenterOffset: -height/2
        name: "Value Out"
        type: "float"
        id: outport0
    }
}
