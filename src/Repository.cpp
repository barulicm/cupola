#include "Repository.h"

Repository::Repository(const QString &name, const QColor &statusColor)
  : m_name(name),
    m_statusColor(statusColor)
{
}

QString Repository::name() const {
  return m_name;
}

QColor Repository::statusColor() const {
  return m_statusColor;
}
