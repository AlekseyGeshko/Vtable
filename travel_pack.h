class TravelPack {
public:
    TravelPack()
        : identity_document_()
        , identity_doc1_((IdentityDocument*)(new Passport()))
        , identity_doc2_((IdentityDocument*)(new DrivingLicence()))
    {
        TravelPack::SetVTable(this);
        std::cout << "TravelPack::Ctor()"sv << std::endl;
    }
 
    TravelPack(const TravelPack& other)
        : identity_document_(other.identity_document_)
        , identity_doc1_((IdentityDocument*)(new Passport(*reinterpret_cast<Passport*>(other.identity_doc1_))))
        , identity_doc2_((IdentityDocument*)(new DrivingLicence(*reinterpret_cast<DrivingLicence*>(other.identity_doc2_))))
        , additional_pass_(other.additional_pass_)
        , additional_dr_licence_(other.additional_dr_licence_) 
    {
        TravelPack::SetVTable(this);
        std::cout << "TravelPack::CCtor()"sv << std::endl;
    }
 
    ~TravelPack() {
        identity_doc1_->Delete();
        //delete identity_doc1_;
        identity_doc2_->Delete();
        //delete identity_doc2_;
        std::cout << "TravelPack::Dtor()"sv << std::endl;
        IdentityDocument::SetVTable((IdentityDocument*)this);
    }
 
    operator IdentityDocument() {
        return { identity_document_ };
    }
 
    void PrintID() const {
        GetVtable()->inside_this(this);
    }
 
    void Delete() {
        GetVtable()->delete_this(this);
    }
 
    using InsideFunction = void(*)(const TravelPack*);
    using DeleteFunction = void(*)(TravelPack*);
 
    struct Vtable {
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };
 
    static void SetVTable(TravelPack* obj) {
        *(TravelPack::Vtable**)obj = &TravelPack::VTABLE;
    }
 
    const Vtable* GetVtable() const {
        return (const TravelPack::Vtable*)identity_document_.GetVtable();
    }
 
    Vtable* GetVtable() {
        return (TravelPack::Vtable*)identity_document_.GetVtable();
    }
 
    int GetID() const {
        return identity_document_.GetID();
    }
 
    static void PrintUniqueIDCount() {
        IdentityDocument::PrintUniqueIDCount();
    }
 
    static TravelPack::Vtable VTABLE;
private:
    IdentityDocument identity_document_;
    static void Delete(TravelPack* obj) {
        delete obj;
    }
    static void PrintID(const TravelPack* obj) {
        obj->identity_doc1_->PrintID();
        obj->identity_doc2_->PrintID();
        obj->additional_pass_.PrintID();
        obj->additional_dr_licence_.PrintID();
    }
 
    IdentityDocument* identity_doc1_;
    IdentityDocument* identity_doc2_;
    Passport additional_pass_;
    DrivingLicence additional_dr_licence_;
};
 
TravelPack::Vtable TravelPack::VTABLE = { TravelPack::PrintID, TravelPack::Delete };