import QtQuick 1.0

Item {

    id: finalOut
    width: 150
    height: 100

    property string name
    property string nodeName: "FinalOut"
    property string fileName: "baxbaz"

    MouseArea {
        height: 100
        width: parent.width - 48
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
        width: parent.width
        height: parent.height
        title: parent.nodeName
        icon: "default/"+ parent.nodeName + ".png"
    }

    InPort {
        id: inport0
        width: 16; height: 16
        y: 10
        anchors.horizontalCenter: parent.left
        anchors.horizontalCenterOffset: width/2 + 4
        name: "Render programs"
        type: "renderprogram"
        portid: "IN.FinalOut.RenderProgram"


    }
}
