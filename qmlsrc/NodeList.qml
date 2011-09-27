import QtQuick 1.0
import "Components.js" as Network
Item {
    id: nodeList
    width: 97
    height: 750
    MouseArea {
        anchors.fill: parent
        onClicked: grid.currentIndex = -1
    }
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
