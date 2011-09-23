import Qt 4.7


Rectangle {
    id: page
    width: 640
    height: 480
    color: "lightgray"

    Rectangle {
        id: testBox1
        width:100; height:100
        color: "red"
        anchors.horizontalCenter: page.horizontalCenter

        Text {
            id: testBoxLabel1
            text: "Hello world!"
            y: 30
            anchors.horizontalCenter: testBox1.horizontalCenter
            font.pointSize: 24; font.bold: true
        }
    }

    Rectangle {
        id: testBox2
        width:100; height:100
        color: "blue"
        anchors.horizontalCenter: page.horizontalCenter

        Text {
            id: testBoxLabel2
            text: "Hello world!"
            y: 40
            anchors.horizontalCenter: testBox1.horizontalCenter
            font.pointSize: 24; font.bold: true
        }

    }

}
