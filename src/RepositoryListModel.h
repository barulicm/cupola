#ifndef CUPOLA_REPOBACKEND_H
#define CUPOLA_REPOBACKEND_H

#include <QAbstractListModel>
#include "Repository.h"

class RepositoryListModel : public QAbstractListModel {
Q_OBJECT

public:
    explicit RepositoryListModel(QObject *parent = nullptr);

    enum RepositoryRoles {
        NameRole = Qt::UserRole +1,
        NotificationsRole
    };

    void addRepository(const Repository &repo);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE Repository get(int i);

    Q_INVOKABLE void replace(int i, Repository repo);

    Q_INVOKABLE void createRepository(QString localPath);

    Q_INVOKABLE void clear();

protected:
    QHash<int, QByteArray> roleNames() const;

private:

    QList<Repository> m_repos;
};

#endif //CUPOLA_REPOBACKEND_H
