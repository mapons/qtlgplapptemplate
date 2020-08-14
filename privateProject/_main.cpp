#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "main.h" //MANDATORY: ADD THIS INCLUDE


#include "QtLegal.h" //optional Qt legal widget

//example MACHINE STATUS : REMOVE IT IN YOUR PROJECT
#include "statemachine.h"

#ifdef DEFINED_PUBLIC_LIBS
//test external library
#include <JlCompress.h>

#endif
int _main(int argc, char *argv[]) //rename main to _main
{
    // https://doc.qt.io/qt-5/qdir.html#Q_INIT_RESOURCE
    //If the file name contains characters that cannot be part of a valid C++ function name (such as '-'), they have to be replaced by the underscore character ('_').

    Q_INIT_RESOURCE(privateProject);//FORCE LINK RESOURCES IN STATIC LIBRARY ..."privateProject.qrc"
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //set software data for legal widget
    //app.setApplicationName("My custom app name");
    app.setOrganizationName("My organization");
    app.setOrganizationDomain("myorganization.com");



    QQmlApplicationEngine engine;


    //OPTIONAL:register QML legal component
    QtLegal::instance()->setVersionData("v0.1",BUILD_DATE,":/CHANGELOG.txt");

    //example MACHINE STATUS
    qmlRegisterType<CalculatorStateMachine>("CalculatorStateMachine", 1, 0,
                                            "CalculatorStateMachine");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;



#ifdef DEFINED_PUBLIC_LIBS
    qWarning()<<"TEST EXTERNAL LIBRARY "<<JlCompress::compressFile("text.zip","main.o");
#endif


    return app.exec();
}

