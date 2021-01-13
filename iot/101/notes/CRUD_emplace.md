create new item

use .emplace method coming from the Multi index class
- args
    emplace( uint64_t payer, Lambda&& constructor )

    // payer - `_self`; this reference is inherited from `eosio::contract` class, and stands for `account_name` who deployed the contract


example:

auto new_proposal = proposals.emplace( _self, [&](){
    proposal.id = proposals.available_primary_key();
    proposal.owner = sender;
    proposal.description = description;
});