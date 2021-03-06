import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    id: lvdelegate
    width: parent.width
    height: 30

    MouseArea{
        anchors.fill: parent
        onClicked: lvdelegate.ListView.view.currentIndex = index
    }

    RowLayout{
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        spacing: 8
        Text{
            id: id_lv
            text: name
            color: lvdelegate.ListView.isCurrentItem ? "red" : "black"
            font.pixelSize: lvdelegate.ListView.isCurrentItem ? 22 : 18
            Layout.fillWidth: true
        }
    }
}
