import QtQuick 2.10
import QtQuick.Controls 2.3

Button {
    id: control

    leftPadding: padding + 10
    topPadding: padding + 5
    rightPadding: padding + 10
    bottomPadding: padding + 5

    property alias color: back.color
    property alias border: back.border

    contentItem: Text {
        text: control.text
        font.pixelSize: 14
        anchors.right: parent.horizontalCenter
        anchors.left: parent.horizontalCenter
        anchors.bottom: parent.verticalCenter
        anchors.top: parent.verticalCenter
        font.family: "Verdana"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

    }

    background: Rectangle {
        id: back
        border.width: 1
        radius: 5
    }



}



/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
