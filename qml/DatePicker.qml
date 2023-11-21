import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.14

import "./delegate"

Dialog {
    modal: true
    standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

    property int max: 150
    property int column: -1

    property int year: 0
    property int month: 0
    property int day: 0
    property int hour: 0
    property int minute: 0

    property bool updatetable: true

    //property AlarmModel alarmModel

    function formatNumber(number) {
        return number < 10 && number >= 0 ? "0" + number : number.toString()
    }

    function getDayName(year, month, day, locale = Qt.locale())
    {
        var date = new Date(year, month, day);
        return date.toLocaleString(locale,"ddd");
    }
    function formatday(year, month, day) {
        var currentYear = new Date().getFullYear()
        year = year + currentYear;
        var num = day < 10 && day >= 0 ? "0" + day : day.toString();
        var dayname = getDayName(year, month, day)

        return dayname + ' ' + day
    }

    onAccepted: {
            year = yearTumbler.years[yearTumbler.currentIndex]
            month = monthTumbler.currentIndex + 1
            day = dayTumbler.currentIndex + 1

            var date = new Date(year, month, day)

            if(updatetable) {
                headers.setText(column, date.toLocaleDateString(Qt.locale(), Locale.ShortFormat))
                table_model.setDate(date)
            }
    }
    onRejected: close()

    contentItem: RowLayout {


        RowLayout {
            id: datePicker

            Layout.leftMargin: 20

            property alias dayTumbler: dayTumbler
            property alias monthTumbler: monthTumbler
            property alias yearTumbler: yearTumbler

            readonly property var days: [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

            Tumbler {
                id: dayTumbler

                function updateModel() {
                    // Populate the model with days of the month. For example: [0, ..., 30]
                    var previousIndex = dayTumbler.currentIndex
                    var array = []
                    var newDays = datePicker.days[monthTumbler.currentIndex]
                    for (var i = 1; i <= newDays; ++i)
                        array.push(i)
                    dayTumbler.model = array
                    dayTumbler.currentIndex = Math.min(newDays - 1, previousIndex)
                }

                Component.onCompleted: updateModel()

                delegate: TumblerDelegate {
                    text: formatday(yearTumbler.currentItem.myData.modelData, monthTumbler.currentItem.myData.modelData, modelData) //formatNumber(modelData)
                }
            }
            Tumbler {
                id: monthTumbler

                onCurrentIndexChanged: dayTumbler.updateModel()

                model: 12
                delegate: TumblerDelegate {
                    property variant myData: model
                    text: window.locale.standaloneMonthName(modelData, Locale.ShortFormat)
                }
            }
            Tumbler {
                id: yearTumbler
                wrap :false

                // This array is populated with the next three years. For example: [2018, 2019, 2020]
                readonly property var years: (function() {
                    var arrd = []
                    for(var i = 0; i < max; i++)
                        arrd.push(max - 1 - i)
                    var currentYear = new Date().getFullYear()
                    return arrd.map(function(value) { return currentYear - value; })
                })()

                onCurrentIndexChanged: dayTumbler.updateModel()
                currentIndex: max - 1

                model: years
                delegate: TumblerDelegate {
                    property variant myData: model
                    text: formatNumber(modelData)
                }
            }
        }
    }
}
