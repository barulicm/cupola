#include <iostream>
#include "PersistenceManager.h"

PersistenceManager::PersistenceManager(QObject *parent)
  : QObject(parent),
    m_settings("barulicm","Cupola")
{
}

void PersistenceManager::loadRepositoryListModel(RepositoryListModel &model) {
  model.clear();
  int repoCount = m_settings.beginReadArray("repos");
  for(auto i_repos = 0; i_repos < repoCount; i_repos++) {
    m_settings.setArrayIndex(i_repos);
    Repository repo;
    repo.setName(m_settings.value("name").toString());
    repo.setLocalPath(m_settings.value("localPath").toString());
    int notificationsCount = m_settings.beginReadArray("notifications");
    for(auto i_notifications = 0; i_notifications < notificationsCount; i_notifications++) {
      m_settings.setArrayIndex(i_notifications);
      repo.addNotification(m_settings.value("message").toString());
    }
    m_settings.endArray();
    model.addRepository(repo);
  }
  m_settings.endArray();
}

void PersistenceManager::saveRepositoryListModel(RepositoryListModel *model) {
  auto repoCount = model->rowCount();
  m_settings.beginWriteArray("repos", repoCount);
  for(int i_repo = 0; i_repo < repoCount; i_repo++) {
    m_settings.setArrayIndex(i_repo);
    const auto& repo = model->get(i_repo);
    m_settings.setValue("name", repo.name());
    m_settings.setValue("localPath", repo.localPath());
    m_settings.beginWriteArray("notifications", repo.notifications().size());
    auto i_notifications = 0;
    for(const auto& notification : repo.notifications()) {
      m_settings.setArrayIndex(i_notifications);
      m_settings.setValue("message", notification);
      i_notifications++;
    }
    m_settings.endArray();
  }
  m_settings.endArray();
}
