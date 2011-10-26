import QtQuick 1.0
import "Canvas"
import "Cables.js" as CableCode
Item {
    id: bgc

    property variant currentCable: Cable{ x0: 0; y0: 0; x1: 0; y1: 0}
    property variant isDragging: false
    property variant _currentOutPort;

    Canvas {
        width: 1000
        height:1000
        id: cablesCanvas
        anchors.fill: parent
        color: Qt.rgba(0,0,0,0)
        onPaint: { draw(); }


        function draw() {
            var ctx = getContext();
            ctx.save()
            ctx.clearRect(0, 0, width, height)
            ctx.strokeStyle = "red"
            ctx.lineWidth = 3.0

            if (bgc.isDragging) {
                ctx.beginPath()
                ctx.moveTo(bgc.currentCable.x0, bgc.currentCable.y0)
                ctx.lineTo(bgc.currentCable.x1, bgc.currentCable.y1)
                ctx.stroke()
                ctx.closePath()
            }

            ctx.lineWidth = 5.0
            ctx.strokeStyle = "white"

            CableCode.globalCables.forEach(
                function(cable) {

                    var startPos = cable.start.mapToItem(page, 8, 8)
                    var endPos = cable.end.mapToItem(page, 8, 8)

                    ctx.beginPath()
                    ctx.moveTo(startPos.x, startPos.y)
                    ctx.lineTo(endPos.x, endPos.y)
                    ctx.stroke()
                    ctx.closePath()

                }
            );
            ctx.restore()
        }

        MouseArea {
            id: mousearea
            anchors.fill: parent
            hoverEnabled: true

            function getPortFromCursor(x, y)
            {
                var o = mapToItem(page, x, y);
                var c = page.childAt(o.x, o.y)
                if (c == null) return;

                var portCoord = mapToItem(c, o.x, o.y)
                var port = c.childAt(portCoord.x, portCoord.y)
                if (port == null || port.portid == null) return;

                console.log(port.portid)
                return port
            }

            function endDraw(x, y)
            {
                var port = getPortFromCursor(x, y);

                if (port == null) {
                    console.log("not a port")
                    clearCurrentCable();
                    return;
                }

                if (0 != port.portid.indexOf("IN")) {
                    console.log("cant connect an outport to an outport")
                    return
                }

                if (port.type == _currentOutPort.type) {
                    console.log("connecting")
                    endCable(port, x, y)
                }
            }


            onReleased: {
                if (drawingBackground.isDragging)
                    endDraw(mouse.x, mouse.y)
            }


            onPressed: {
                var port = getPortFromCursor(mouse.x, mouse.y);
                if (port == null || 0 != port.portid.indexOf("OUT")) return;
                drawingBackground.startCable(port, mouse.x, mouse.y)
            }

            onPositionChanged: {
                if (pressedButtons & Qt.LeftButton) {
                    if (drawingBackground.isDragging)
                        updateCable(mouse.x, mouse.y)
                }
            }
        }


    }

    function requestPaint() {
        cablesCanvas.requestPaint();
    }

    function startCable(outPort, x, y) {

        bgc._currentOutPort = outPort
        drawingBackground.isDragging = true;

        bgc.currentCable.x0 = x
        bgc.currentCable.y0 = y
        bgc.currentCable.x1 = x
        bgc.currentCable.y1 = y
    }

    function updateCable(x, y) {
        if (!bgc.isDragging) return;
        bgc.currentCable.x1 = x;
        bgc.currentCable.y1 = y;
        cablesCanvas.requestPaint();
    }

    function clearCurrentCable() {
        bgc.isDragging = false
        bgc.currentCable.x0 = 0
        bgc.currentCable.y0 = 0
        bgc.currentCable.x1 = 0
        bgc.currentCable.y1 = 0
        cablesCanvas.requestPaint();
    }

    function endCable(inPort, x, y) {
        if (!bgc.isDragging) return;

        var outPort = bgc._currentOutPort

        if (inPort.type != outPort.type) {
            clearCurrentCable();
            cablesCanvas.requestPaint();
        }

        CableCode.globalCables.push({
                     start: bgc._currentOutPort,
                     end: inPort
                     })
        bgc.isDragging = false

        clearCurrentCable();
        console.log(mainWindow.bindComponents(inPort.type, outPort.portid, inPort.portid) )
        cablesCanvas.requestPaint();
    }


}
