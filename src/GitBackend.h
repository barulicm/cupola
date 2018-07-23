#ifndef CUPOLA_GITBACKEND_H
#define CUPOLA_GITBACKEND_H

#include <QtCore/QObject>
#include <git2.h>
#include "Repository.h"

class GitBackend : public QObject {
Q_OBJECT
public:
    explicit GitBackend(QObject *parent = nullptr);

    Q_INVOKABLE Repository updateRepository(Repository repo);

    void checkError(int error);

    void fetchAllRemotes(git_repository *repository);

    std::vector<std::string> getAllTags(git_repository *repository);

    void notifyIfNewTags(Repository repo, std::vector<std::string> &tagsBeforeFetch,
                         std::vector<std::string> &tagsAfterFetch);
};

#endif //CUPOLA_GITBACKEND_H
