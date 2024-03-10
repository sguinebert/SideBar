#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QQmlContext>
//#include <QQuickStyle>

//#include "TableModel.h"
//#include "Property.h"
#include "MyType.h"

#include "model/TableModelProxy.h"

//#include <QtQml/qqmlextensionplugin.h>
//#include "QWKWidgets/widgetwindowagent.h"
//#include "qwindowkit/src/widgets/widgetwindowagent.h"
//#include <qwindowkit/src/widgets/widgetwindowagent.h>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
   // qputenv("QT_QUICK_CONTROLS_STYLE", "Material");
   //QQuickStyle::setStyle("Material");
   // auto agent = new QWK::WidgetWindowAgent();


   QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    qmlRegisterType<HeaderList>("HeaderList", 1, 0, "HeaderList");
    qmlRegisterType<HeaderListProxy>("HeaderListProxy", 1, 0, "HeaderListProxy");
    qmlRegisterType<FiltersList>("FiltersList", 1, 0, "FiltersList");
    qmlRegisterType<TableModel>("TableModel", 1, 0, "TableModel");
    qmlRegisterType<TableModelProxy>("TableModelProxy", 1, 0, "TableModelProxy");
    qmlRegisterType<Stock>("Study", 1, 0, "Study");

//    qmlRegisterType<Property>       ("App.Class", 0, 1, "Property");
    qmlRegisterUncreatableMetaObject(MetaTypeNamespace::staticMetaObject, "App.Class", 0, 1, "MetaType", "Access to enums & flags only");




    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    auto dataprovider = new DataProvider();

    dataprovider->getStocksSymbols();
    //dataprovider->getStockHistory("ACC", QDateTime::currentDateTime().addDays(-3));

    TableModel tablemodel_(nullptr, app.parent());
    TableModelProxy tablemodelproxy_(app.parent());
    tablemodelproxy_.setSource(&tablemodel_);

    engine.rootContext()->setContextProperty("studymodel", &tablemodel_);
    engine.rootContext()->setContextProperty("studyproxy", &tablemodelproxy_);
    engine.rootContext()->setContextProperty("headerproxy", tablemodel_.headerproxy());


    return app.exec();
}
