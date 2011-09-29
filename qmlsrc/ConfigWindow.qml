import QtQuick 1.0
import "ConfigWindow.js" as Cfg

Item {
    signal cfgDone (variant opts)
    signal cfgCancel

    id: confWindow
    width:  350
    height: 500
    visible: false

    property string nodeName

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
                 GradientStop { position: 0.0; color: "#999" }
                 GradientStop { position: 1.0; color: "#555" }
             }

        Rectangle {
            x:25; y:15
            id: nameInput
            width: 300
            height: 55
            color: "#555"

            Text {
                x:5; y: 3
                color: "#EEE"
                style: Text.Raised;
                styleColor: "#333"
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
               Cfg.cfg.options[0]["name"] = textInput.text
               parent.visible = !parent.visible
               confWindow.cfgDone(Cfg.cfg.options)
            }

        }

        Button {
            anchors.horizontalCenterOffset: 100
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.bottom
            anchors.verticalCenterOffset: -20
            id: cancel
            text: "Cancel"
            onClicked: {
                cfgCancel()
            }

        }
    }
}
