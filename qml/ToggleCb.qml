import QtQuick 2.14
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

CheckBox {
    id: cb
    text: qsTr("CheckBox")
    checked: true

    leftPadding :13
    rightPadding :13
    //clip: false
    background: RoundRect {
        color: "#ffb6c1"
        radius: 30
        topLeftCorner:true
        topRightCorner: true
        bottomLeftCorner: true
        bottomRightCorner: true
    }

    // indicator: Rectangle {
    //     implicitWidth: 26
    //     implicitHeight: 26
    //     x: control.leftPadding
    //     y: parent.height / 2 - height / 2
    //     radius: 3
    //     border.color: control.down ? "#17a81a" : "#21be2b"

    //     Rectangle {
    //         width: 14
    //         height: 14
    //         x: 6
    //         y: 6
    //         radius: 2
    //         color: control.down ? "#17a81a" : "#21be2b"
    //         visible: control.checked
    //     }
    // }

    // contentItem: Text {
    //     text: control.text
    //     font: control.font
    //     opacity: 1.0
    //     color: control.down ? "#17a81a" : "#21be2b"
    //     verticalAlignment: Text.AlignVCenter
    //     leftPadding: control.indicator.width + control.spacing
    // }
}
