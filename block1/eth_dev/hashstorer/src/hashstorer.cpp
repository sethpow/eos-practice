#include <eosio/eosio.hpp>

CONTRACT hashstorer : public eosio::contract
{
public:
using contract::contract;

  // setup table structure
    // determines whats in a record, in our table
  TABLE hashschema
  {
    eosio::name user;
    std::string ipfs_hash;
    // PK function; returns the PK
      // need to write like:    primary_key()
    auto primary_key() const { return user.value; }
  };

  // setup/use table
              // table name, struct using,    type name
  typedef eosio::multi_index<"hashes"_n, hashschema> hashes_table;

  ACTION sethash (eosio::name user, std::string ipfs_hash)
  {
    // user submitting action; they must sign tx
    eosio::require_auth( user );

    /* instantiate the table
          calling table _hashes in this func
          pass in code (use own code in the contract that writes to table; this contract) & scope (int behind name)
    */
    hashes_table _hashes( get_self(), get_self().value );

    /* now we can do things with the table
          _hashes.emplace();    create record/places new record; 2 args - payer (account responsible for RAM cost), lambda func - 
          _hashes.modify();
          _hashes.erase();
          _hashes.find();       find a record
          _hashes.get();
    */
                            // lambda func args - row to modify; newrecord - abitrary name; how you refer to the row that you're changing inside lambda func
    _hashes.emplace( user, [&]( auto& newrecord ){
      newrecord.user = user;
      newrecord.ipfs_hash = ipfs_hash;
    });
  }

private:

};