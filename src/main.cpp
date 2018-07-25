#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QtQml>
#include "RepositoryListModel.h"
#include "GitBackend.h"
#include "PersistenceManager.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  qmlRegisterType<Repository>();
  qRegisterMetaType<Repository>();
  qmlRegisterType<RepositoryListModel>();

  PersistenceManager persistenceManager;

  RepositoryListModel repositoryListModel;

  persistenceManager.loadRepositoryListModel(repositoryListModel);

  GitCredentialsManager gitCredentialsManager;

  GitBackend gitBackend(&gitCredentialsManager);

  QQmlApplicationEngine engine;

  auto rootContext = engine.rootContext();
  rootContext->setContextProperty("repoListModel", &repositoryListModel);
  rootContext->setContextProperty("gitBackend", &gitBackend);
  rootContext->setContextProperty("gitCredentialsManager", &gitCredentialsManager);
  rootContext->setContextProperty("persistenceManager", &persistenceManager);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return QApplication::exec();
}