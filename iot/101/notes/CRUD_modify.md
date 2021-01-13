.modify


valid args:
    modify( const T& obj, uint64_t payer, Lambda&& updater )


example:
    auto iter = proposals.find(proposal_id);

    // assert basically checks if iteration is at the end, meaning there is no value
    eosio_assert(iter != proposals.end(), "Could not find proposal");

    proposals.modify( iter, _self, [&]( auto& proposal){ proposal.description = "New value" } );

    // first line: retrieve iterator obj, which checks if the list is not at the end of the MI table (meaning there is no item)
    // then, pass the iterator obj into `modify`; second arg is `_self`; this reference is inherited from `eosio::contract` class, and stands for `account_name` who deployed the contract
    // lambda - get the obj reference for you to update


