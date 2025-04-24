#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <stdexcept>
#include <string>

// === Исключения===
class SmartPtrCopyException : public std::logic_error {
public:
    explicit SmartPtrCopyException(const std::string& what_arg)
        : std::logic_error(what_arg) {}
    explicit SmartPtrCopyException(const char* what_arg)
        : std::logic_error(what_arg) {}
};
// =========


template <typename T>
class SmartPtr {
private:
    T* ptr; // обычный указатель
public:
    explicit SmartPtr(T* p = nullptr) : ptr(p) {};
    ~SmartPtr() {
        delete ptr;
    }

    // Запрещаем копирование
    //SmartPtr(const SmartPtr&) = delete;
    //SmartPtr& operator=(const SmartPtr&) = delete;
    SmartPtr(const SmartPtr& other) {
        throw SmartPtrCopyException(
            "SmartPtr: Copying is prohibited. Use move semantics instead."
            );
    }

    SmartPtr& operator=(const SmartPtr& other) {
        throw SmartPtrCopyException(
            "SmartPtr: Copy assignment is prohibited. Use move assignment instead."
            );
    }
    /*
     * Для избежания двойного удаления, когда оба smartPtr владеют одним ptr,
     * при удалении ptr, первый smartPtr удалит его, а второй обратится к уже
     * освобождённой памяти + принцип единственности владения
    */

    explicit operator bool() const {
        return ptr != nullptr; // Для упрощения проверок if(file)
    }

    // Move-конструктор
    SmartPtr(SmartPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    // Move-перенос
    SmartPtr& operator=(SmartPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        return *this;
    }

    // Операторы доступа:
    T* operator->() const {
        return ptr;
    }
    T& operator*() const {
        return *ptr;
    }

    T* get() const {
        return ptr;
    }

    // Передача владения
    T* release() {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    void reset(T* p = nullptr) {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }

    void swap(SmartPtr& other) noexcept {
        std::swap(ptr, other.ptr);
    }


};

#endif //SMARTPTR_H
