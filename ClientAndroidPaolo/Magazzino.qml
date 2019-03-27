import QtQuick 2.10
import QtQuick.Controls 2.5
import io.qt.Backend 1.0



Item
{
    id: element

    Backend {
        id: backend


        onSendCode: {txtCodice.text = code}


        onSendPCosto:{txtPCosto.text = p_pCosto}

        onSendPPubblico:{txtPPub.text = p_pPubblico}

    }


    Row {
        id: row1
        height: 50
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 3

        Rectangle {
            id: rectangle_Search
            height: 44
            color: "#0e99b2"
            radius: 7
            anchors.top: parent.verticalCenter
            anchors.topMargin: -25
            anchors.left: parent.left

            anchors.right: parent.right


            Text {
                id:lbl_SearchCode
                color: "#0a0808"
                text: qsTr("Codice")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 4
                font.pixelSize: 12
            }

            CustomTextEdit {
                id: c_Txt_codice
                y: 0
                width: 50
                height: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.bottom: parent
                anchors.bottomMargin: 0
                anchors.left: lbl_SearchCode.right
                anchors.leftMargin: 20

            }

            CustomButton {
                id: btnSearchKey
                x: 583
                y: 3
                text: "S"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.top: parent.verticalCenter
                anchors.topMargin: -22
                color: enabled ? this.down ? "#78C37F" : "#87DB8D" : "gray"
                onClicked: {
                    // backend.connectClicked()
                    backend.connectClicked()
                    backend.sendSearch(c_Txt_codice.text,2)

                }
            }

        }
    }
    Row {
        id: row2
        height: 200
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 3
        anchors.top: row1.bottom
        anchors.topMargin: 2

        Rectangle{
            id: rectangle_Articolo
            color: "#0e99b2"
            radius: 18
            anchors.fill: parent



            Label{
                id: lbl_NBusta
                color: "#ebedef"
                text: "N°Busta"
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 10
            }

            CustomTextEdit {
                id: txtCodice
                width: 40
                height: 18
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: lbl_NBusta.right
                anchors.leftMargin: 30
            }

            Label {
                id: lbl_PCosto
                x: 5
                y: -1
                color: "#ebedef"
                text: "Pr. Costo"
                anchors.top: lbl_NBusta.bottom
                anchors.topMargin: 18
                anchors.left: parent.left
                anchors.leftMargin: 5
            }

            CustomTextEdit {
                id: txtPCosto
                y: 8
                width: 40
                height: 18
                anchors.top: txtCodice.bottom
                anchors.topMargin: 10
                anchors.left: lbl_PCosto.right
                anchors.leftMargin: 25
            }

            CustomTextEdit {
                id: txtPPub
                x: -3
                y: -47
                width: 40
                height: 18
                anchors.top: txtPCosto.bottom
                anchors.topMargin: 10
                anchors.left: lbl_PCosto.right
                anchors.leftMargin: 25
            }

            Label {
                id: lbl_pPubblioco
                x: 2
                y: -56
                color: "#ebedef"
                text: "Pr. Pub."
                anchors.top: lbl_PCosto.bottom
                anchors.topMargin: 17
                anchors.left: parent.left
                anchors.leftMargin: 5
            }

            CustomButton {
                id: btnSalva
                x: 0
                color: qsTr("#ffffff")
                text: "SALVA"
                anchors.top: parent.top
                anchors.topMargin: 50
                anchors.right: parent.right
                anchors.rightMargin: 50
                onClicked: {

                }
            }

            CheckBox {
                id: checkBoxPronta
                text: qsTr("Pronta")
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: lbl_pPubblioco.bottom
                anchors.topMargin: 10
            }


        }

    }
}
