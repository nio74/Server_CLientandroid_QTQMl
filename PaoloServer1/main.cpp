#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include"backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


//    QQmlApplicationEngine engine;
//    Backend backend;

//    QQmlContext *context = engine.rootContext();
//    context->setContextProperty("backend",&backend);


    qmlRegisterType<Backend>("io.qt.Backend", 1, 0, "Backend");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
