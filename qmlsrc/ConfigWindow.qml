import QtQuick 1.0
import "ConfigWindow.js" as Cfg

Item {

    signal cfgDone (variant opts)

    y: 25;
    id: confWindow
    width:  350
    height: 500
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    visible: false

    function clear() {
        Cfg.cfg.clear()
    }

    function addOpt(name) {
        Cfg.cfg.addOpt(name)
    }

    function show() {
        visible = !visible
        Cfg.cfg.show()
    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
                 GradientStop { position: 1.0; color: "#999" }
                 GradientStop { position: 0.0; color: "#777" }
             }

        Rectangle {
            x:15; y:15
            id: nameInput
            width: 250
            height: 75
            color: "#aaa"

            Text {
                text: "Name"
            }

            TextInput {
                y:25
                x: 15
                color: "white"
                width: 150
                height: 35
                id: textInput
                focus: true
            }
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.bottom
            anchors.verticalCenterOffset: -20
            id: addComponent
            text: "Add"
            onClicked: {
               Cfg.cfg.options["name"] = textInput.text
               parent.visible = !parent.visible
                confWindow.cfgDone(Cfg.cfg.options["name"])
            }

        }

    }
}
