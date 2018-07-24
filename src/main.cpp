#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QtQml>
#include "RepositoryListModel.h"
#include "GitBackend.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  qmlRegisterType<Repository>();
  qRegisterMetaType<Repository>();

  RepositoryListModel repositoryListModel;
  repositoryListModel.addRepository(Repository("wheego_selfdrive", "/home/matt/wheego_selfdrive"));

  GitCredentialsManager gitCredentialsManager;

  GitBackend gitBackend(&gitCredentialsManager);

  QQmlApplicationEngine engine;

  auto rootContext = engine.rootContext();
  rootContext->setContextProperty("repoListModel", &repositoryListModel);
  rootContext->setContextProperty("gitBackend", &gitBackend);
  rootContext->setContextProperty("gitCredentialsManager", &gitCredentialsManager);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return QApplication::exec();
}