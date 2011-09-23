import QtQuick 1.0


Item {

    id: defRend
    width: 300
    height: 100

    property string name

    MouseArea {
        height: 100
        width: 264
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        drag.target: parent
        drag.axis: Drag.XandYAxis

        drag.minimumX: 0
        drag.minimumY: 0
        drag.maximumY: page.height - parent.height/2
        drag.maximumX: page.width - parent.width/2

        onMousePositionChanged: drawingBackground.requestPaint()
    }

    Renderer {
        id: renderer
        name: defRend.name
        width: parent.width
        height: parent.height
    }

    InPort {
        id: inport0
        width: 16; height: 16
        y: 10
        anchors.horizontalCenter: parent.left
        anchors.horizontalCenterOffset: width/2 + 4
        name: "Light Radius"
        type: "float"
        portid: "IN.deferredRenderer.LightRadius"


    }

    OutPort {
        id: outport0
        width: 16; height: 16
        y: 10
        anchors.horizontalCenter: parent.right
        anchors.horizontalCenterOffset: - width/2 - 5
        name: "Color Texture"
        type: "texture"
        portid: "OUT.deferredRenderer.ColorTexture"

    }

    OutPort {
        id: outport1
        width: 16; height: 16
        y: 30
        anchors.horizontalCenter: parent.right
        anchors.horizontalCenterOffset: - width/2 - 5
        name: "Normal Texture"
        type: "texture"
        portid: "OUT.DeferredRenderer.NormTexture"

    }

    OutPort {
        id: outport2
        width: 16; height: 16
        y: 50
        anchors.horizontalCenter: parent.right
        anchors.horizontalCenterOffset: - width/2 - 5
        name: "Position Texture"
        type: "texture"
        portid: "OUT.DeferredRenderer.PosTexture"

    }
}
