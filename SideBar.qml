import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
//import Qt5Compat.GraphicalEffects

Item {
    id: sideBar

    width: 105
    height: 700
    state: 'close'
    //anchors.centerIn: parent

    property int maxwidth: 200
    property int minwidth: 50
    property int index: -1

    states: [
        State {
            name: 'open'

            PropertyChanges {
                target: sideBar
                width: maxwidth
            }

            PropertyChanges {
                target: timer
                index: 0
            }
        },
        State {
            name: 'close'

            PropertyChanges {
                target: sideBar
                width: minwidth
            }

            PropertyChanges {
                target: timer
                index: 0
            }
        }
    ]

    transitions: [
        Transition {
            from: 'close'
            to: 'open'

            NumberAnimation {
                properties: 'width'
                duration: 300
                easing.type: Easing.OutCubic
            }

            ScriptAction {
                script: {
                    timer.start();
                }
            }
        },
        Transition {
            from: 'open'
            to: 'close'

            SequentialAnimation {

                ScriptAction {
                    script: {
                        timer.start();
                    }
                }

                PauseAnimation {
                    duration: 600
                }

                NumberAnimation {
                    properties: 'width'
                    duration: 300
                    easing.type: Easing.OutCubic
                }
            }
        }
    ]

    Timer {
        id: timer

        property int index: 0

        interval: 10

        onTriggered: {
            if (sideBar.state === 'open')
                columnItems.itemAt(index).state = 'left';
            else
                columnItems.itemAt(index).state = 'middle';

            if (++index != 9)
                timer.start();
        }
    }

    Rectangle {
        id: body

        //radius: 10
        color: '#FFFFFF'
        anchors.fill: parent

        ColumnLayout {
            id: buttonColumn

            width: parent.width
            spacing: 0
            anchors { top: parent.top; topMargin: 0 }

            ListModel {
                id: sideBarModel
                ListElement { name: "Menu"; selected: false }
                ListElement { name: "Search"; selected: false }
                ListElement { name: "Home"; selected: false }
                ListElement { name: "Explore"; selected: false }
                ListElement { name: "Notifications"; selected: false }
                ListElement { name: "Bookmarks"; selected: false }
                ListElement { name: "Messages"; selected: false }
                ListElement { name: "Profile"; selected: false }
                ListElement { name: "Setting"; selected: false }
            }

            Repeater {
                id: columnItems

                model: sideBarModel// ['Menu', 'Search', 'Home', 'Explore', 'Notifications', 'Bookmarks', 'Messages', 'Profile', 'Setting']
                delegate: Rectangle {
                    id: button

                    width: body.width
                    Layout.preferredHeight: 50
                    Layout.fillWidth: true
                    //radius: 10
                    color: buttonMouseArea.containsMouse ? '#f0f0f0' : '#ffffff'
                    //Layout.alignment: Qt.AlignLeft
                    Layout.topMargin: /*model.index === 1 ? 20 :*/ 0
                    state: 'middle'

                    Rectangle {
                        // The colored band
                        id:band
                        visible: model.selected
                        width: 3 // Set the width of the colored band
                        height: parent.height
                        anchors.left: parent.left // Align the right edge with the parent's right edge
                        color: "blue" // Set the color of the band
                    }

                    Behavior on color {
                        ColorAnimation {
                            duration: 200
                        }
                    }

                    states: [
                        State {
                            name: 'left'

                            PropertyChanges {
                                target: button
                                //Layout.leftMargin: 10
                                Layout.preferredWidth: model.index !== 0 ? 240 : 50
                            }

                            PropertyChanges {
                                target: title
                                opacity: 1
                            }
                        },
                        State {
                            name: 'middle'

                            PropertyChanges {
                                target: button
                                Layout.leftMargin: 0// Math.ceil((sideBar.width - 50) / 2)
                                Layout.preferredWidth: 50
                            }

                            PropertyChanges {
                                target: title
                                opacity: 0
                            }
                        }
                    ]

                    transitions: [
                        Transition {
                            from: 'middle'
                            to: 'left'

                            NumberAnimation {
                                properties: 'Layout.leftMargin, Layout.preferredWidth, opacity'
                                duration: 300
                                easing.type: Easing.InOutSine
                            }
                        },
                        Transition {
                            from: 'left'
                            to: 'middle'

                            NumberAnimation {
                                properties: 'Layout.leftMargin, Layout.preferredWidth, opacity'
                                duration: 300
                                easing.type: Easing.InOutSine
                            }
                        }
                    ]

                    MouseArea {
                        id: buttonMouseArea

                        hoverEnabled: true
                        anchors.fill: parent

                        onClicked: {

                            if (model.index === 0) {
                                if (sideBar.state === 'close')
                                    sideBar.state = 'open';
                                else
                                    sideBar.state = 'close';
                            }
                            else if (sidebar.index !== model.index) {
                                model.selected = true
                                sideBarModel.setProperty(sidebar.index, "selected", false)
                                //model[sidebar.index].selected = false
                                sidebar.index = model.index
                            }
                        }
                    }

                    Image {
                        id: icon

                        source: 'icons/' + model.name + '.svg'
                        sourceSize: Qt.size(30, 30)
                        anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
                    }

                    Text {
                        id: title

                        text: model.index === 0 ? '' : model.name
                        font.family: sourceSansProFont.name
                        anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 55 }

                    }
                }
            }
        }
    }

//    DropShadow {
//        id: shadow

//        anchors.fill: body
//        source: body
//        radius: 20
//        samples: radius * 2 + 1
//        color: Qt.rgba(0, 0, 0, 0.05)
//    }
}
