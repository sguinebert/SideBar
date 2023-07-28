import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: window

    width: 750
    height: 850
//    height: 1440

    visible: true
    title: 'SideBar'
    color: '#E0E2ED'
    //visibility: "FullScreen"

    //Material.theme: Material.Dark
    //Material.theme: Material.Dark
    //Material.accent: "#4096DD"
    //Material.primary: "#4096DD"

//    header: Rectangle {
//        color:'red'
//        anchors.fill: parent
//    }

    Component.onCompleted: {
        console.log(screenManager.screenCount());
        //screenManager.setScreen(mainWindow,1); // for a second screen
    }

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
//    Rectangle {
//            color:'red'
//            anchors.fill: parent
//        }

    RowLayout {
        anchors.fill: parent
        width: window.width // Set the desired width of the RowLayout
        height: window.height // Set the desired height of the RowLayout

        SideBar {
            id:sidebar
            //anchors.left: window.left;
            //height: window.height
            Layout.fillHeight: true
        }

        Rectangle {
            id:tabrec
            anchors.left: sidebar.right
            Layout.fillHeight: true
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
//                    Frame {
//                        background: Rectangle {
//                            color: "transparent"
//                            border.color: "#21be2b"
//                            radius: 2
//                        }

//                        Label {
//                            text: qsTr("Content goes here!")
//                        }
//                    }
                    GroupBox {
                        id: control2
                        title: qsTr("GroupBox")

                        background: Rectangle {
                            y: control2.topPadding - control2.bottomPadding
                            width: parent.width
                            height: parent.height - control2.topPadding + control2.bottomPadding
                            color: "transparent"
                            border.color: "#21be2b"
                            radius: 2
                        }

                        label: Label {
                            x: control2.leftPadding
                            width: control2.availableWidth
                            text: control2.title
                            color: "#21be2b"
                            elide: Text.ElideRight
                        }

                        Label {
                            text: qsTr("Content goes here!")
                        }
                    }
                    GroupBox {
                        id: control
                        title: qsTr("GroupBox")
                        anchors.centerIn: parent
                        width: 300
                        height: 150

                        background: Rectangle {
                            y: control.topPadding - control.padding
                            width: parent.width
                            height: parent.height - control.topPadding + control.padding
                            color: "transparent"
                            border.color: "#21be2b"
                            radius: 2
                        }

                        label: Rectangle {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottom: parent.top
                            anchors.bottomMargin: -height/2
                            color: "white"                  //set this to the background color
                            width: parent.width * 0.7
                            height: title.font.pixelSize
                            Text {
                                id: title
                                text: qsTr("My Tilte")
                                anchors.centerIn: parent
                                font.pixelSize: 32
                            }
                        }
                    }

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
