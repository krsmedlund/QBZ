import QtQuick 1.0

Item {
    width:150
    height:50
    id: postprocessor
    property string name

    MouseArea {
        y:16
        height: 18
        width: parent.width
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
        name: parent.name
        height: 50
        width: 150
    }

    InPort {
        y: 5
        width: 16; height: 16

        anchors.horizontalCenter: parent.left
        anchors.horizontalCenterOffset: 12
        portid: "IN.PostProcess.Texture"
        name: "Texture In"
        type: "texture"
        id: inport0
    }

    InPort {
        y: 25
        width: 16; height: 16
        anchors.horizontalCenter: parent.left
        anchors.horizontalCenterOffset: 12
        portid: "IN.PostProcess.BlurAmount"
        name: "Blur amount"
        type: "float"
        id: inport1
    }

    OutPort {
        y: 5
        width: 16; height: 16
        anchors.horizontalCenter: parent.right
        anchors.horizontalCenterOffset: -12
        portid: "OUT.PostProcess.RenderTexture"
        name: "Texture Out"
        type: "texture"
        id: outport0
    }
}
