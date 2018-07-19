

#ifndef CUPOLA_REPOSITORY_H
#define CUPOLA_REPOSITORY_H


#include <QtGui/QColor>

class Repository {
public:
    Repository(const QString &name, const QColor &statusColor);

    QString name() const;
    QColor statusColor() const;

private:

    QString m_name;
    QColor m_statusColor;

};


#endif //CUPOLA_REPOSITORY_H
