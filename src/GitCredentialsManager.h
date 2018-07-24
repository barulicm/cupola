

#ifndef CUPOLA_GITCREDENTIALSMANAGER_H
#define CUPOLA_GITCREDENTIALSMANAGER_H

#include <git2/transport.h>
#include <QtCore/QObject>

int
credential_manager_callback(git_cred **cred, const char *url, const char *username_from_url, unsigned int allowed_types,
                            void *payload);

class GitCredentialsManager : public QObject {
Q_OBJECT
public:
    explicit GitCredentialsManager(QObject *parent = nullptr);

    int get_ssh_key(git_cred **out, const char *url, const char *username_from_url);

    int get_userpass(git_cred **out, const char *url, const char *username_from_url);

signals:
    void promptForUserPass();

private:



};


#endif //CUPOLA_GITCREDENTIALSMANAGER_H
