import QtQuick 1.0
import "Components.js" as Network
import "ConfigWindow.js" as Cfg

Item {
    property string nodeName
    property string fileName

    id: nodeList
    width: 97
    height: 750
    MouseArea {
        anchors.fill: parent
        onClicked: grid.currentIndex = -1
    }

    function reset() {
        cfgWin.visible = false
        resWin.visible = false
        nodeList.nodeName = ""
        nodeList.fileName = ""
    }

    function showConfigWindow() {
        cfgWin.addOpt("foo", "use foo", "bool")
        cfgWin.visible = true
    }

    function showResourceWindow(nodeName)
    {
        nodeList.nodeName = nodeName
        resWin.nodeName = nodeName

        resWin.visible = true
        resWin.clear()
        var _resList = mainWindow.getResourceList(nodeName)
        var resList = _resList.split(":")
        for (var i=0; i<resList.length; i++) {
            resWin.addResource(resList[i])
        }
    }

    ResourceWindow {
        visible: false
        height: parent.height - 40
        x:100
        id:resWin
        onResourceSelectDone: {
            nodeList.fileName = name
            nodeList.showConfigWindow()
        }
        onResourceSelectCancel: nodeList.reset()
    }


    ConfigWindow {
        height: parent.height - 40
        x:250
        id: cfgWin
        onCfgDone: {
            var obj = Network.componentContainer.addNode(nodeList.nodeName)
            obj.nodeName = nodeList.nodeName
            obj.name = opts[0]["name"]


            obj.fileName = (nodeList.fileName == "") ? obj.name = opts[0]["name"] : nodeList.fileName;

            console.log("name")
            console.log(obj.name)

            console.log("filename")
            console.log(obj.fileName)

            console.log("nodename")
            console.log(obj.nodeName)

            mainWindow.addComponent(obj.nodeName, obj.fileName)

            nodeList.reset();
        }
        onCfgCancel: nodeList.reset()
    }

    ResourceWindow {}

    GridView {
        id: grid
        anchors.fill: parent
        cellWidth: 97; cellHeight: 62
        model: NodeListData
        delegate: nodeListDelegate
        focus: true
        flickableChildren: MouseArea {
             anchors.fill: parent


             onClicked: grid.currentIndex = -1
        }
        Component.onCompleted: currentIndex = -1

        function onAdd() {
            console.log("added")
        }
    }

    Component {
        id: nodeListDelegate
        Rectangle {
            id :delRect
            height: 61
            width: 97
            border.width: 1
            border.color: "#aaa"
            gradient: Gradient {
                     GradientStop { position: 0.0; color: "#C0C5C5" }
                     GradientStop { position: 1.0; color: "#A0A5A5" }
                 }

            Text {
                y:3
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 11
                text: modelData
                color: "#222"
                style: Text.Raised
                styleColor: "#ddd"
            }

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 5
                source: "Icons/default/" + modelData + ".png"
            }

            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    grid.currentIndex = index
                    //nodeList.showConfigWindow(modelData)
                    nodeList.showResourceWindow(modelData)
                }
            }

            states: [
                State {
                    name: "none"
                    when: (grid.currentIndex == -1)
                },
                State {
                    name: "selected"
                    when: rect.GridView.isCurrentItem
                        PropertyChanges {
                                target: delRect;
                                width: 100;
                                height: 100
                                color: "blue"
                        }
                    }
                ]
            transitions: Transition {
                PropertyAnimation {
                    target: delRect
                    properties: "width, height"
                }
            }
        }
    }


}
