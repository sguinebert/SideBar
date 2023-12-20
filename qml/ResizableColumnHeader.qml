import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12


ListView {
    id:root
    required property var headermodel //proxy model for header
    required property var tablemodel //proxy model for table
    required property var tableview //proxy model for table

    width: tableview.width
    contentWidth: tableview.width
    onColumnWidthChanged: tableview.forceLayout()
    interactive: false

    property var len : [200,200]
    property var count :  headermodel.length()
    property real defaultWidth : 150
    property real minimalWidth : 50
    //property int name: value
    signal  columnWidthChanged
    signal switchColumn(from: int, to: int)

    onSwitchColumn: (from, to) => {
        headermodel.switchColumn(from, to)
    }

    Connections {
        target: tableview  // Set this to the id of tableview
        onContentXChanged: {
            // This will be called whenever tableView's contentX changes
            //console.log('TableView contentXChanged', contentX, horizontalHeader.contentX)
            if(contentX !== tableview.contentX) {
                contentX = tableview.contentX
            }
        }
    }
    onContentXChanged: {
        //console.log('ListView contentXChanged', contentX, tableView.contentX)
        if(tableview.contentX !== contentX) {
            contentX = tableview.contentX
        }
    }
    orientation: ListView.Horizontal
    clip: true

    DatePicker {
        id: datepicker
    }

    DateTimePicker {
        id: datetimepicker
    }

    model: DelegateModel { //visual delegate model for header
        id:visualModel
        model: headermodel
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
                    //console.log("drag", header.from, header.to)
                }
                visualModel.items.move((drag.source as HeaderDelegate).visualIndex, header.visualIndex)
            }

            HeaderDelegate {
                id: header
                dragParent: root
                visualIndex: delegateRoot.visualIndex
                property int from
                property int to
                signal columnSwitched


                width: columnWidth // root.len[index] ? root.len[index] : 200
                height:  root.height
                color:"#eec"
                text: "<b>"+title+"</b>"
                filtertext: filter
                filtertype: type

                onColumnSwitched: {
                    //console.log("switched")
                    //tablemodel.updateColumn()
                    dragParent.headermodel.invalidate()
                    dragParent.tablemodel.invalidate()
                }

                onFtextChanged: (newtext) => {
                    console.log("text changed", newtext)
                    filter = newtext
                }

                onDateselected: (date) => {
                    console.log("date selected", date)
                    //headers.setText(column, date.toLocaleDateString(Qt.locale(), Locale.ShortFormat))
                    tablemodel.setDate(date)
                    //filter = date
                }

                onDateRangeSelected: (from, to) => {
                    tablemodel.setDatetimeRange(from, to);
                }

                onFilterChanged:{
                    console.log('onFilterChanged', filtertext, filter)
                    if(filtertext == filter) return;
                    if(filtertext === ""){
                        if(type === 1){
                            tablemodel.clearDateRange()
                        }
                        if(type === 2){
                            tablemodel.clearDatetimeRange()
                        }
                    }

                    filter = filtertext
                    tablemodel.setFilters();
                    tableview.forceLayout();
                    tableview.returnToBounds();
                }

                //                    onXChanged: {
                //                        //console.log('onXChanged : ', delegateRoot.x, filterdelegate.x, header.x)
                //                        if (Drag.active) {
                //                            // Update the corresponding FilterDelegate's position
                //                            filterdelegate.x = header.x - delegateRoot.x;
                //                            //filterdelegate.z = 1.8
                //                        }
                //                    }

                Rectangle {
                    id: resizeHandle
                    color: Qt.darker(parent.color, 1.05)
                    height: parent.subheight
                    width: 10
                    anchors.right: parent.right
                    anchors.top: parent.top
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
