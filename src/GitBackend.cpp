#include <iostream>
#include "GitBackend.h"

GitBackend::GitBackend(QObject *parent)
  : QObject(parent)
{
  git_libgit2_init();
}

Repository GitBackend::updateRepository(Repository repo) {
  repo.setStatusColor(Qt::transparent);
  auto repoPath = repo.localPath().toStdString().c_str();
  if (git_repository_open_ext(nullptr, repoPath, GIT_REPOSITORY_OPEN_NO_SEARCH, nullptr) == 0) {
    git_repository *repoHandle = nullptr;
    checkError(git_repository_open(&repoHandle, repoPath));

    auto tagsBeforeFetch = getAllTags(repoHandle);

    fetchAllRemotes(repoHandle);

    auto tagsAfterFetch = getAllTags(repoHandle);

    notifyIfNewTags(repo, tagsBeforeFetch, tagsAfterFetch);

    git_repository_free(repoHandle);
  }
  std::cout << repo.name().toStdString() << " updated.\n";
  return repo;
}

void GitBackend::checkError(int error) {
  if (error < 0) {
    const git_error *e = giterr_last();
    printf("Error %d/%d: %s\n", error, e->klass, e->message);
    exit(error);
  }
}

void GitBackend::fetchAllRemotes(git_repository *repository) {
  git_strarray remotes = {0};
  checkError(git_remote_list(&remotes, repository));
  for(auto i = 0; i < remotes.count; i++) {
    auto remoteName = remotes.strings[i];
    git_remote *remote = nullptr;
    checkError(git_remote_lookup(&remote, repository, remoteName));
    checkError(git_remote_fetch(remote, nullptr, nullptr, nullptr));
    git_remote_free(remote);
  }
}

std::vector<std::string> GitBackend::getAllTags(git_repository *repository) {
  git_strarray tags = {0};
  checkError(git_tag_list(&tags, repository));
  std::vector<std::string> stdTags;
  stdTags.resize(tags.count);
  for(auto i = 0; i < tags.count; i++) {
    stdTags[i] = tags.strings[i];
  }
  git_strarray_free(&tags);
  return stdTags;
}

void GitBackend::notifyIfNewTags(Repository repo, std::vector<std::string> &tagsBeforeFetch,
                                 std::vector<std::string> &tagsAfterFetch) {
  std::sort(tagsBeforeFetch.begin(), tagsBeforeFetch.end());
  std::sort(tagsAfterFetch.begin(), tagsAfterFetch.end());
  std::vector<std::string> newTags;
  std::set_difference(tagsAfterFetch.begin(), tagsAfterFetch.end(), tagsBeforeFetch.begin(), tagsBeforeFetch.end(),
                      std::back_inserter(newTags));
  if(!newTags.empty()) {
    repo.setStatusColor("red");
    QString notification("New tags available: ");
    for(const auto &tag : newTags) {
      notification.append(QString::fromStdString(tag));
      notification.append(' ');
    }
    repo.addNotification(notification);
  }
}
