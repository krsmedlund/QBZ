import QtQuick 1.0
import "Components.js" as Network
Item {

    id: nodeList
    width: 1000
    height: 100
    x: 10
    MouseArea {
        anchors.fill: parent
        onClicked: grid.currentIndex = -1
    }
    GridView {
        id: grid
        anchors.fill: parent
        cellWidth: 120; cellHeight: 80
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
            height: 75
            width: 75
            border.width: 1
            border.color: "white"
            gradient: Gradient {
                     GradientStop { position: 0.0; color: "#DDF" }
                     GradientStop { position: 1.0; color: "#AAC" }
                 }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 10
                text: modelData
            }

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: "Icons/default/" + modelData + ".png"
            }

            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    Network.componentContainer.addNode(modelData)
                    grid.currentIndex = index
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
