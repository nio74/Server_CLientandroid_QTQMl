#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //Pass my c++ to Qml

    //qmlRegisterType<ClientServices>("io.qt.Clienteservices", 1, 0, "Clientservices");


    qmlRegisterType<Backend>("io.qt.Backend", 1, 0, "Backend");
//    Backend backend;

//    QQmlContext *context = engine.rootContext();
//    context->setContextProperty("backend",&backend);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main2.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}


