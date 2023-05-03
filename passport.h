#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std::string_view_literals;

class Passport{
public:
    Passport()
        : identityDocument_() ,expiration_date_(GetExpirationDate()){
        Passport::SetVTable(this);
        std::cout << "Passport::Ctor()"sv << std::endl;
    }

    Passport(const Passport& other)
        : identityDocument_(other.identityDocument_)
        , expiration_date_(other.expiration_date_){
        Passport::SetVTable(this);
        std::cout << "Passport::CCtor()"sv << std::endl;
    }

    ~Passport() {
        std::cout << "Passport::Dtor()"sv << std::endl;
        IdentityDocument::SetVTable((IdentityDocument*)this);
    }

    void PrintID() const{
        GetVtable()->inside_this(this);
    }

    void Delete() {
        GetVtable()->delete_this(this);
    }

    operator IdentityDocument() const{
        return {identityDocument_};
    }

    using InsideFunction = void(*)(const Passport*);
    using DeleteFunction = void(*)(Passport*);

    struct Vtable {
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };

    static void SetVTable(Passport* obj) {
        *(Passport::Vtable**)obj = &Passport::VTABLE;
    }

    const Vtable* GetVtable() const {
        return (const Passport::Vtable*)identityDocument_.GetVtable();
    }

    Vtable* GetVtable() {
        return (Passport::Vtable*)identityDocument_.GetVtable();
    }


    void PrintVisa(const std::string& country) const {
        std::cout << "Passport::PrintVisa("sv << country << ") : "sv << identityDocument_.GetID() << std::endl;
    }

    void PrintUniqueIDCount() {
        identityDocument_.PrintUniqueIDCount();
    }
private:
    IdentityDocument identityDocument_;
    const struct tm expiration_date_;

    static Passport::Vtable VTABLE;

    tm GetExpirationDate() {
        time_t t = time(nullptr);
        tm exp_date = *localtime(&t);
        exp_date.tm_year += 10;
        mktime(&exp_date);
        return exp_date;
    }

    static void PrintID(const Passport* passport){
        std::cout << "Passport::PrintID() : "sv <<passport->identityDocument_.GetID();
        std::cout << " expiration date : "sv << passport->expiration_date_.tm_mday << "/"sv << passport->expiration_date_.tm_mon << "/"sv
                  << passport->expiration_date_.tm_year + 1900 << std::endl;
    }

    static void Delete(Passport* obj) {
        delete obj;
    }
};

Passport::Vtable Passport::VTABLE = { Passport::PrintID, Passport::Delete };