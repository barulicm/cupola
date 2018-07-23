#include <git2.h>
#include <iostream>
#include <QtWidgets/QFileDialog>
#include "GitCredentialsManager.h"

int
credential_manager_callback(git_cred **cred, const char *url, const char *username_from_url, unsigned int allowed_types,
                            void *payload) {
  GitCredentialsManager& credentialsManager = *static_cast<GitCredentialsManager*>(payload);

  if(allowed_types & GIT_CREDTYPE_USERNAME) {
    // network is asking for a username associated with an SSH key
    std::cout << "network is asking for a username associated with an SSH key\n";
    return -1;
  }
  if(allowed_types & GIT_CREDTYPE_USERPASS_PLAINTEXT) {
    // network is asking for a username/password combination to use
    std::cout << "network is asking for a username/password combination to use\n";
    return -1;
  }
  if(allowed_types & GIT_CREDTYPE_SSH_KEY) {
    // network is asking for an SSH key to use
    std::cout << "network is asking for an SSH key to use\n";
    auto publicKeyPath = QFileDialog::getOpenFileName(nullptr, "Public Key", "~/.ssh").toStdString();
    auto privateKeyPath = QFileDialog::getOpenFileName(nullptr, "Private Key", "~/.ssh").toStdString();
    std::cout << publicKeyPath << "\t" << privateKeyPath << "\n";
    git_cred_ssh_key_new(cred, username_from_url, publicKeyPath.c_str(), privateKeyPath.c_str(), "");
    return 0;
  }
  if(allowed_types & GIT_CREDTYPE_SSH_CUSTOM) {
    // network is asking for an SSH key with custom signing callback to use
    std::cout << "network is asking for an SSH key with custom signing callback to use\n";
    return -1;
  }
  if(allowed_types & GIT_CREDTYPE_DEFAULT) {
    // network is asking for a ... default? credential type?...
    std::cout << "network is asking for a ... default? credential type?...\n";
    return -1;
  }
  if(allowed_types & GIT_CREDTYPE_SSH_MEMORY) {
    // network is asking for an SSH key from memory
    std::cout << "network is asking for an SSH key from memory\n";
    return -1;
  }

  std::cout << "network is asking for an unimplemented credential type\n";
  std::cout << allowed_types << "\n";
  return -1;
}

GitCredentialsManager::GitCredentialsManager(QObject *parent)
  : QObject(parent)
{
}
