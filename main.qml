import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: window

    width: 750
    height: 850
    visible: true
    title: 'SideBar'
    color: '#E0E2ED'

    //Material.theme: Material.Dark
    //Material.theme: Material.Dark
    //Material.accent: "#4096DD"
    //Material.primary: "#4096DD"

    FontLoader {
        id: sourceSansProFont

        source: 'fonts/SourceSansPro-Regular.ttf'
        //name: 'SourceSansPro'
    }

//    TabBar {
//        id: control
//        height: window.height

//        contentItem: ListView {
//            model: control.contentModel
//            currentIndex: control.currentIndex

//            spacing: control.spacing
//            orientation: ListView.Vertical   // <<-- VERTICAL
//            boundsBehavior: Flickable.StopAtBounds
//            flickableDirection: Flickable.AutoFlickIfNeeded
//            snapMode: ListView.SnapToItem

//            highlightMoveDuration: 0
//            highlightRangeMode: ListView.ApplyRange
//            preferredHighlightBegin: 40
//            preferredHighlightEnd: height - 40
//        }

//        TabButton {
//            text: qsTr("Home")
//        }
//        TabButton {
//            text: qsTr("Discover")
//        }
//        TabButton {
//            text: qsTr("Activity")
//        }
//    }

    RowLayout {
        width: window.width // Set the desired width of the RowLayout
        height: window.height // Set the desired height of the RowLayout

        SideBar {
            id:sidebar
            //anchors.left: window.left;
            height: window.height
        }

        Rectangle {
            id:tabrec
            anchors.left: sidebar.right
            Layout.fillWidth: true // This item will expand to fill the available width
            height: window.height // Set the height of this item to match the RowLayout's height
            width: window.width - sidebar.width
            TabBar {
                id: bar
                width: tabrec.width
                TabButton {
                    text: qsTr("Home")
                }
                TabButton {
                    text: qsTr("Discover")
                }
                TabButton {
                    text: qsTr("Activity")
                }
            }

            StackLayout {
                width: tabrec.width
                height: parent.height - bar.height
                y:bar.height
                currentIndex: bar.currentIndex
                Item {
                    id: homeTab
        //            Rectangle {
        //                anchors.fill: homeTab
        //                color:'red'
        //            }

                }
                Item {
                    id: discoverTab
                }
                Item {
                    id: activityTab
                }
            }
        }
    }
}
