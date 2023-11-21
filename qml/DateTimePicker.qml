import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.14

import "./delegate"

Dialog {
    id: dateDialog
    title: "Filter by date and time"
    modal: true
    width: 300
    height: 250
    standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

    header: Item {
        TabBar {
            id: bar
            currentIndex: view.currentIndex
            width: parent.width
            TabButton {
                text: qsTr("Day")
                onClicked: view.setCurrentIndex(TabBar.index)
            }
            TabButton {
                text: qsTr("Range")
                onClicked: view.setCurrentIndex(TabBar.index)
            }
            TabButton {
                text: qsTr("Since")
                onClicked: view.setCurrentIndex(TabBar.index)
            }
        }
    }

    property int column: -1

    function formatNumber(number) {
        return number < 10 && number >= 0 ? "0" + number : number.toString()
    }

    function addDays(date, days) {
      var result = new Date(date);
      result.setDate(result.getDate() + days);
      return result;
    }

    onAccepted: {
        if(view.currentIndex == 0){

            //dpicker
            var bdate = new Date(dpicker.year, dpicker.month, dpicker.day, 0, 0)
            var fdate = new Date(dpicker.year, dpicker.month, dpicker.day, 23, 59, 60)

            console.log(bdate, fdate)

            table_model.setDatetimeRange(bdate, fdate)
            headers.setText(column, bdate.toLocaleDateString(Qt.locale(), Locale.ShortFormat) + ' - ' +  fdate.toLocaleDateString(Qt.locale(), Locale.ShortFormat))

        }
        else if(view.currentIndex == 1){
            if(bottomDate.date && floorDate.date) {
                table_model.setDatetimeRange(bottomDate.date, floorDate.date)
                headers.setText(column, bottomDate.date.toLocaleDateString(Qt.locale(), Locale.ShortFormat) + ' - ' +  floorDate.date.toLocaleDateString(Qt.locale(), Locale.ShortFormat))
            }
            else
            {
                table_model.clearDatetimeRange()
                headers.setText(column, "")
            }
        }
        else if(view.currentIndex == 2){
            //console.log(addDays(sinceDays.date, - sinceDays.text))
            if(sinceDays.text){
                table_model.setDatetimeRange(addDays(sinceDays.date, - sinceDays.text), sinceDays.date)
                headers.setText(column, sinceDays.text)

            }

        }
    }
    onRejected: dateDialog.close()

    contentItem:

        Rectangle {
        //color: "red"
        anchors.fill: parent



        SwipeView {
            id: view
            currentIndex: 1
            anchors.fill: parent
            clip: true

            ColumnLayout {
                TextField {
                    id: oneDate
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    property var date: new Date()
                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            dpicker.open()
                        }
                    }
                }
                DatePicker {
                    id: dpicker
                    updatetable:false

                    onAccepted: {
                        oneDate.text =  new Date(dpicker.year, dpicker.month, dpicker.day).toString()
                    }
                }
            }
            Item {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                Column {
                    id: rowTumbler
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                    TextField {
                        id: bottomDate
                        property var date: new Date()
                        text: 'click'
                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                picker1.open()
                            }
                        }
                        DatetimeDialog {
                            id:picker1
                            //        x: (window.width - width) / 2
                            //        y: (window.height - height) / 2
                            onAccepted: {
                                var date = new Date(picker1.year, picker1.month, picker1.day, picker1.hour, picker1.minute)
                                bottomDate.date = date
                                bottomDate.text = date.toString()
                            }
                        }

                    }
                    TextField {
                        id: floorDate
                        property var date: new Date()
                        text: 'click'

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                picker2.open()
                            }
                        }
                        DatetimeDialog {
                            id:picker2
                            onAccepted: {

                                var date = new Date(picker2.year, picker2.month, picker2.day, picker2.hour, picker2.minute)
                                floorDate.date = date
                                floorDate.text = date.toString()

                            }
                        }
                    }
                } //ColumnLayout
            }
            ColumnLayout {
                TextField {                    
                    id: sinceDays
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    property var date: new Date()
                    validator: IntValidator {bottom: 1; top: 999}
                    placeholderText: 'number of days'
                }
            }
        }//SwipeView
    }
}
