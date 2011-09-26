import Qt 4.7

Item {
    id: dial
    width: 80
    height: 100

    property string name : "unnamed dial"
    property real value: 0.0
    property real delta: 0

    property real min: 0.0
    property real max: 10.0
    property real range: 10.0
    property string connectedTo: "Composer.LightRadius"


    Rectangle {
        anchors.fill: parent
        id: backgroundColor
        color: Qt.rgba(dial.value, dial.value, dial.value, 1)

        Image {
            width:80
            height:80
            id: background
            source: "knob002bbas.png"
            anchors.top: parent.top
            MouseArea {
                anchors.fill: parent;
            }
        }
    }

    Rectangle {
        anchors.fill: parent;
        color: Qt.rgba(dial.value, dial.value, dial.value, 0.3)
        Image {
            width:80
            height:80
            id: needle
            smooth: true
            source: "knob002bytterst.png"
            anchors.top: parent.top
            transform: Rotation {
                id: needleRotation
                origin.x: dial.width / 2
                origin.y: (dial.height-20) / 2
                angle: 300 * value
            }
        }
    }
    MouseArea {
        height: 64
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -8

        onPressed: {
            dial.delta = mouse.x
           }
        onPositionChanged: {
            var v = dial.value + (mouse.x - dial.delta) / 100.0;
            dial.delta = mouse.x
            if (v > 0.99) v = 1.0
            if (v < 0.01) v = 0.0
            if (dial.value != v) {
                mainWindow.setPortValue(dial.connectedTo, dial.min + dial.range * v)
            }
            dial.value = v
        }
    }

    OutPort
    {
        id: outport0

        width:16; height:16
        anchors.verticalCenter: dial.bottom
        anchors.verticalCenterOffset: -height/2

        portid: "OUT.Dial.Value"
        name: "value"
        type: "float"
        max: 1.0
        min: 0.0
    }
}
