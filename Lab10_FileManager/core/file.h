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


#endif // FILE_H
