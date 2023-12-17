import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
ListView {
    id:root
    required property var headermodel //proxy model for header
    required property var tablemodel //proxy model for table
    property var len : [200,200]
    property var count :  headermodel.length()
    property real defaultWidth : 150
    property real minimalWidth : 50
    signal  columnWidthChanged
    signal switchColumn(from: int, to: int)

    onSwitchColumn: (from, to) => {
        headermodel.switchColumn(from, to)
    }

    orientation: ListView.Horizontal
    clip: true

    model: DelegateModel { //visual delegate model for header
        id:visualModel
        model: headermodel
        delegate :
        DropArea {
            id: delegateRoot

            width: headerlayout.width
            height: headerlayout.height


            property int visualIndex: DelegateModel.itemsIndex

            onEntered: function(drag) {
                if((drag.source as HeaderDelegate).visualIndex !== header.visualIndex) {

                    header.from = (drag.source as HeaderDelegate).visualIndex
                    header.to = header.visualIndex
                    switchColumn(header.from, header.to)
                    //console.log("drag", header.from, header.to)
                }
                visualModel.items.move((drag.source as HeaderDelegate).visualIndex, header.visualIndex)
            }

            ColumnLayout {
                id:headerlayout
                spacing: 1
                height: root.height

                HeaderDelegate {
                    id: header
                    dragParent: root
                    visualIndex: delegateRoot.visualIndex
                    property int from
                    property int to
                    signal columnSwitched

                    //width: columnWidth // root.len[index] ? root.len[index] : 200
                    //height:  root.height

                    Layout.preferredWidth: columnWidth
                    Layout.preferredHeight: root.height * 0.5
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    color:"#eec"
                    text: "<b>"+title+"</b>"

                    onColumnSwitched: {
                        //console.log("switched")
                        tablemodel.updateColumn()
                        //tablemodel.invalidate()
                        //headermodel.invalidate()
                    }

                    onXChanged: {
                        //console.log('drag test', Drag.active)
                        if (Drag.active) {
                            // Update the corresponding FilterDelegate's position
                            filterdelegate.x = header.x;
                            filterdelegate.width = header.width;
                            filterdelegate.z = 100
                            //filterdelegate.y = header.y;
                        }
                    }


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
                                //console.log('width : ', headerproxy)
                                if (drag.active) {
                                    var newWidth = header.width + mouseX
                                    if (newWidth >= root.minimalWidth) {
                                        header.width = newWidth
                                        columnWidth = newWidth
                                        root.len[index] = newWidth
                                        root.columnWidthChanged()
                                    }
                                }
                            }
                        }
                    }
                }

                FilterDelegate {
                    id:filterdelegate
                    visible: true

                    text: filter
                    Layout.preferredHeight: root.height * 0.5
                    Layout.preferredWidth: columnWidth

//                    Behavior on x {
//                        NumberAnimation { id: anim; duration: 3000; easing.type: Easing.InBack }
//                        //enabled: false
//                    }

                    onTextChanged:{
                        //table_model.setFilterStr(index, text);
                    }
                    onAccepted:{
                        console.log("accepted")
                        filter = text
                        table_model.setFilters();
                        tableView.forceLayout();
                        tableView.returnToBounds();

                    }

//                    states: [
//                        State {
//                            when: header.Drag.active
//                            ParentChange {
//                                target: filterdelegate
//                                parent: filterdelegate.dragParent
//                            }
//                            AnchorChanges {
//                                target: filterdelegate
//                                anchors.horizontalCenter: undefined
//                                anchors.verticalCenter: undefined
//                            }
//                        }
//                    ]

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
        NumberAnimation {
            target: header
            properties: "x,y";
            easing.type: Easing.OutQuad
        }
    }

    function columnWidthProvider(column) {
        //console.log('columnWidthProvider : ', column, headerproxy.columnWidthProvider(column))
        return headermodel.columnWidthProvider(column);
        //return len[column]
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
