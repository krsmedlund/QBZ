import QtQuick 1.0


Item {

    id: modelFile
    width: 150
    height: 100

    property string name
    property string fileName
    property string nodeName: "ModelFile"

    MouseArea {
        height: 100
        width: parent.width - 48
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        drag.target: parent
        drag.axis: Drag.XandYAxis
        drag.minimumX: 0
        drag.minimumY: 0
        drag.maximumY: page.height - parent.height / 2
        drag.maximumX: page.width - parent.width / 2
        onMousePositionChanged: drawingBackground.requestPaint()
    }

    Renderer {
        id: renderer
        name: parent.name
        width: parent.width
        height: parent.height
        icon: "default/" + parent.nodeName + ".png"
    }

    OutPort {
        id: outport0
        width: 16; height: 16
        y: 10
        anchors.horizontalCenter: parent.right
        anchors.horizontalCenterOffset: - width/2 - 5
        name: "Model data"
        type: "model"
        portid: "OUT." + parent.fileName + ".ModelData"
    }
}
