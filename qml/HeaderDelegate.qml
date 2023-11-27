import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: icon
    required property Item dragParent
    property int visualIndex: 0

    property alias text : label.text
    property alias textColor: label.color
    property alias horizontalAlignment: label.horizontalAlignment
//    implicitWidth: 100
//    implicitHeight: 30
    color:"#eec"
    Text {
        id: label
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        rightPadding: 5
        leftPadding: 5
        font.bold: true
    }

    DragHandler {
        id: dragHandler
        yAxis.enabled:false

        onActiveChanged: {
            if (!active) {
                // Drag operation has ended or mouse released
                console.log("Drag operation ended or mouse released");
                studyproxy.invalidate()
                headerproxy.setval()
                //headerproxy.invalidate()
            }
        }
    }

    Drag.active: dragHandler.active
    Drag.source: icon
    Drag.hotSpot.x: 36
    Drag.hotSpot.y: 36

    states: [
        State {
            when: dragHandler.active
            ParentChange {
                target: icon
                parent: icon.dragParent
            }
            AnchorChanges {
                target: icon
                anchors.horizontalCenter: undefined
                anchors.verticalCenter: undefined
            }
        },
        State {
            when: dragHandler.active

            StateChangeScript {
                name: "firstScript"
                script: console.log("entering first state")
            }
        }

    ]


}
