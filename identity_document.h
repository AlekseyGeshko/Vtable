#pragma once

#include <iostream>
#include <string>

using namespace std::string_view_literals;

class IdentityDocument {
public:
    IdentityDocument()
        : unique_id_(++unique_id_count_)
    {
        IdentityDocument::SetVTable(this);
        std::cout << "IdentityDocument::Ctor() : "sv << unique_id_ << std::endl;
    }

    ~IdentityDocument() {
        --unique_id_count_;
        std::cout << "IdentityDocument::Dtor() : "sv << unique_id_ << std::endl;
    }

    IdentityDocument(const IdentityDocument& other)
        : unique_id_(++unique_id_count_)
    {
        IdentityDocument::SetVTable(this);
        std::cout << "IdentityDocument::CCtor() : "sv << unique_id_ << std::endl;
    }

    static void SetVTable(IdentityDocument* obj) {
        *(IdentityDocument::Vtable**)obj = &IdentityDocument::VTABLE;
    }

    IdentityDocument& operator=(const IdentityDocument&) = delete;

    using InsideFunction = void(*)(const IdentityDocument* identityDocument_);
    using DeleteFunction = void(*)(IdentityDocument*);

    struct Vtable {
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };

    void PrintID() const {
        GetVtable()->inside_this(this);
    }

    void Delete() {
        GetVtable()->delete_this(this);
    }

    const Vtable* GetVtable() const {
        return vptr_;
    }

    Vtable* GetVtable() {
        return vptr_;
    }

    static void PrintUniqueIDCount() {
        std::cout << "unique_id_count_ : "sv << unique_id_count_ << std::endl;
    }

    int GetID() const {
        return unique_id_;
    }

    static Vtable VTABLE;

private:
    static void PrintID(const IdentityDocument* identityDocument_){
        std::cout << "IdentityDocument::PrintID() : "sv << identityDocument_->unique_id_ << std::endl;
    }

    static void Delete(IdentityDocument* obj) {
        //В этот момент тип объекта известен. Просто удаляем указатель.
        //Вызов delete запустит процесс вызовов деструкторов
        delete obj;
    }

    Vtable* vptr_ = nullptr;
    static int unique_id_count_;
    int unique_id_;
};

IdentityDocument::Vtable IdentityDocument::VTABLE = { IdentityDocument::PrintID, IdentityDocument::Delete };
int IdentityDocument::unique_id_count_ = 0;