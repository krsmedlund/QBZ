import QtQuick 1.0
import "Components.js" as Network

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
        x: 169; y: 45
        value: 0.1
    }


    NodeListWindow {
        id: nodeListWindow
        NodeList {
            id: nodeList
        }
    }

    InputListWindow {
        id: inputListWindow
    }
}
