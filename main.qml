import QtQuick 6.4
import QtQuick.Controls 6.4
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12
import Qt.labs.qmlmodels 1.0
import "./qml"
import "./qml/delegate"
import "./ribbonbar"


ApplicationWindow {
    id: window

    width: 1600
    height: 850
//    height: 1440

    visible: true
    title: 'SideBar'
    color: '#E0E2ED'
    //visibility: "FullScreen"
    property bool modern_style: RibbonTheme.modern_style

    //Material.theme: Material.Dark
    //Material.theme: Material.Dark
    //Material.accent: "#4096DD"
    //Material.primary: "#4096DD"

//    header: Rectangle {
//        color:'red'
//        anchors.fill: parent
//    }

    Component.onCompleted: {
        //console.log(screenManager.screenCount());
        //screenManager.setScreen(mainWindow,1); // for a second screen
    }

    FontLoader {
        id: sourceSansProFont

        source: 'fonts/SourceSansPro-Regular.ttf'
        //name: 'SourceSansPro'
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0



    // RibbonBottomBar{
    //     id: bottom_bar
    //     anchors{
    //         left: parent.left
    //         right: parent.right
    //         bottom: parent.bottom
    //     }
    //     right_content: RowLayout{
    //         clip: true
    //         spacing:1
    //         Layout.preferredHeight: parent.height
    //         layoutDirection: Qt.RightToLeft
    //         RibbonSlider{
    //             id: page_slider
    //             slide_width: 80
    //             show_filled_color: false
    //             value: 70
    //         }
    //         RibbonButton{
    //             text:"Test Button 3"
    //             show_bg:false
    //             adapt_height:true
    //             icon_source: RibbonIcons.Airplane
    //         }
    //         RibbonButton{
    //             text:"Test Button 4"
    //             show_bg:false
    //             adapt_height:true
    //         }
    //     }
    //     RibbonButton{
    //         text:"Test Button 5"
    //         show_bg:false
    //         adapt_height:true
    //         icon_source: RibbonIcons.AccessTime
    //         checkable: true
    //     }
    //     RibbonButton{
    //         text:"Test Button 6"
    //         show_bg:false
    //         adapt_height:true
    //     }
    //     RibbonButton{
    //         show_bg:false
    //         adapt_height:true
    //         icon_source: RibbonIcons.AppStore
    //         checkable: true
    //         tip_text: "Test Button 7"
    //     }
    // }

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
        Layout.fillWidth: true
        Layout.fillHeight: true // Take up the remaining space

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

                    GroupBox {
                        id: control
                        title: qsTr("GroupBox")
                        anchors.top: parent.top
                        width: parent.width
                        //height: 300
                        anchors.topMargin:boxtitle.height/2

                        background: Rectangle {
                            y: control.topPadding - control.padding
                            width: parent.width
                            height: parent.height - control.topPadding + control.padding
                            color: "transparent"
                            border.color: "#ff0000"
                            radius: 2
                        }

                        ListModel {
                            id: indices
                            ListElement {
                                name: "AEX"
                                checked: false
                            }
                            ListElement {
                                name: "BEL 20"
                                checked: false
                            }
                            ListElement {
                                name: "CAC 40"
                                checked: true
                            }
                            ListElement {
                                name: "DAX"
                                checked: false
                            }
                            ListElement {
                                name: "DOW JONES"
                                checked: false
                            }
                            ListElement {
                                name: "FTSE 100"
                                checked: false
                            }
                            ListElement {
                                name: "IBEX 35"
                                checked: false
                            }
                            ListElement {
                                name: "MDAX"
                                checked: false
                            }
                            ListElement {
                                name: "NASDAQ 100"
                                checked: false
                            }
                            ListElement {
                                name: "OMX Helsinki 15"
                                checked: false
                            }
                            ListElement {
                                name: "OMX Helsinki 25"
                                checked: false
                            }
                            ListElement {
                                name: "OMX Stockholm 30"
                                checked: false
                            }
                            ListElement {
                                name: "S&P 100"
                                checked: false
                            }
                            ListElement {
                                name: "S&P 500"
                                checked: false
                            }
                            ListElement {
                                name: "SDAX"
                                checked: false
                            }
                            ListElement {
                                name: "SMI"
                                checked: false
                            }
                            ListElement {
                                name: "TECDAX"
                                checked: false
                            }
                            ListElement {
                                name: "MOEX"
                                checked: false
                            }
                        }
                        Flow {
                            id:flow
                            anchors.fill: parent

                            Repeater {
                                model:indices
                                delegate: ToggleCb {
                                    text:name
                                }
                            }
                        }



                        // Button {
                        //     id:testButton
                        //     anchors.centerIn: parent
                        //     text: qsTr("Click me!")
                        //     onPressed: {
                        //         console.log("Pressed!");
                        //     }
                        //     onClicked: {
                        //         console.log("Clicked!");
                        //         //studyproxy.switchColumn(6, 4);

                        //     }
                        // }

                        label: Rectangle {
                            id:boxtitle
                            anchors.horizontalCenter: parent.left + width / 2
                            anchors.bottom: parent.top
                            anchors.bottomMargin: -height/2
                            //color: "#21be2b"                  //set this to the background color
                            width: title.width
                            height: title.font.pixelSize

                            Text {
                                id: title
                                text: qsTr("Indices")
                                anchors.centerIn: parent
                                font.pixelSize: 20
                            }
                        }
                    }

                }


                    ResizableColumnHeader {             // COLUMN HEADER
                        id: horizontalHeader
                        Layout.fillWidth: true
                        height: 60
                        defaultWidth: 200
                        spacing: 1
                        headermodel: headerproxy
                        tablemodel: studyproxy
                        tableview: tableView

                        Layout.alignment: Qt.AlignTop

                        //ScrollBar.horizontal: ScrollBar{}
                    }

//                    HorizontalHeaderView {
//                        id: horizontalHeader
//                        anchors.left: tableView.left
//                        anchors.top: parent.top
//                        //syncView: tableView
//                        clip: true
//                        //resizableColumns :true
//                        model: headerproxy

////                        transitions: [
////                            ViewTransition {
////                                item:ViewTransition.Displaced
////                                NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
////                            }
////                        ]

////                        Behavior on x {
////                            NumberAnimation { duration: 300 }
////                        }

//                        delegate : ColumnLayout {
//                            clip: true
//                            Rectangle {
//                                id: headerdelegate
//                                color: "red"
//                                Layout.fillWidth: true
//                                height: 30
//                                implicitWidth: 100



//                                Text {
//                                    id: headertxt
//                                    anchors.fill: parent
//                                    text: model.display

//                                    MouseArea {
//                                        id: headermouse
//                                        anchors.fill: parent

//                                        onClicked: {
//                                            console.log("clicked__ç___")
//                                            model.sortColumn = index
//                                        }
//                                    }
//                                }

//                            }


//                            TextInput {
//                                id: headersearch
//                                height: 30
//                                //width: headertxt.width
//                                Layout.fillWidth: true
//                                clip:true
//                                wrapMode: Text.WordWrap
//                            }
//                        }
//                    }

//                    VerticalHeaderView {
//                        id: verticalHeader
//                        anchors.top: tableView.top
//                        anchors.left: parent.left
//                        syncView: tableView
//                        clip: true
//                    }

                    TableView {
                        id: tableView
                        //anchors.left: verticalHeader.right
                        anchors.left: parent.left
                        anchors.top: horizontalHeader.bottom
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        columnSpacing: 1
                        rowSpacing: 1
                        clip: true
                        columnWidthProvider: horizontalHeader.columnWidthProvider
                        contentWidth:horizontalHeader.contentWidth

                        //resizableColumns :true
                        //onReboundChanged: horizontalHeader.rebound()

                        model: studyproxy

                        delegate: CellText {
                            value: model.display
                            type: model.cellType
                            option: model.cellOption
                            flags: model.cellFlags
                            readOnly: window.interactive ? cellFlags & Class.Property.ReadOnly : true
                        }

                        ScrollBar.horizontal:   ScrollBar { orientation: Qt.Horizontal }
                        ScrollBar.vertical:     ScrollBar { }
                    }
//                    GroupBox {
//                        id: control2
//                        title: qsTr("GroupBox")

//                        background: Rectangle {
//                            y: control2.topPadding - control2.bottomPadding
//                            width: parent.width
//                            height: parent.height - control2.topPadding + control2.bottomPadding
//                            color: "transparent"
//                            border.color: "#21be2b"
//                            radius: 2
//                        }

//                        label: Label {
//                            x: control2.leftPadding
//                            width: control2.availableWidth
//                            text: control2.title
//                            color: "#21be2b"
//                            elide: Text.ElideRight
//                        }

//                        Label {
//                            text: qsTr("Content goes here!")
//                        }
//                    }

                Item {
                    id: discoverTab
                }
                Item {
                    id: activityTab
                }
            }
        }
    }


    }//ColumnLayout
}
