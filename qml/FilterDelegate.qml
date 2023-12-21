import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12


TextField {
    id:filteredit
    signal cleared
    signal dateselected(var date)
    signal dateRangeSelected(var datebottom, var datetop, var rangetext)

    required property int type
    Layout.fillWidth: true
    Layout.fillHeight: false
    topPadding: 0
    bottomPadding: 0
    rightPadding: 5
    clip: true

    Layout.alignment: Qt.AlignBottom

    MouseArea {
        id:textfieldmouse
        anchors.fill: parent
        propagateComposedEvents: true
        acceptedButtons: Qt.LeftButton
        cursorShape: Qt.IBeamCursor
        preventStealing :true
        property int min:0
        property int max:0
        //acceptedButtons: Qt.NoButton
        //cursorShape: Qt.PointingHandCursor
        onPositionChanged : {
            if(pressed){
                if(filteredit.positionAt(mouseX, mouseY) > min)
                    max = filteredit.positionAt(mouseX, mouseY);
                else
                    min = filteredit.positionAt(mouseX, mouseY);
                filteredit.select(min, max);
            }
        }
        onPressed:{
            min = filteredit.positionAt(mouseX, mouseY);
            max = min;
            filteredit.moveCursorSelection(min);
            filteredit.deselect();

        }
        onReleased:{
            max = min;
        }
        onClicked: function(mouse) {

            //mouse.accepted = false
            var type = filteredit.type //table_model.checktype(index)
            if(!type)
                filteredit.forceActiveFocus()
            else if (type === 1){
                datepicker.filterid = filteredit
                datepicker.column = index;
                var globalCoordinates = filteredit.mapToItem(window.contentItem, 0, 0)
                datepicker.x = globalCoordinates.x
                datepicker.y = globalCoordinates.y
                datepicker.open();
            }
            else if (type === 2){
                datetimepicker.filterid = filteredit
                datetimepicker.column = index;
                var globalCoordinates = filteredit.mapToItem(window.contentItem, 0, 0)
                //console.log("filteredit : ", globalCoordinates.x, globalCoordinates.y)
                datetimepicker.x = globalCoordinates.x
                datetimepicker.y = globalCoordinates.y

                datetimepicker.open();
            }
        }
        onDoubleClicked:{
            filteredit.selectWord();
        }
    }
    Image {
        anchors { verticalCenter: parent.verticalCenter; right: parent.right; margins: 5 }
        id: clearText
        fillMode: Image.PreserveAspectFit
        smooth: true;
        visible: filteredit.text
        source: "qrc:/icons/clear.svg"
        height: 10
        width: 10

        MouseArea {
            id: clear
            anchors { horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter }
            height: 10; width: 10
            onClicked: {
                filteredit.text = "";
                filteredit.cleared()
            }
        }
    }

}
