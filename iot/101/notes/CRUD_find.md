find/retrieve

to retrieve a record by its PK:
    auto itr = proposals.find(proposal_id)

    // find() simply runs the std::find_if function that checks if the looped item has the correct PK
    ptr._item->primary_key() == input_primary

returns an iterator that has a queried result item cached privaately
    this iterator gives some useful features to walk thru the table

    the iterator on itself can return the currect obj by obj dereference or obj instance
        print(eosioitr->property)   // reference
        print((*itr).property)      // instance

        Proposal proposal = *itr    // get obj instance




Next/Previous objects
The iterator on itself can then be iterated thru to retrieve the next or prev obj inside the DB.
    This is useful during iteration thru objects in the table

    auto nextitr = itr++
    auto previtr = itr--
