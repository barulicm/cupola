

#ifndef CUPOLA_REPOSITORY_H
#define CUPOLA_REPOSITORY_H

#include <QObject>
#include <QtGui/QColor>

class Repository : public QObject {
Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);
    Repository(const QString &name, const QString &localPath);
    Repository(const Repository &other);
    Repository& operator=(const Repository &other);

    QString name() const;
    QColor statusColor() const;
    QString localPath() const;

    void setName(QString name);
    void setStatusColor(QColor statusColor);
    void setLocalPath(QString localPath);

private:

    QString m_name;
    QColor m_statusColor;
    QString m_localPath;

};

Q_DECLARE_METATYPE(Repository)

#endif //CUPOLA_REPOSITORY_H
