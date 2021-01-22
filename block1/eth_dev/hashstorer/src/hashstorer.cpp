#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>	// for asset & symbol

CONTRACT hashstorer : public eosio::contract
{
public:
using contract::contract;

	// constructor
	hashstorer( eosio::name receiver, eosio::name code, eosio::datastream<const char *> ds )
		:contract( receiver, code, ds ),	// extending contract; passing up chain to contract
		staketoken_symbol( "SYS", 4 )		// set stake const; can be used throughout our contract
		// hashes_table _hashes( get_self(), get_self().value );	// instantiate permanent things; setup hashes table
	{

	}

	// setup table structure
	// determines whats in a record, in our table
	TABLE hashschema
	{
		eosio::name user;
		std::string ipfs_hash;
		// dont need eosio::asset; dont need to store symbol in memory; save RAM costs by only storing amount
			// remember to pass in the amount member of our asset stake, not just pass in whole asset
		int64_t stakeamount;

		// PK function; returns the PK
		// need to write like:    primary_key()
		auto primary_key() const { return user.value; }
	};

	// setup/use table
				// table name, struct using,    type name
	typedef eosio::multi_index<"hashes"_n, hashschema> hashes_table;

	// cannot remain ACTION; allows anyone to call it (only want incoming transfers to notify it)
	[[eosio::on_notify( "eosio.token::transfer" )]]	// governing contract acc, and relevent action
	// transfer() - 4 args: name from, name to, asset quantity, string memo
		// sethash will receive those same args
	void sethash (eosio::name user, eosio::name recipient, eosio::asset stake, std::string ipfs_hash)
	{
		/* No longer needed - since person owning tokens authorized the transfer; otherwise this notification hasnt come thru to us
		// user submitting action; they must sign tx
		eosio::require_auth( user );
		*/

		// run simple checks on transfer
		eosio::check( user != get_self() && recipient == get_self(), "You can't send to yourself." );
		eosio::check( stake.amount > 0, "Staked amount must be more than 0." );
		eosio::check( stake.symbol == staketoken_symbol, "Must be SYS with precision 4" );

		// verify that hash is a valid hash
		// sanitize/clean it up
		// pass in stake balance to be stored

		update_hash( user, stake.amount, ipfs_hash );
	}

private:
	const eosio::symbol staketoken_symbol;

	// update hash and store in table
	void update_hash( eosio::name user, int64_t stake_amount, std::string ipfs_hash )
	{
		/* instantiate the table
          calling table _hashes in this func
          pass in code (use own code in the contract that writes to table; this contract) & scope (int behind name)
		
				DONE IN CONSTRUCTOR
		*/
		hashes_table _hashes( get_self(), get_self().value );

		/* now we can do things with the table
			_hashes.emplace();    create record/places new record; 2 args - payer (account responsible for RAM cost), lambda func - 
			_hashes.modify();
			_hashes.erase();
			_hashes.find();       find a record
			_hashes.get();
		*/

		// find if record exists first(by PK); modify if does, add if doesnt
			// itr - points to position in table; end is row after table (doesnt exist)
		auto hash_itr = _hashes.find( user.value );
		if( hash_itr == _hashes.end() )
		{
		// lambda func args - row to modify; newrecord - abitrary name; how you refer to the row that you're changing inside lambda func
		_hashes.emplace( user, [&]( auto& newrecord ){
			newrecord.user = user;
			newrecord.ipfs_hash = ipfs_hash;
			newrecord.stakeamount = stake_amount;
		});
		} else
		{
		// args- itr pointing to row to modify, payer of RAM, lambda
		_hashes.modify( hash_itr, user, [&]( auto& record_to_modify ){
			record_to_modify.ipfs_hash = ipfs_hash;
			record_to_modify.stakeamount += stake_amount;
		});
		}
	}

};