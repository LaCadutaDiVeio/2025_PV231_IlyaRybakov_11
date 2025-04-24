#include "core/file.h"
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <filesystem>

void File::copyTo(const std::string& dest) const {
    if (!exists()) {
        throw FileCopyError("Source file does not exist");
    }

    try {
        std::filesystem::copy_file(
            path,
            dest,
            std::filesystem::copy_options::overwrite_existing // для чего-то надо :/
            );
    } catch (const std::filesystem::filesystem_error& e) {
        throw FileCopyError(e.what());
    }
}


void File::remove() {
    if (!exists()) {
        throw FileRemoveError("File does not exist");
    }

    try {
        if (isDirectory()) {
            std::filesystem::remove_all(path); // для папок
        } else {
            std::filesystem::remove(path); // для файлов
        }
    } catch (const std::filesystem::filesystem_error& e) {
        throw FileRemoveError(e.what());
    }
}

void File::validatePath() const {
    if (path.empty()) {
        throw FileOpenError("Path cannot be empty");
    }

    #ifdef _WIN32
    if (path.find_first_of("*?<>|") != std::string::npos) {
        throw FileOpenError("Path contains invalid characters");
    }
    #endif
}


/*
 * struct stat {
    dev_t st_dev;      // ID устройства
    ino_t st_ino;      // Inode номер
    mode_t st_mode;    // Тип и права
    nlink_t st_nlink;  // Количество жёстких ссылок
    uid_t st_uid;      // ID владельца
    gid_t st_gid;      // ID группы
    off_t st_size;     // Размер в байтах
    time_t st_mtime;   // Время последнего изменения
         ...
};
*/
// stat(...) - заполнение сис. буфера; 0 если +, -1 если -

bool File::rename(const std::string& newName) {
    std::string newPath = joinPaths(std::filesystem::path(path).parent_path().string(), newName);
    return std::rename(path.c_str(), newPath.c_str()) == 0;
}

bool File::exists() const {
    struct stat buffer;
    return stat(path.c_str(), &buffer) == 0;
}

bool File::isDirectory() const {
    struct stat buffer;
    return stat(path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode);
}

size_t File::getSize() const {
    struct stat buffer;
    return stat(path.c_str(), &buffer) == 0 ? buffer.st_size : 0;
}

std::time_t File::getLastModified() const {
    struct stat buffer;
    return stat(path.c_str(), &buffer) == 0 ? buffer.st_mtime : 0;
}

std::string File::getPath() const {
    return path;
}

std::string File::getName() const {
    size_t pos = path.find_last_of("/\\");
    return pos == std::string::npos ? path : path.substr(pos + 1);
}

std::string File::joinPaths(const std::string& base, const std::string& name) {
    return (std::filesystem::path(base) / name).string();
}
