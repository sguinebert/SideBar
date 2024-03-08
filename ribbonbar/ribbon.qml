import QtQuick 2.15
import RibbonUI
import QtQuick.Layouts


RibbonTabBar {
    Layout.fillWidth: true
    Layout.preferredHeight: height

    id: tab_bar
    modern_style: window.modern_style
    bg_opacity: 1.0
    right_tool_bar: RowLayout{
        spacing: 10
        RibbonButton{
            text:"Test Button 1"
            icon_source: RibbonIcons.Alert
            checkable: true
        }
        RibbonButton{
            text:"Test Button 2"
        }
    }

    RibbonTabPage{
        id: basic_page
        title: qsTr("Basic")
        RibbonTabGroup{
            width: slider_layout.width + 20
            text: qsTr("Slider")
            RowLayout{
                id: slider_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 0
                RibbonSlider{
                    Layout.alignment: Qt.AlignVCenter
                    slide_width: 40
                    horizontal: false
                    value: 20
                }
                RibbonSlider{
                    Layout.alignment: Qt.AlignVCenter
                    slide_width: 40
                    horizontal: false
                    show_button: false
                    value: 40
                }
                ColumnLayout{
                    spacing: 0
                    Layout.alignment: Qt.AlignVCenter
                    RibbonSlider{
                        Layout.alignment: Qt.AlignHCenter
                        slide_width: 40
                        value: 60
                    }
                    RibbonSlider{
                        Layout.alignment: Qt.AlignHCenter
                        slide_width: 40
                        show_button: false
                        value: 80
                    }
                }
            }
        }
        RibbonTabGroup{
            width: switch_layout.width + 30
            text: qsTr("Switch Button")
            RowLayout{
                id: switch_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 0
                ColumnLayout{
                    spacing: 5
                    RibbonSwitchButton{
                        text: "Button"
                        grabber_checked_color: "red"
                        checked: true
                    }
                    RibbonSwitchButton{
                        text: "Button"
                        text_on_left: true
                        grabber_checked_color: "orange"
                        checked: true
                    }
                    RibbonSwitchButton{
                        grabber_checked_color: "blue"
                    }
                }
                ColumnLayout{
                    spacing: 5
                    RibbonSwitchButton{
                        text: "Button"
                        show_grabber_text: false
                        grabber_checked_color: "green"
                    }
                    RibbonSwitchButton{
                        text: "Button"
                        show_grabber_text: false
                        text_on_left: true
                        grabber_checked_color: "indigo"
                        checked: true
                    }
                    RibbonSwitchButton{
                        show_grabber_text: false
                        grabber_checked_color: "yellow"
                        checked: true
                    }
                }
            }
        }
        RibbonTabGroup{
            width: checkbox_layout.width + 30
            text: qsTr("CheckBox")
            RowLayout{
                id: checkbox_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 0
                ColumnLayout{
                    spacing: 10
                    RibbonCheckBox{
                        text: "CheckBox"
                        icon_filled_bg_color: "blue"
                        checked: true
                    }
                    RibbonCheckBox{
                        text: "CheckBox"
                        text_on_left: true
                        icon_filled_bg_color: "red"
                    }
                    RowLayout{
                        spacing: 30
                        RibbonCheckBox{
                            icon_filled_bg_color:"orange"
                            tip_text: "CheckBox"
                            show_tooltip: true
                            checked: true
                        }
                        RibbonCheckBox{
                            icon_filled_bg_color:"purple"
                        }
                    }
                }
            }
        }
        RibbonTabGroup{
            width: button_layout.width + 30
            text: qsTr("Button")
            RowLayout{
                id: button_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 1
                ColumnLayout{
                    spacing: 10
                    RibbonButton{
                        text:"Button"
                        icon_source: RibbonIcons.Accessibility
                        checkable: true
                    }
                    RibbonButton{
                        text:"Button"
                    }
                    RibbonButton{
                        text:"Button"
                        show_tooltip: false
                    }
                }
                ColumnLayout{
                    spacing: 10
                    RibbonButton{
                        text:"Button"
                        show_bg:false
                        icon_source: RibbonIcons.Beaker
                        checkable: true
                    }
                    RibbonButton{
                        text:"Button"
                        show_bg:false
                    }
                    RibbonButton{
                        text:"Button"
                        show_bg:false
                        show_tooltip: false
                    }
                }
                ColumnLayout{
                    spacing: 10
                    RibbonButton{
                        show_bg:false
                        icon_source: RibbonIcons.Badge
                        icon_source_filled: RibbonIcons_Filled.Badge
                        checkable: true
                        tip_text: "Button"
                    }
                    RibbonButton{
                        show_bg:false
                        icon_source: RibbonIcons.Clock
                        icon_source_filled: RibbonIcons_Filled.Clock
                        tip_text: "Button"
                    }
                    RibbonButton{
                        show_bg:false
                        icon_source: RibbonIcons.Board
                        icon_source_filled: RibbonIcons_Filled.Board
                        checkable: true
                        tip_text: "Button"
                        show_tooltip: false
                    }
                }
            }
        }
        RibbonTabGroup{
            width: pushbutton_layout.width + 30
            text: qsTr("Push Button")
            RowLayout{
                id: pushbutton_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 10
                RibbonPushButton{
                    text: qsTr("No Menu")
                    icon_source: RibbonIcons.AttachText
                }
                RibbonPushButton{
                    text: qsTr("Menu")
                    icon_source: RibbonIcons.MeetNow
                    Action{
                        text: "Test Item 1"
                    }
                    RibbonMenuSeparator{}
                    Action{
                        text: "Test Item 2"
                        enabled: false
                    }
                }
                RibbonPushButton{
                    text: qsTr("No Menu")
                    icon_source: "qrc:/RibbonUIAPP/resources/imgs/heart.png"
                    icon_size: height-5
                }
                RibbonPushButton{
                    text: qsTr("Menu")
                    icon_source: "qrc:/RibbonUIAPP/resources/imgs/search.png"
                    Action{
                        text: "Test Item 3"
                    }
                    RibbonMenuSeparator{}
                    Action{
                        text: "Test Item 4"
                        enabled: false
                    }
                }
            }
        }
    }
    RibbonTabPage{
        title: qsTr("Input")
        RibbonTabGroup{
            width: lineedit_layout.width + 30
            text: qsTr("Line Edit")
            RowLayout{
                id: lineedit_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 10
                ColumnLayout{
                    spacing: 10
                    Layout.fillHeight: true
                    RibbonLineEdit{
                    }
                    RibbonLineEdit{
                        show_clear_btn:false
                    }
                }
                ColumnLayout{
                    spacing: 10
                    Layout.fillHeight: true
                    RibbonLineEdit{
                        icon_source:RibbonIcons.Search
                    }
                    RibbonLineEdit{
                        icon_source:RibbonIcons.Keyboard
                        show_clear_btn:false
                    }
                }
            }
        }
        RibbonTabGroup{
            width: lineedit_layout.width + 30
            text: qsTr("Text Edit")
            RowLayout{
                id: textedit_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 10
                ColumnLayout{
                    spacing: 30
                    Layout.fillHeight: true
                    RibbonTextEdit{
                        max_height: 50
                    }
                    RibbonTextEdit{
                        max_height: 30
                        show_clear_btn:false
                    }
                }
                ColumnLayout{
                    spacing: 30
                    Layout.fillHeight: true
                    RibbonTextEdit{
                        max_height: 50
                        icon_source:RibbonIcons.Search
                    }
                    RibbonTextEdit{
                        max_height: 30
                        icon_source:RibbonIcons.Keyboard
                        show_clear_btn:false
                    }
                }
            }
        }
        RibbonTabGroup{
            width: combobox_layout.width + 30
            text: qsTr("Combo Box")
            RowLayout{
                id: combobox_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 10
                ColumnLayout{
                    spacing: 10
                    Layout.fillHeight: true
                    RibbonComboBox{
                        model: ListModel {
                            ListElement { text: "Test Item 1" }
                            ListElement { text: "Test Item 2" }
                            ListElement { text: "Test Item 3" }
                        }
                    }
                    RibbonComboBox{
                        editable: true
                        model: ListModel {
                            id: model
                            ListElement { text: "Test Item 1" }
                            ListElement { text: "Test Item 2" }
                            ListElement { text: "Test Item 3" }
                        }
                        onAccepted: {
                            if (find(editText) === -1 && editText)
                                model.append({text: editText})
                        }
                    }
                }
                ColumnLayout{
                    spacing: 10
                    Layout.fillHeight: true
                    RibbonComboBox{
                        model: ListModel {
                            ListElement { text: "Test Item 1" }
                            ListElement { text: "Test Item 2" }
                            ListElement { text: "Test Item 3" }
                        }
                        icon_source: RibbonIcons.Beaker
                    }
                    RibbonComboBox{
                        editable: true
                        model: ListModel {
                            id: model_1
                            ListElement { text: "Test Item 1" }
                            ListElement { text: "Test Item 2" }
                            ListElement { text: "Test Item 3" }
                        }
                        icon_source: RibbonIcons.Calendar
                        onAccepted: {
                            if (find(editText) === -1 && editText)
                                model_1.append({text: editText})
                        }
                    }
                }
            }
        }
        RibbonTabGroup{
            width: spinbox_layout.width + 30
            text: qsTr("Spin Box")
            show_border: false
            RowLayout{
                id: spinbox_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 10
                ColumnLayout{
                    spacing: 10
                    Layout.fillHeight: true
                    RibbonSpinBox{
                        width: 100
                    }
                    RibbonSpinBox{
                        id: spinbox
                        width: 80
                        icon_source: RibbonIcons.DataPie
                        validator: DoubleValidator {
                            bottom: Math.min(spinbox.from, spinbox.to)
                            top:  Math.max(spinbox.from, spinbox.to)
                        }
                        textFromValue: function(value, locale) {
                            return Number(value / 100).toLocaleString(locale, 'f', 2)
                        }
                        valueFromText: function(text, locale) {
                            return Number.fromLocaleString(locale, text) * 100
                        }
                    }
                }
            }
        }
    }
    RibbonTabPage{
        title: qsTr("Others")
        RibbonTabGroup{
            width: text_layout.width + 30
            text: qsTr("Text")
            RowLayout{
                id: text_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 10
                ColumnLayout{
                    spacing: 10
                    Layout.fillHeight: true
                    RibbonText{
                        font.pixelSize: 13
                        text: "Test Text"
                    }
                    RibbonText{
                        font.pixelSize: 13
                        text: "Test Text (Read Only)"
                        view_only: true
                    }
                }
            }
        }
        RibbonTabGroup{
            width: menu_layout.width + 30
            text: qsTr("Menu")
            RowLayout{
                id: menu_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 10
                RibbonButton{
                    text: qsTr("Open Menu")
                    icon_source: RibbonIcons.Open
                    onClicked: menu.popup()
                }
            }
        }
        RibbonTabGroup{
            width: popup_layout.width + 30
            text: qsTr("Popup")
            RowLayout{
                id: popup_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 10
                ColumnLayout{
                    spacing: 10
                    Layout.fillHeight: true
                    RibbonButton{
                        text: qsTr("Open Popup")
                        icon_source: RibbonIcons.Open
                        onClicked: popup.open()
                    }
                    RibbonButton{
                        text: qsTr("Open Popup Dialog (Double Choices)")
                        icon_source: RibbonIcons.Open
                        onClicked: {
                            dialog.buttonFlags = RibbonPopupDialogType.NegativeButton | RibbonPopupDialogType.PositiveButton
                            dialog.open()
                        }
                    }
                    RibbonButton{
                        text: qsTr("Open Popup Dialog (Triple Choices)")
                        icon_source: RibbonIcons.Open
                        onClicked: {
                            dialog.buttonFlags = RibbonPopupDialogType.NegativeButton | RibbonPopupDialogType.PositiveButton | RibbonPopupDialogType.NeutralButton
                            dialog.open()
                        }
                    }
                }
                RibbonPopup{
                    id: popup
                    height: 200
                    width: height
                }
                RibbonPopupDialog{
                    id: dialog
                }
            }
        }
        RibbonTabGroup{
            width: theme_layout.width + 30
            text: qsTr("Theme")
            RowLayout{
                id: theme_layout
                anchors.centerIn: parent
                height: parent.height
                spacing: 10
                RibbonComboBox{
                    id: theme_combo
                    model: ListModel {
                        id: model_theme
                        ListElement { text: "Light" }
                        ListElement { text: "Dark" }
                        ListElement { text: "System" }
                    }
                    icon_source: RibbonIcons.DarkTheme
                    Component.onCompleted: update_state()
                    onActivated: {
                        if (currentText === "System")
                            RibbonTheme.theme_mode = RibbonThemeType.System
                        else if (currentText === "Light")
                            RibbonTheme.theme_mode = RibbonThemeType.Light
                        else
                            RibbonTheme.theme_mode = RibbonThemeType.Dark
                    }
                    Connections{
                        target: RibbonTheme
                        function onTheme_modeChanged(){
                            theme_combo.update_state()
                        }
                    }
                    function update_state(){
                        let str = (RibbonTheme.theme_mode === RibbonThemeType.System ? "System" : RibbonTheme.theme_mode === RibbonThemeType.Light ? "Light" : "Dark")
                        currentIndex = find(str)
                    }
                }
            }
        }
    }
}
