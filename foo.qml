import QtQuick 1.0
import "qmlsrc"
import "./Canvas"

Rectangle {

    id: page; width:1000; height:1000
    color: "#303030"

    /*
    Image {
        id: bg
        anchors.fill: parent
        smooth: true
        source: "qmlsrc/background.jpg"
    }
    */

    BackgroundCanvas {
        id: drawingBackground
        anchors.fill: parent
    }

    MainMenu {
        width: 1000
        height: 30
    }

    Dial {
        id: dial1
        name: "test dial"
        x: 69; y: 45
        value: 0.1
    }


    DeferredRenderer {
        id: render1
        name: "test renderer"
        objectName: "testRenderer"
    }

    PostProcessor {
        id: hblur
        name: "horizontal blur"
        objectName: "hblur"
    }

    PostProcessor {
        id: vblur
        name: "vertical blur"
        objectName: "vblur"
    }


    ConfigWindow {
        id: confWin
    }

    ListView {
        width: 100; height: 100
        model: NodeList
        delegate: Rectangle {
            height: 25
            width: 100
            Text { text: modelData }
        }
    }
}
