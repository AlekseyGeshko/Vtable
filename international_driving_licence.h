#pragma once

#include "driving_licence.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class InternationalDrivingLicence {
public:
    InternationalDrivingLicence(): drivingLicence_() {
        InternationalDrivingLicence::SetVTable(this);
        std::cout << "InternationalDrivingLicence::Ctor()"sv << std::endl;
    }

    InternationalDrivingLicence(const InternationalDrivingLicence& other)
        :drivingLicence_(other.drivingLicence_)
    {
        InternationalDrivingLicence::SetVTable(this);
        std::cout << "InternationalDrivingLicence::CCtor()"sv << std::endl;
    }

    ~InternationalDrivingLicence() {
        std::cout << "InternationalDrivingLicence::Dtor()"sv << std::endl;
        DrivingLicence::SetVTable((DrivingLicence*)this);
    }

    void PrintID() const{
        GetVtable()->inside_this(this);
    }

    void Delete() {
        GetVtable()->delete_this(this);
    }

    operator DrivingLicence(){
        return {drivingLicence_};
    }

    operator IdentityDocument() {
        return drivingLicence_.operator IdentityDocument();
    }

    using InsideFunction = void(*)(const InternationalDrivingLicence*);
    using DeleteFunction = void(*)(InternationalDrivingLicence*);

    struct Vtable {
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };

    static void SetVTable(InternationalDrivingLicence* obj) {
        *(InternationalDrivingLicence::Vtable**)obj = &InternationalDrivingLicence::VTABLE;
    }

    const Vtable* GetVtable() const {
        return (const InternationalDrivingLicence::Vtable*)drivingLicence_.GetVtable();
    }

    Vtable* GetVtable() {
        return (InternationalDrivingLicence::Vtable*)drivingLicence_.GetVtable();
    }

    void PrintUniqueIDCount() {
        drivingLicence_.PrintUniqueIDCount();
    }

private:
    DrivingLicence drivingLicence_;
    static InternationalDrivingLicence::Vtable VTABLE;

    static void PrintID(const InternationalDrivingLicence* iDL) {
        std::cout << "InternationalDrivingLicence::PrintID() : "sv << iDL->drivingLicence_.GetId() << std::endl;
    }
    static void Delete(InternationalDrivingLicence* obj) {
        delete obj;
    }
};

InternationalDrivingLicence::Vtable InternationalDrivingLicence::VTABLE
= { InternationalDrivingLicence::PrintID, InternationalDrivingLicence::Delete };