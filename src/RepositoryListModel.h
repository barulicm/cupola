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
        ColorRole
    };

    void addRepository(const Repository &repo);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:

    QList<Repository> m_repos;
};


#endif //CUPOLA_REPOBACKEND_H
