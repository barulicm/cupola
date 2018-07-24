#include <iostream>
#include <git2/remote.h>
#include "GitBackend.h"

GitBackend::GitBackend(QObject *parent)
  : QObject(parent),
    credentialsManager(nullptr)
{
  git_libgit2_init();
}

GitBackend::GitBackend(GitCredentialsManager *credentialsManager, QObject *parent)
  : QObject(parent),
    credentialsManager(credentialsManager)
{
  git_libgit2_init();
}

Repository GitBackend::updateRepository(Repository repo) {
  const auto repoPath = repo.localPath().toStdString();
  if (git_repository_open_ext(nullptr, repoPath.c_str(), GIT_REPOSITORY_OPEN_NO_SEARCH, nullptr) == 0) {
    git_repository *repoHandle = nullptr;
    checkError(git_repository_open(&repoHandle, repoPath.c_str()));

    auto tagsBeforeFetch = getAllTags(repoHandle);

    fetchAllRemotes(repoHandle);

    auto tagsAfterFetch = getAllTags(repoHandle);

    notifyIfNewTags(repo, tagsBeforeFetch, tagsAfterFetch);

    notifyIfNewBranchCommits(repo, repoHandle);

    git_repository_free(repoHandle);
    std::cout << repo.name().toStdString() << " updated.\n";
  } else {
    std::cerr << "Could not find git repository at " << repoPath << std::endl;
  }
  return repo;
}

void GitBackend::checkError(int error) {
  if (error < 0) {
    const git_error *e = giterr_last();
    if(e != nullptr) {
      printf("Error %d/%d: %s\n", error, e->klass, e->message);
    }
    exit(error);
  }
}

void GitBackend::fetchAllRemotes(git_repository *repository) {
  git_fetch_options fetch_opts = GIT_FETCH_OPTIONS_INIT;
  fetch_opts.callbacks.credentials = credential_manager_callback;
  fetch_opts.callbacks.payload = credentialsManager;

  git_strarray remotes = {0};
  checkError(git_remote_list(&remotes, repository));
  for(auto i = 0; i < remotes.count; i++) {
    auto remoteName = remotes.strings[i];
    git_remote *remote = nullptr;
    checkError(git_remote_lookup(&remote, repository, remoteName));
    git_strarray refspecs{nullptr, 0};
    checkError(git_remote_fetch(remote, &refspecs, &fetch_opts, "fetch"));
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
    QString notification("New tags available: ");
    for(const auto &tag : newTags) {
      notification.append(QString::fromStdString(tag));
      notification.append(' ');
    }
    repo.addNotification(notification);
  }
}

void GitBackend::notifyIfNewBranchCommits(Repository repo, git_repository *repoHandle) {
  git_reference *headReference = nullptr;
  checkError(git_repository_head(&headReference, repoHandle));
  auto isBranch = git_reference_is_branch(headReference);
  if(isBranch == 1) {
    const char* branchName;
    checkError(git_branch_name(&branchName, headReference));

    git_reference* upstreamReference;
    auto upstreamRetVal = git_branch_upstream(&upstreamReference, headReference);
    if(upstreamRetVal == 0) {
      auto headName = git_reference_name(headReference);
      auto upstreamName = git_reference_name(upstreamReference);

      git_revwalk* revwalk;
      git_revwalk_new(&revwalk, repoHandle);
      git_revwalk_push_ref(revwalk, upstreamName);
      git_revwalk_hide_ref(revwalk, headName);

      git_oid id;
      int commitCount = 0;
      while(!git_revwalk_next(&id, revwalk)) {
        commitCount++;
      }

      if(commitCount > 0) {
        repo.addNotification(QString("There are %1 new commits available on the %2 branch.").arg(QString::number(commitCount), branchName));
      }

      git_revwalk_free(revwalk);
      git_reference_free(upstreamReference);
    } else if(upstreamRetVal != GIT_ENOTFOUND) {
      checkError(upstreamRetVal);
    }
  } else if(isBranch != 0) {
    checkError(isBranch);
  }
  git_reference_free(headReference);
}
