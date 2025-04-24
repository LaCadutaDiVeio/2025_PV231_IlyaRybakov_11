#ifndef FILE_COPIER_H
#define FILE_COPIER_H

#include "core/file.h"
#include "core/utils/smartptr.h"
#include <vector>

class FileCopier {
public:
    FileCopier() : copiedCount(0), skippedCount(0) {}

    bool copyFiles(const std::vector<SmartPtr<File>>& files,
                   const std::string& destination);

    int getCopiedCount() const { return copiedCount; }
    int getSkippedCount() const { return skippedCount; }

private:
    bool copySingleFile(const SmartPtr<File>& file,
                        const std::string& destPath);

    int copiedCount;
    int skippedCount;
};

#endif // FILE_COPIER_H
