#ifndef FILE_MANAGER_CONTROLLER_H
#define FILE_MANAGER_CONTROLLER_H

#include <QObject>
#include "core/file_manager.h"
#include "core/file_copier.h"

class FileManagerController : public QObject
{
    Q_OBJECT
public:
    explicit FileManagerController(QObject* parent = nullptr);

    void setSourceDir(const QString& path);
    void setDestDir  (const QString& path);

    const QString& sourceDir() const {
        return m_src;
    }
    const QString& destDir() const {
        return m_dst;
    }

    // Вернёт {copied, skipped}
    QPair<int,int> copySelected(const QList<QString>& paths);

signals:
    void copyFinished(int copied, int skipped, const QString& log);

private:
    QString             m_src, m_dst;
    FileManager   m_manager;
    FileCopier    m_copier;
};

#endif // FILE_MANAGER_CONTROLLER_H
