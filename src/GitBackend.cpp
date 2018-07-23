#include <iostream>
#include "GitBackend.h"

GitBackend::GitBackend(QObject *parent)
  : QObject(parent)
{

}

Repository GitBackend::updateRepository(Repository repo) {
  std::cout << repo.name().toStdString() << "\n";
  repo.setName(repo.name() + " UPDATED");
  std::cout << repo.name().toStdString() << "\n";
  return repo;
}
