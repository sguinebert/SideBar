QT += core gui widgets
#QT -= gui
QT += core qml quick #quickwidgets
#QT += opengl
#QT += svg
QT += websockets network
QT += sql


#CONFIG += release  # Use release mode, which omits debugging symbols
CONFIG += ltcg     # Use link-time code generation
CONFIG += qtquickcompiler  # Precompile QML into C++
#QMAKE_CXXFLAGS_RELEASE += -s

CONFIG += c++latest

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE = 0x060000 # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Property.cpp \
        main.cpp \
        model/Filter.cpp \
        model/FilterListProxy.cpp \
        model/FiltersList.cpp \
        model/Header.cpp \
        model/HeaderList.cpp \
        model/HeaderListProxy.cpp \
        model/Stock.cpp \
        model/Stocks.cpp \
        model/TableModel.cpp \
        model/TableModelProxy.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    MyType.h \
    Property.h \
    model/DataProvider.h \
    model/Filter.h \
    model/FilterListProxy.h \
    model/FiltersList.h \
    model/Header.h \
    model/HeaderList.h \
    model/HeaderListProxy.h \
    model/Stock.h \
    model/Stocks.h \
    model/TableModel.h \
    model/TableModelProxy.h
