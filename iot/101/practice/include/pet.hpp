#ifndef PET
#define PET

// Add an action which will allow for table entries to be added to pet table

//  Table Step 1.
//      to make a table, add c++ attribute
class [[eosio::table, eosio::contract("practice")]] pet_t
{
private:
    uint64_t id;
    eosio::name owner;
    eosio::name petname;
    uint64_t age;
    eosio::name type;
public:
    // no default constructor
    pet_t() {};
    // parameterized constructor
    pet_t(uint64_t const _id,
        eosio::name const & _owner,
        eosio::name const & _petname,
        uint64_t const _age,
        eosio::name const & _type) : id(_id), owner(_owner), petname(_petname), age(_age), type(_type)
        {  }

    uint64_t get_id() const { return id; }
    eosio::name get_owner() const { return owner; }
    eosio::name get_pet_name() const { return petname; }
    uint64_t get_age() const { return age; }
    eosio::name get_type() const { return type; }

    // this function needs to be included in every table
    //      - way data is organized and sorted
    uint64_t primary_key() const { return get_id(); }

//  Table Step 2.
//      create macro in public named EOSLIB
//                    class name,  data that should be saved in class
    EOSLIB_SERIALIZE( pet_t, (id)(owner)(petname)(age)(type) )
};

//  Table Step 3.
//      Create typedef
//                          name of table( _n means treat as eosio::name("pets") ),
//                          name of class which containts the data structure for our table
typedef eosio::multi_index <"pets"_n, pet_t> pets_table;

#endif //PET