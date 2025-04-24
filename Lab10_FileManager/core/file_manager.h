#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "core/file.h"
#include "core/utils/smartptr.h"
#include <vector>
#include <unordered_set>

class FileManager {
private:
    std::vector<SmartPtr<File>> files;
    std::unordered_set<std::string> pathLookup; // быстрый посик

public:
    void addFile(SmartPtr<File> file);
    void copyFiles(const std::vector<SmartPtr<File>>& files, const std::string& destination) const;
    const std::vector<SmartPtr<File>>& getFiles() const;
    bool contains(const std::string& destination) const;
};

#endif // FILE_MANAGER_H
