What is an action?


Explicit actions vs implicit (inline) actions:
    - Differ in the way they are executed by EOSIO
        - Both are defined in SC code. Key difference is that inline actions are not included in the actual transactions propagated through the network and eventually incluced in a block; they are implicit

    - explicit: present in a signed TX
        - Regular or explicit actions, as their name implies, are included in the actual list of actions that form a transaction
        - Explicit actions are encoded as action instances before being pushed into the transaction. Explicit actions also contain the actual payload data, if any, associated with the action to be executed as part of the transaction
    - implicit: created as a side effect of processing a TX
        - inline actions work within the same scope and permissions of the caller action. Therefore, inline actions are guaranteed to execute within the same transaction.

    - Implicit (inline) actions are also defined in smart contract code, just like explicit actions. The key difference is that inline actions are not included in the actual transactions propagated through the network and eventually included in a block; they are implicit.


Action vs transaction


What is a transaction receipt and what does it mean to receive it?
