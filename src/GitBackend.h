#ifndef CUPOLA_GITBACKEND_H
#define CUPOLA_GITBACKEND_H

#include <QtCore/QObject>
#include <git2.h>
#include "Repository.h"
#include "GitCredentialsManager.h"

class GitBackend : public QObject {
Q_OBJECT
public:
    explicit GitBackend(QObject *parent = nullptr);

    explicit GitBackend(GitCredentialsManager *credentialsManager, QObject *parent = nullptr);

    Q_INVOKABLE Repository updateRepository(Repository repo);

private:

    GitCredentialsManager *credentialsManager;

    void checkError(int error);

    void fetchAllRemotes(git_repository *repository);

    std::vector<std::string> getAllTags(git_repository *repository);

    void notifyIfNewTags(Repository repo, std::vector<std::string> &tagsBeforeFetch,
                         std::vector<std::string> &tagsAfterFetch);

    void notifyIfNewBranchCommits(Repository repo, git_repository *repoHandle);
};

#endif //CUPOLA_GITBACKEND_H
