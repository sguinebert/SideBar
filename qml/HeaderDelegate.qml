import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Rectangle {
    id: headerdelegate
    required property Item dragParent //Listview root
    property int visualIndex: 0
    property int subheight: label.height

    property alias text : label.text
    property alias textColor: label.color
    property alias horizontalAlignment: label.horizontalAlignment
    //    implicitWidth: 100
    //    implicitHeight: 30
    property alias filtertext : filterdelegate.text
    property alias filtertype : filterdelegate.type

    ColumnLayout {
        id: headerlayout
        spacing: 1
        height: headerdelegate.height

        Rectangle {
            color:"#eec"
            Layout.preferredWidth: headerdelegate.width
            Layout.preferredHeight: headerdelegate.height * 0.5
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                id: label
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                rightPadding: 5
                leftPadding: 5
                font.bold: true
            }
        }

        FilterDelegate {
            id:filterdelegate
            visible: true

            //text: filter
            Layout.preferredHeight: headerdelegate.height * 0.5
            Layout.preferredWidth: headerdelegate.width

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
        }
    }

    DragHandler {
        id: dragHandler
        yAxis.enabled:false

        onActiveChanged: {
            if (!active) { // Drag operation has ended or mouse released
                //console.log("Drag operation ended or mouse released");

                columnSwitched()
                //studyproxy.updateColumn()
                //headerproxy.invalidate()
            }
        }
    }

    Drag.active: dragHandler.active
    Drag.source: headerdelegate
    Drag.hotSpot.x: 36
    Drag.hotSpot.y: 36

    states: [
        State {
            when: dragHandler.active
            ParentChange {
                target: headerdelegate
                parent: headerdelegate.dragParent
            }
            AnchorChanges {
                target: headerdelegate
                anchors.horizontalCenter: undefined
                anchors.verticalCenter: undefined
            }
        }
    ]


}
