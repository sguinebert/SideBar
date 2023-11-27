import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
ListView {
    id:root
    property var len : [200,200]
    property var count :  headerproxy.length()
    property real defaultWidth : 150
    property real minimalWidth : 50
    required property var visualmodel
    signal  columnWidthChanged
    signal switchColumn(from: int, to: int)


    orientation: ListView.Horizontal
    clip: true

    model: DelegateModel {
        id:visualModel
        model: visualmodel
        delegate :
        DropArea {
            id: delegateRoot

            width: header.width
            height: header.height


            property int visualIndex: DelegateModel.itemsIndex

            onEntered: function(drag) {
                if((drag.source as HeaderDelegate).visualIndex !== header.visualIndex) {

                    header.from = (drag.source as HeaderDelegate).visualIndex
                    header.to = header.visualIndex
                    switchColumn(header.from, header.to)
                    console.log("drag", header.from, header.to)
                }
                visualModel.items.move((drag.source as HeaderDelegate).visualIndex, header.visualIndex)
//                if(delegateRoot.from !== delegateRoot.to)

            }

            HeaderDelegate {
                id: header
                dragParent: root
                visualIndex: delegateRoot.visualIndex
                property int from
                property int to
                //        width:  root.len[index] ?? defaultWidth // only Qt>= 5.15
                width:  root.len[index] ? root.len[index] : 200
                height:  root.height
                color:"#eec"
                text: "<b>"+title+"</b>"

                Rectangle {
                    id: resizeHandle
                    color: Qt.darker(parent.color, 1.05)
                    height: parent.height
                    width: 10
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    MouseArea {
                        id: mouseHandle
                        anchors.fill: parent
                        drag{ target: parent; axis: Drag.XAxis }
                        hoverEnabled: true
                        cursorShape: Qt.SizeHorCursor
                        onMouseXChanged: {
                            if (drag.active) {
                                var newWidth = header.width + mouseX
                                if (newWidth >= root.minimalWidth) {
                                    header.width = newWidth
                                    root.len[index] = newWidth
                                    root.columnWidthChanged()
                                }
                            }
                        }
                    }
                }
            }
        }
    }

//    delegate: HeaderDelegate {
//        id: header
////        width:  root.len[index] ?? defaultWidth // only Qt>= 5.15
//        width:  root.len[index] ? root.len[index] : defaultWidth
//        height:  root.height
//        color:"#eec"
//        text: "<b>"+modelData+"</b>"
//        Rectangle {
//            id: resizeHandle
//            color: Qt.darker(parent.color, 1.05)
//            height: parent.height
//            width: 10
//            anchors.right: parent.right
//            anchors.verticalCenter: parent.verticalCenter
//            MouseArea {
//                id: mouseHandle
//                anchors.fill: parent
//                drag{ target: parent; axis: Drag.XAxis }
//                hoverEnabled: true
//                cursorShape: Qt.SizeHorCursor
//                onMouseXChanged: {
//                    if (drag.active) {
//                        var newWidth = header.width + mouseX
//                        if (newWidth >= minimalWidth) {
//                            header.width = newWidth
//                            root.len[index] = newWidth
//                            root.columnWidthChanged()
//                        }
//                    }
//                }
//            }
//        }
//    }
    onCountChanged: modelCountChanged()
//    Component.onCompleted: resetColumns()
    displaced: Transition {
        //SequentialAnimation {
        NumberAnimation {
            properties: "x,y";
            easing.type: Easing.OutQuad
        }

            //ScriptAction { script: console.log("ttttttttttttttttt")}
        //}
    }

    function columnWidthProvider(column) {
        return len[column]
    }
    function resetColumns() {
        len=[]
        for (var i=0; i<count; i++) len.push(defaultWidth)
    }
    function modelCountChanged() {
        resetColumns()
        root.columnWidthChanged()
    }
}
