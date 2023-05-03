#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class DrivingLicence{
public:
    DrivingLicence(): identityDocument_() {
        DrivingLicence::SetVTable(this);
        std::cout << "DrivingLicence::Ctor()"sv << std::endl;
    }

    DrivingLicence(const DrivingLicence& other)
        : identityDocument_(other.identityDocument_){
        DrivingLicence::SetVTable(this);
        std::cout << "DrivingLicence::CCtor()"sv << std::endl;
    }

    ~DrivingLicence() {
        std::cout << "DrivingLicence::Dtor()"sv << std::endl;
        IdentityDocument::SetVTable((IdentityDocument*)this);
    }

    void PrintID() const{
        GetVtable()->inside_this(this);
    }

    void Delete() {
        GetVtable()->delete_this(this);
    }

    operator IdentityDocument() {
        return {identityDocument_};
    }

    using InsideFunction = void(*)(const DrivingLicence*);
    using DeleteFunction = void(*)(DrivingLicence*);

    struct Vtable {
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };

    static void SetVTable(DrivingLicence* obj) {
        *(DrivingLicence::Vtable**)obj = &DrivingLicence::VTABLE;
    }

    const Vtable* GetVtable() const {
        return (const DrivingLicence::Vtable*)identityDocument_.GetVtable();
    }

    Vtable* GetVtable() {
        return (DrivingLicence::Vtable*)identityDocument_.GetVtable();
    }

    void PrintUniqueIDCount() {
        identityDocument_.PrintUniqueIDCount();
    }

    int GetId() const{
        return identityDocument_.GetID();
    }

private:
    IdentityDocument identityDocument_;
    static DrivingLicence::Vtable VTABLE;

    static void PrintID(const DrivingLicence* drivingLicence){
        std::cout << "DrivingLicence::PrintID() : "sv << drivingLicence->identityDocument_.GetID()  << std::endl;
    }

    static void Delete(DrivingLicence* obj) {
        delete obj;
    }
};

DrivingLicence::Vtable DrivingLicence::VTABLE = { DrivingLicence::PrintID, DrivingLicence::Delete };