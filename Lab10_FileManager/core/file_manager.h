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
};

#endif // FILE_MANAGER_H
