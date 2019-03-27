import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ApplicationWindow {


    visible:true

    Rectangle {
        id: rectangle
        color: "#212126"
        anchors.fill: parent
    }


    header: ToolBar {



        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("‹")
                onClicked: stackView.pop()
            }
            Label {
                text: "Title"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                text: qsTr("⋮")
                onClicked: menu.open()
            }
        }
    }

    ListModel {
        id: pageModel
        ListElement {
            title: "Riparazioni"
            page: "Riparazioni.qml"
        }
        ListElement {
            title: "Magazzino"
            page: "Magazzino.qml"
        }
    }
    StackView {
        id: stackView
        anchors.fill: parent
        // Implements back key navigation
        focus: true
//        //Keys.onReleased: if (event.key === Qt.Key_Back && stackView.depth > 1) {
//                             stackView.pop();
//                             event.accepted = true;
//                         }

        initialItem: Item {
            width: parent.width
            height: parent.height
            ListView {
                model: pageModel
                anchors.fill: parent
                delegate: AndroidDelegate {
                    text: title
                    onClicked: stackView.push(Qt.resolvedUrl(page))
                }
            }
        }
    }
    StackView {
        id: stack
        anchors.fill: parent
    }

    Menu {
        id: menu


        MenuItem{
            text: "setup"


        }
    }





}



/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_height:0;anchors_width:0}
}
 ##^##*/
