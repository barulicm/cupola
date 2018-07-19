#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QtQml>
#include "RepositoryListModel.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  RepositoryListModel repositoryListModel;
  repositoryListModel.addRepository(Repository("Repo1", QColor(255, 0, 0)));

  QQmlApplicationEngine engine;

  auto rootContext = engine.rootContext();
  rootContext->setContextProperty("repoListModel", &repositoryListModel);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return QApplication::exec();
}