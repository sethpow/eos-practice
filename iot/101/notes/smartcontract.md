In EOSIO, smart contracts consist of a set of actions, usually grouped by functionality, and a set of type definitions which those actions depend on. Therefore, actions specify and define the actual behaviors of the contract. Several actions are implemented in the standard EOSIO contracts for account creation, producer voting, token operations, etc. Application developers can extend, replace, or disable this functionality altogether by creating custom actions within their own smart contracts and applications. Transactions, on the other hand, are typically created at the application level. Smart contracts are agnostic to them.

An EOSIO smart contract is implemented as a C++ class that derives from eosio::contract. Actions are implemented as C++ methods within the derived class. Transactions, on the other hand, are generated dynamically (as transaction instances) within an EOSIO application. The EOSIO software processes each transaction instance and keeps track of its state as it evolves from creation, signing, validation, and execution.
