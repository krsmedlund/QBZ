import QtQuick 1.0

Item {
    signal resourceSelectDone (string name)
    signal resourceSelectCancel

    id: resWindow
    width:  150
    visible: false

    property string nodeName

    function addResource(name) {
        resModel.append({
            "name": name,
            "file": name,
            "icon": name + ".png"
            })
    }

    function clear() {
        resModel.clear()
    }

    Rectangle {
        id: listContainer

        anchors.fill: parent
        color: "#C0C5C5"

        ListModel {
            id: resModel

            ListElement {
                name: 'dummy'
                file: 'dummy.fak'
                icon: 'dummy.png'
            }
        }

        Component {
            id: resListEntry
            Item {
                id: entryItem
                width: 140
                height: 61
                Row {
                    Text {
                        font.pointSize: 11
                        text: name
                        color: "#222"
                        style: Text.Raised
                        styleColor: "#ddd"
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        listView.currentIndex = index
                        resWindow.resourceSelectDone(name)
                    }
                }
                states: [
                    State {
                        name: "selected"
                        when: listView.isCurrentItem
                            PropertyChanges {
                                Text.color: "white"
                            }
                        }
                    ]
            }
        }

        ListView {
            id: listView
            anchors.fill: parent
            model: resModel
            delegate: resListEntry
            highlight: Rectangle {
                        x:5
                        border.color: "#666"
                        border.width: 1
                        radius: 15
                        smooth: true
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#d0d5d5" }
                            GradientStop { position: 1.0; color: "#b0b5b5" }
                        }
            }
            highlightMoveDuration: 150
            highlightFollowsCurrentItem: true
        }

        Row {
              anchors { left: parent.left; bottom: parent.bottom; margins: 20 }
              Button {
                  text: "close"
                  onClicked: {
                      resourceSelectCancel()
                  }
              }
       }

    }

}
