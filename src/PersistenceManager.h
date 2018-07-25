#ifndef CUPOLA_PERSISTENCEMANAGER_H
#define CUPOLA_PERSISTENCEMANAGER_H

#include <QObject>
#include <QSettings>
#include "RepositoryListModel.h"

class PersistenceManager : public QObject {
Q_OBJECT
public:
    PersistenceManager(QObject *parent = nullptr);

    Q_INVOKABLE void loadRepositoryListModel(RepositoryListModel &model);

    Q_INVOKABLE void saveRepositoryListModel(RepositoryListModel *model);

private:
    QSettings m_settings;
};


#endif //CUPOLA_PERSISTENCEMANAGER_H
