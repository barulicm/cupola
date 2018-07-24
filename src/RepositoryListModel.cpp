#include "RepositoryListModel.h"

RepositoryListModel::RepositoryListModel(QObject *parent) :
        QAbstractListModel(parent)
{

}

QHash<int, QByteArray> RepositoryListModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NameRole] = "name";
  roles[NotificationsRole] = "notifications";
  return roles;
}

void RepositoryListModel::addRepository(const Repository &repo) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_repos << repo;
  endInsertRows();
}

int RepositoryListModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_repos.count();
}

QVariant RepositoryListModel::data(const QModelIndex &index, int role) const {
  if(index.row() < 0 || index.row() >= m_repos.count())
    return QVariant();

  const Repository &repo = m_repos[index.row()];
  if(role == NameRole)
    return repo.name();
  if(role == NotificationsRole)
    return repo.notifications();

  return QVariant();
}

Repository RepositoryListModel::get(int i) {
  return m_repos[i];
}

void RepositoryListModel::replace(int i, Repository repo) {
  m_repos[i] = repo;
  emit dataChanged(createIndex(i,0), createIndex(i,0));
}

void RepositoryListModel::createRepository(QString localPath) {
  auto lastSlashIndex = localPath.lastIndexOf('/');
  auto name = localPath.mid(lastSlashIndex);
  if(localPath.midRef(0,7) == "file://") {
    localPath = localPath.mid(7);
  }
  addRepository(Repository(name,localPath));
}
