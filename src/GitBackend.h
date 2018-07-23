#ifndef CUPOLA_GITBACKEND_H
#define CUPOLA_GITBACKEND_H

#include <QtCore/QObject>
#include "Repository.h"

class GitBackend : public QObject {
Q_OBJECT
public:
    explicit GitBackend(QObject *parent = nullptr);

    Q_INVOKABLE Repository updateRepository(Repository repo);
};

#endif //CUPOLA_GITBACKEND_H
