import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: root
    property int fontSize: 10
    //property BreezeQuickPalette palette: BreezeQuickPalette
   // property string text: "Type here..."
    property alias text: input.text
    implicitHeight: input.font.pixelSize*2
//    implicitWidth: 196
    Rectangle{
        id: body
        color: "transparent"
        anchors.fill: parent
        border {
            color: palette.plasmaBlue
            width: 2
        }
        TextInput{
            id: input
            color: "#f3f1f1"
            anchors.rightMargin: 2
            anchors.leftMargin: 4
            anchors.bottomMargin: 2
            anchors.topMargin: 2

            anchors {
                fill: parent
            }



        }
    }
}







/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
