#include <iostream>
#include "Repository.h"

Repository::Repository(QObject *parent)
  : QObject(parent)
{
}

Repository::Repository(const QString &name, const QString &localPath)
  : m_name(name),
    m_localPath(localPath)
{
}

Repository::Repository(const Repository &other)
  : m_name(other.m_name),
    m_localPath(other.m_localPath),
    m_notifications(other.m_notifications)
{
}

Repository &Repository::operator=(const Repository &other) {
  m_name = other.m_name;
  m_localPath = other.m_localPath;
  m_notifications = other.m_notifications;
  return *this;
}

QString Repository::name() const {
  return m_name;
}

QString Repository::localPath() const {
  return m_localPath;
}

void Repository::setName(QString name) {
  m_name = name;
}

void Repository::setLocalPath(QString localPath) {
  m_localPath = localPath;
}

QStringList Repository::notifications() const {
  return m_notifications;
}

void Repository::addNotification(QString notification) {
  m_notifications.append(notification);
}

void Repository::clearNotification(int notificationIndex) {
  m_notifications.removeAt(notificationIndex);
}
