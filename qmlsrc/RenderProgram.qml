import QtQuick 1.0


Item {
    id: renderProgram
    width: 150
    height: 100

    property string name

    ConfigWindow {
        id: cfgWin
        onCfgDone: {
            mainWindow.addComponent("RenderProgram", opts)
            renderProgram.name = opts
            renderer.visible = true
        }
    }

    function showConfigWindow() {
        cfgWin.clear()
        cfgWin.addOpt("foo", "use foo", "bool")
        cfgWin.show()
        renderer.visible = false
    }

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
        icon: "default/RenderProgram.png"
        visible: false
        title: "RenderProgram"
    }

    InPort {
        id: inport0
        width: 16; height: 16
        y: 10
        anchors.horizontalCenter: parent.left
        anchors.horizontalCenterOffset: width/2 + 4
        name: "Models"
        type: "model"
        portid: "IN." + parent.name + ".Models"
    }

    OutPort {
        id: outport0
        width: 16; height: 16
        y: 10
        anchors.horizontalCenter: parent.right
        anchors.horizontalCenterOffset: - width/2 - 5
        name: "Render program data"
        type: "renderprogram"
        portid: "OUT." + parent.name + ".RenderProgram"
    }


}
