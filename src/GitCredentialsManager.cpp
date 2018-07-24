#include <git2.h>
#include <iostream>
#include <QtQuick/QQuickView>
#include "GitCredentialsManager.h"

int
credential_manager_callback(git_cred **cred, const char *url, const char *username_from_url, unsigned int allowed_types,
                            void *payload) {
  GitCredentialsManager& credentialsManager = *static_cast<GitCredentialsManager*>(payload);

  if(allowed_types & GIT_CREDTYPE_USERPASS_PLAINTEXT) {
    return credentialsManager.get_userpass(cred, url, username_from_url);
  } else if(allowed_types & GIT_CREDTYPE_SSH_KEY) {
    return credentialsManager.get_ssh_key(cred, url, username_from_url);
  } else {
    std::cout << "libgit2 asked for a credential type I don't know how to fill yet.\n";
    std::cout << "allowed_types is " << allowed_types << "\n";
    return -1;
  }
}

GitCredentialsManager::GitCredentialsManager(QObject *parent)
  : QObject(parent)
{
}

int GitCredentialsManager::get_ssh_key(git_cred **out, const char *url, const char *username_from_url) {
  auto ret = git_cred_ssh_key_from_agent(out, username_from_url);
  if(ret != 0) {
    const git_error *e = giterr_last();
    if(e != nullptr) {
      printf("Error %d/%d: %s\n", ret, e->klass, e->message);
    }
    return ret;
  }
  return 0;
}

int GitCredentialsManager::get_userpass(git_cred **out, const char *url, const char *username_from_url) {
  emit promptForUserPass();
  return -1;
}
