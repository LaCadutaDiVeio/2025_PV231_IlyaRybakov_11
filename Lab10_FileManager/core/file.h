#ifndef FILE_H
#define FILE_H

#include "string"
#include "ctime"
#include <exception>
#include "core/utils/smartptr.h"

// === Исключения ===
class FileOpenError : public std::runtime_error {
public:
    explicit FileOpenError(const std::string& what_arg)
        : std::runtime_error(what_arg) {}
    explicit FileOpenError(const char* what_arg)
        : std::runtime_error(what_arg) {}
};

class FileCopyError : public std::runtime_error {
public:
    explicit FileCopyError(const std::string& what_arg)
        : std::runtime_error(what_arg) {}
    explicit FileCopyError(const char* what_arg)
        : std::runtime_error(what_arg) {}
};

class FileRemoveError : public std::runtime_error {
public:
    explicit FileRemoveError(const std::string& what_arg)
        : std::runtime_error(what_arg) {}
    explicit FileRemoveError(const char* what_arg)
        : std::runtime_error(what_arg) {}
};
// ==================

class File {
private:
    std::string path;

    void validatePath() const;
    static std::string joinPaths(const std::string& base, const std::string& name);

public:
    explicit File(const std::string& path);
    ~File();

    void copyTo(const std::string& destination) const;
    void remove();
    bool rename(const std::string& newName);

    // Работа с информацией
    std::string getPath() const;
    std::string getName() const;
    size_t getSize() const;
    std::time_t getLastModified() const;
    bool exists() const;
    bool isDirectory() const;
};


#endif // FILE_H
