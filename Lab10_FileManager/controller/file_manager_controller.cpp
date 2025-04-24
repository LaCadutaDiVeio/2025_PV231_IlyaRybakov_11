#include "file_manager_controller.h"
#include <QTextStream>

FileManagerController::FileManagerController(QObject *parent)
    : QObject(parent) {}

void FileManagerController::setSourceDir(const QString &p){ m_src = p; }
void FileManagerController::setDestDir  (const QString &p){ m_dst = p; }

QPair<int,int> FileManagerController::copySelected(const QList<QString>& paths)
{
    std::vector<SmartPtr<File>> toCopy;
    for(const QString& q : paths)
        toCopy.emplace_back(SmartPtr(new File(q.toStdString())));

    bool ok = m_copier.copyFiles(toCopy, m_dst.toStdString());

    emit copyFinished(m_copier.getCopiedCount(),
                      m_copier.getSkippedCount(),
                      ok ? "OK" : "Some files skipped");
    return {m_copier.getCopiedCount(), m_copier.getSkippedCount()};
}
