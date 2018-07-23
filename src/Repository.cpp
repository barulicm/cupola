#include "Repository.h"

Repository::Repository(QObject *parent)
  : QObject(parent)
{
}

Repository::Repository(const QString &name, const QString &localPath)
  : m_name(name),
    m_statusColor("red"),
    m_localPath(localPath)
{
}

Repository::Repository(const Repository &other)
  : m_name(other.m_name),
    m_statusColor(other.m_statusColor),
    m_localPath(other.m_localPath)
{
}

Repository &Repository::operator=(const Repository &other) {
  m_name = other.m_name;
  m_statusColor = other.m_statusColor;
  m_localPath = other.m_localPath;
  return *this;
}

QString Repository::name() const {
  return m_name;
}

QColor Repository::statusColor() const {
  return m_statusColor;
}

QString Repository::localPath() const {
  return m_localPath;
}

void Repository::setName(QString name) {
  m_name = name;
}

void Repository::setStatusColor(QColor statusColor) {
  m_statusColor = statusColor;
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
