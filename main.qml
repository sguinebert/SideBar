import QtQuick 6.4
import QtQuick.Controls 6.4
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12
import Qt.labs.qmlmodels 1.0
import QtCharts 2.6
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

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 10

                        GroupBox {
                            id: control
                            title: qsTr("GroupBox")
                            Layout.fillWidth: true
                            anchors.top: parent.top
                            //width: parent.width
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
                        Component {
                          id: listHeaderComponent

                          Item {
                            id: headerItem
                            width: listView.width;
                            height: 30
                            z:100
                            //Component.onCompleted: rootWindow.listHeaderItem = headerItem
                            Rectangle {
                                width: parent.width
                                //width: 250;
                                height: 30
                                radius: 5
                                color:"red"
                            }
                          }
                        }

                        Component {
                            id: listDelegate
                            Rectangle {
                                width: parent.width
                                //width: 250;
                                height: 50
                                radius: 5
                                color:"yellow"

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        console.log("test : ", index)
                                        stockslist.getData(index);
                                    }
                                }

                                Row {
                                    CheckBox {
                                        anchors.verticalCenter: parent.Center
                                        // contentItem: Text {
                                        //     text: control.text
                                        //     font: control.font
                                        //     opacity: 1.0
                                        //     color: control.down ? "#17a81a" : "#21be2b"
                                        //     verticalAlignment: Text.AlignVCenter
                                        //     leftPadding: control.indicator.width + control.spacing
                                        // }
                                    }

                                    Column {
                                        width: 300
                                        anchors.verticalCenter: parent.verticalCenter
                                        Text {
                                            text: name
                                            width: 290
                                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                                        }
                                        Text { text: symbol
                                            font.pointSize: 5
                                            font.pixelSize: 8
                                        }
                                    }
                                    Text {
                                        text: country
                                        width: 130
                                        anchors.verticalCenter: parent.verticalCenter
                                    }
                                    Text {
                                        text: currency
                                        width: 100
                                        anchors.verticalCenter: parent.verticalCenter
                                    }
                                    Text {
                                        text: industry
                                        width: 400
                                        clip: true
                                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                                        anchors.verticalCenter: parent.verticalCenter
                                    }
                                }
                            }
                        }
                        ListView {
                            id: listView
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            //anchors.top: control.bottom;
                            anchors.margins: 5
                            height: parent.height
                            width:parent.width
                            spacing: 3
                            headerPositioning :ListView.OverlayHeader
                            model: stockslist

                            header: listHeaderComponent
                            delegate: listDelegate
                            focus: true
                            clip: true
                        }
                    }

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
                }
                Item {
                    id: activityTab

                    ChartView {
                        id:chart
                        objectName: "myChart"

                        title: "Line Chart"
                        anchors.fill: parent
                        antialiasing: true

                        Component.onCompleted: {
                            //studymodel.onRowCountChanged.connect(updateAxisRanges)
                        }
                        ValueAxis {
                            id: axisX
                            min: 50
                            max: 500
                            tickCount: 5
                        }
                        DateTimeAxis {
                           id: chartXAxis
                           min: new Date(2024, 1, 1, 0, 0, 0, 0) // 00:00
                           max: new Date(2024, 03, 12, 5, 0, 0, 0) // 05:00
                           format: "dd/MM"
                           tickCount: 6
                           labelsColor: "white"
                           gridVisible: false
                           lineVisible: true
                           titleText: "Date"
                           titleFont.pointSize: 10
                           //rubberBand: ChartView.RectangleRubberBand
                        }

                        ValueAxis {
                            id: axisY
                            min: 120
                            max: 250
                        }

                        // function updateAxisRanges() {
                        //     xAxis.min = /* Your logic to find min X */;
                        //     xAxis.max = /* Your logic to find max X */;
                        //     yAxis.min = /* Your logic to find min Y */;
                        //     yAxis.max = /* Your logic to find max Y */;
                        // }
                        // LineSeries {
                        //     name: "Line"
                        //     XYPoint { x: 0; y: 0 }
                        //     XYPoint { x: 1.1; y: 2.1 }
                        //     XYPoint { x: 1.9; y: 3.3 }
                        //     XYPoint { x: 2.1; y: 2.1 }
                        //     XYPoint { x: 2.9; y: 4.9 }
                        //     XYPoint { x: 3.4; y: 3.0 }
                        //     XYPoint { x: 4.1; y: 3.3 }
                        // }
                        function updateHighlightPoint(highlightX, highlightY) {
                            scatterSeries.clear(); // Remove any existing points
                            scatterSeries.append(highlightX, highlightY); // Add the new point
                        }
                        LineSeries {
                            id:lineSeries
                            name: "My Data"
                            axisX: chartXAxis
                            axisY: axisY
                            VXYModelMapper  {
                                model: studymodel // This is your C++ model
                                xColumn: 12 // Assuming the first column is the X axis
                                yColumn: 16 // Assuming the second column is the Y axis
                                // firstRow: 0   // Start of range for Line 1
                                // rowCount: 5   // Number of rows for Line 1
                            }
                        }
                        // Scatter series for highlighting a point
                        ScatterSeries {
                            id: scatterSeries
                            axisX: chartXAxis
                            axisY: axisY
                            markerShape: ScatterSeries.MarkerShapeCircle // customize the marker shape
                            markerSize: 8 // adjust the size of the marker
                        }

                        Canvas {
                            id: projectionCanvas
                            property var selectedPoint: Qt.point(1, 2)
                            anchors.fill: parent
                            onPaint: {
                                return; // Disable the canvas for now
                                var ctx = getContext("2d");
                                ctx.clearRect(0, 0, width, height);
                                ctx.beginPath();
                                ctx.strokeStyle = "#888";
                                // Assume 'selectedPoint' is the point you're focusing on, mapped to pixel coordinates
                                ctx.moveTo(selectedPoint.x, 0);
                                ctx.lineTo(selectedPoint.x, height);
                                ctx.moveTo(0, height - selectedPoint.y);
                                ctx.lineTo(width, height - selectedPoint.y);
                                ctx.stroke();
                            }
                        }

                        PinchArea{
                            id: pa
                            anchors.fill: parent
                            property real currentPinchScaleX: 1
                            property real currentPinchScaleY: 1
                            property real pinchStartX : 0
                            property real pinchStartY : 0

                            onPinchStarted: {
                                // Pinching has started. Record the initial center of the pinch
                                // so relative motions can be reversed in the pinchUpdated signal
                                // handler
                                pinchStartX = pinch.center.x;
                                pinchStartY = pinch.center.y;
                            }

                            onPinchUpdated: {
                                chart.zoomReset();

                                // Reverse pinch center motion direction
                                var center_x = pinchStartX + (pinchStartX - pinch.center.x);
                                var center_y = pinchStartY + (pinchStartY - pinch.center.y);

                                // Compound pinch.scale with prior pinch scale level and apply
                                // scale in the absolute direction of the pinch gesture
                                var scaleX = currentPinchScaleX * (1 + (pinch.scale - 1) * Math.abs(Math.cos(pinch.angle * Math.PI / 180)));
                                var scaleY = currentPinchScaleY * (1 + (pinch.scale - 1) * Math.abs(Math.sin(pinch.angle * Math.PI / 180)));

                                // Apply scale to zoom levels according to pinch angle
                                var width_zoom = height / scaleX;
                                var height_zoom = width / scaleY;

                                var r = Qt.rect(center_x - width_zoom / 2, center_y - height_zoom / 2, width_zoom, height_zoom);
                                chart.zoomIn(r);
                            }

                            onPinchFinished: {
                                // Pinch finished. Record compounded pinch scale.
                                currentPinchScaleX = currentPinchScaleX * (1 + (pinch.scale - 1) * Math.abs(Math.cos(pinch.angle * Math.PI / 180)));
                                currentPinchScaleY = currentPinchScaleY * (1 + (pinch.scale - 1) * Math.abs(Math.sin(pinch.angle * Math.PI / 180)));
                            }
                            MouseArea {
                                id:mousearea
                                anchors.fill: parent
                                hoverEnabled: true
                                drag.target: dragTarget // dragTarget is the id of the virtual item (the goal is not to really drag it, just use it to move chart)
                                drag.axis: Drag.XAndYAxis
                                //property var selectedPoint: undefined
                                function findNearestDataPoint(point, series) {
                                    var minDistance = Number.MAX_VALUE;
                                    var nearestPoint = null;
                                    for (var i = 0; i < series.count; ++i) {
                                        var dataPoint = series.at(i); // Assuming `at` method exists to get the data point at index `i`
                                        var distance = Math.sqrt(Math.pow(dataPoint.x - point.x, 2) + Math.pow(dataPoint.y - point.y, 2));
                                        if (distance < minDistance) {
                                            minDistance = distance;
                                            nearestPoint = dataPoint;
                                        }
                                    }
                                    return nearestPoint;
                                }
                                onPositionChanged: (mouse) => {
                                                       //console.log( "onPositionChanged: ", mouse.x, mouse.y );
                                                       var point = chart.mapToValue(mouse, lineSeries);
                                                       // Assuming you have a function to find the nearest data point to 'point'
                                                       projectionCanvas.selectedPoint = findNearestDataPoint(point, lineSeries);
                                                       chart.updateHighlightPoint(projectionCanvas.selectedPoint.x, projectionCanvas.selectedPoint.y);
                                                       //console.log("nearest points : ", projectionCanvas.selectedPoint)
                                                       projectionCanvas.requestPaint();
                                                       // Position and show the tooltip
                                                       tooltip.x = mouse.x;
                                                       tooltip.y = mouse.y - tooltip.height - 10; // Adjust as needed
                                                       tooltip.text = "X: " + projectionCanvas.selectedPoint.x + ", Y: " + projectionCanvas.selectedPoint.y;
                                                       tooltip.visible = true;

                                                       chart.updateHighlightPoint(projectionCanvas.selectedPoint.x, projectionCanvas.selectedPoint.y);

                                                   }
                                onWheel: (wheel)=> {
                                             //chart.zoomReset();
                                    let gamma = 0.5;
                                    let cd = (wheel.angleDelta.y / 120);


                                    //chart.zoom(cd)
                                    let scale = 1.0 - cd * 0.2;
                                 if((wheel.x <= chart.plotArea.x + chart.plotArea.width) && (wheel.x >= chart.plotArea.x) && // zoom
                                    (wheel.y <= chart.plotArea.y + chart.plotArea.height) && (wheel.y >= chart.plotArea.y)){
                                     if(wheel.angleDelta.y >= 0) { // wheel
                                         chart.zoomIn(Qt.rect(wheel.x, wheel.y, (chart.plotArea.width*scale), (chart.plotArea.height*scale)));
                                         chart.scrollLeft(wheel.x - chart.plotArea.x);
                                         chart.scrollDown(- wheel.y + chart.plotArea.y);
                                     }
                                     else { // wheel
                                         //console.log(wheel.y, chart.plotArea.y)
                                         chart.zoomIn(Qt.rect(wheel.x, wheel.y, (chart.plotArea.width*scale), (chart.plotArea.height*scale)));
                                         chart.scrollLeft(wheel.x - chart.plotArea.x);
                                         chart.scrollDown(- wheel.y + chart.plotArea.y);
                                     }
                                 }
                                    //chart.zoomIn(rect)
                                    if (wheel.modifiers & Qt.ControlModifier){
                                        if (wheel.angleDelta.y > 0)
                                        {
                                            //chart.scrollRight(5)
                                        }
                                        else
                                        {
                                            //chart.scrollLeft(5)
                                            //chart.zoomIn(Qt.rect(p1.x, p1.y-h, w, h))

                                        }
                                        wheel.accepted=true
                                    }
                                    else{
                                        wheel.accepted=false
                                    }
                                }
                                onExited: {
                                    tooltip.visible = false;
                                }
                            }
                            Item {
                                // A virtual item to receive drag signals from the MouseArea.
                                // When x or y properties are changed by the MouseArea's
                                // drag signals, the ChartView is scrolled accordingly.
                                id: dragTarget

                                property real oldX : x
                                property real oldY : y

                                onXChanged: {
                                    chart.scrollLeft( x - oldX );
                                    oldX = x;
                                }
                                onYChanged: {
                                    chart.scrollUp( y - oldY );
                                    oldY = y;
                                }
                            }
                        }

                        ToolTip {
                            id: tooltip
                            visible: false
                            delay: 0
                            timeout: 1000
                            // Additional styling here...
                        }
                    }
                }
            }
        }
    }


    }//ColumnLayout
}
