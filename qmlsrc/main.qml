import QtQuick 1.0
import "Components.js" as Network

Rectangle {
    id: page; width:1500; height:750
    color: "#303030"

    Image {
        id: bg
        anchors.fill: parent
        smooth: true
        source: "bg.png"
    }

    BackgroundCanvas {
        id: drawingBackground
        anchors.fill: parent
    }

    MainMenu {
        width: parent.width
    }

    NodeListWindow {
        height: parent.height
        id: nodeListWindow
        NodeList {
            y:1
            x:1
            id: nodeList
        }
    }

    InputListWindow {
        id: inputListWindow
    }

    Dial {
        x: 200
        y: 200
    }
}
