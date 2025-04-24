#include "core/file_manager.h"

// Добавление файла с проверкой дубликатов
void FileManager::addFile(SmartPtr<File> file) {
    if (!file || contains(file->getPath())) {
        return;
    }

    pathLookup.insert(file->getPath());
    files.push_back(std::move(file)); // Перемещаем владение
}

// Копирование группы файлов
void FileManager::copyFiles(const std::vector<SmartPtr<File>>& files,
                            const std::string& dest) const {
    for (const auto& file : files) {
        try {
            file->copyTo(dest + "/" + file->getName());
        } catch (const FileCopyError& e) {
            // Логирование ошибки (реализуйте отдельно)
        }
    }
}

// Проверка наличия файла по пути
bool FileManager::contains(const std::string& path) const {
    return pathLookup.find(path) != pathLookup.end();
}

// Доступ к файлам
const std::vector<SmartPtr<File>>& FileManager::getFiles() const {
    return files;
}
