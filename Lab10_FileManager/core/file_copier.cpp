#include "core/file_copier.h"

bool FileCopier::copyFiles(const std::vector<SmartPtr<File>>& files,
                           const std::string& dest) {
    copiedCount = 0;
    skippedCount = 0;

    for (const auto& file : files) {
        if (copySingleFile(file, dest)) {
            ++copiedCount;
        } else {
            ++skippedCount;
        }
    }

    return skippedCount == 0;
}

bool FileCopier::copySingleFile(const SmartPtr<File>& file,
                                const std::string& destPath) {
    if (!file || !file->exists()) return false;

    try {
        std::string dest = destPath + "/" + file->getName();
        file->copyTo(dest); // всегда перезаписываем
        return true;
    } catch (...) {
        return false;
    }
}
