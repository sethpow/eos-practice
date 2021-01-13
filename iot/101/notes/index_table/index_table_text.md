https://medium.com/fueled-engineering/exploring-the-eos-multi-index-database-557769b1b7a6

https://www.youtube.com/watch?v=E3Tx2DseLGE&feature=emb_title

The EOS platform is still pretty new, we have been trying to find any information on the EOS platform, let alone specifically on the Database API the EOS platform provides.
For now we have only found this video tutorial and API reference to be the most insightful, but other then that it has been quite sparse.
This gave us, Fueled, the task and opportunity to just figure it out by digging through the actual EOS source code. We laid out what we have figured out by reading, so that you don’t need to (hopefully). I personally do not guarantee that everything in this article is completely correct or is still valid as EOS development is ongoing, but this might give you a better view about the EOS database and the features it has.
The EOS software uses smart contracts itself to persist data about RAM Usage and has some good examples you can use, we’ve been going through all of them reading line by line and here’s our first result, our introduction into the EOS database.
Intro into the EOS database
The EOS database is a special feature that enables you to store indexed data into the blockchain, formatted inside defined data structures. Having the database on the blockchain does not mean everyone has right to do write/read on this database. The EOS database is basically build into multiple layers, as it is described in contracts/eosiolib/db.h has a simple idea:

 * EOS.IO organizes data according to the following broad structure:
 *
 * — **code** — the account name which has write permission
 *    — **scope** — an account where the data is stored
 *       — **table** — a name for the table that is being stored
 *          — **record** — a row in the table
There are some terms used that are different then you heard before, here I laid out what these terms mean.
- codeis a number that correspondents to your contract code. You might have seen it before with building out smart contracts on EOS, it is the “identifier” of the smart contract.
-scopeBecause the contract can be deployed multiple times the contract identifier is not suffice. The scope can be anything, but usually it is the account identifier which it is deployed with.
- table The name of the table.
- recordHopefully that speaks for itself.
Structuring your tables
The EOS database tables can be formatted by struct data type, in these structures you are able to define the naming and type definition of your properties of that table.
Let’s look at an example:

So let’s go through parts of the code and highlight some of the requirements EOS has defined.
ABI Annotations

// @abi table proposal i64
For deploying your contract, you will run the code through the eosiocpp command, the EOS Smart Contract compiler is able to read out the comments above your struct and public functions. there are 2 types you can past; action and table, which speaks for itself. This comment annotation gets fished out by the abi generator (located in libraries/abi_generator/abi_generator.cpp#201) to add this method or table definition into the ABI output.
The second argument i.e. “proposal” which gives you an option for a different table name. The last one is to define a type of table you want to use, for now it seems like there is only a version for i64, which stands for a 64 bit indexed table.
Other types you can pass by are str for querying by string. i64, i64i64i64 and i128i128, all refer the type of the integer primary_key, which basically increases the amount of possible index numbers.
Account owner type defintion
account_name owner = 0
The EOSIO package comes with a custom type definition for storing the account name reference, this is the account you create on your own local EOS wallet.
This is a custom type definition included in the EOS platform. As much as it looks custom, it is really just stored as a uint64_int .
Lists in your table
You can persist vector objects inside your table definition. This means that you can easily create simple sub collections in your schemas.
In this example we have a vector mapping of voter (account_name) and weight of vote (uint32_t).
std::vector<account_name, uint32_t> votes;
Primary Keys
uint64_t primary_key() const { return id; }

The eosio::multi_index class requires your data structure to return a primary key for your row. This is required and can be done by creating a primary_key() method on your struct. This example shows us casting it to a uint64_t, but this can also be account_name which, in its turn is a uint64_t in disguise.
DataStream Seralization
EOSLIB_SERIALIZE( <StructName>, (field1)(field2)(field3))

I was always wondering what this specifically meant in the EOS Contract Examples. Knowing it was definitely a macro I started to go through the code and get to know the system better. By digging deep, I came to read through the contracts/eosiolib/serialize.hpp and found that it was using the `BOOST_PP_SEQ_FOR_EACH` macro (here is what it does). It basically gives the struct extra operators for the serialization and deserialization of data to and from the multi_index database.
Querying, Modifying and Creating
The EOS Multi Index database comes with some functionality to retrieve back the information. Although the features are not as extensive as something like a SQL Query, but it does its basics:
- Querying an entry with .find
- Creating new entries with .emplace
- Modifying existing entries with .modify
Retrieving items
For retrieving a record by its primary key we simply run:
auto itr = proposals.find(proposal_id)
Which returns back you a iterator that has queried result item cached privately. This iterator gives you some quite useful features to walk through the table. Going through multi_index inside EOS we can see that it has a couple of nifty operator methods:
The iterator on itself can return the current object by object dereference or as object instance:
print(eosioitr->property) // reference
print((*itr).property) // instance
Proposal proposal = *itr // get object instance
Next and previous objects
The iterator on itself can then be iterated through to retrieve the next or previous object inside the database. This can be useful during iteration through objects in that table.
auto nextitr = itr++;
auto previtr = itr--;
Under the hood. For me to understand a subject, it really helps for me to understand the underlying functionality, and it usually also reveals the simplicity of it. This is also the case with EOS, upon digging through code, the .find() method simply runs the std::find_if functionality that checks if the looped item has the correct primary key:
ptr._item->primary_key() == input_primary
Modifying items
To modify an object you can use the .modify method, the arguments this method accepts are:
modify( const T& obj, uint64_t payer, Lambda&& updater )
An example could be:
auto iter = proposals.find(proposal_id);
// assert basically checks if iteration is at the end, meaning there is
// no value
eosio_assert(iter != proposals.end(), “Could not find proposal”);
proposals.modify( iter, _self, [&]( auto& proposal) {
 proposal.description = “New value”
});
Our first line we retrieve back the iterator object, which then is checked if the list isn’t at the end of the multi_index table, meaning there is no item.
After that we pass this iterator object into our modify call, the second argument is then _self. This reference is inherited from the eosio::contract class, and stands for the account_name who deployed this contract.
As you can see the modify method second argument is a lambda function where you will get the object reference for you to update.
Creating new items
In order for your to create a new item, you can use the .emplace method coming from the multi_index class. The following arguments are used:
emplace( uint64_t payer, Lambda&& constructor )
As you can see the first argument is again a payer reference. Every interaction with EOS, just like with ETH transaction there is somebody responsible for “paying” for storage, we’ll go over this in a upcoming article.
An example insertion could be:
auto new_proposal = proposals.emplace( _self, [&]( auto& proposal) {
 proposal.id = proposals.available_primary_key();
 proposal.owner = sender;
 proposal.description = description;
});
Putting it all together
To put it all in one contract, it would look something like this:
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using namespace std;

class ballot : public contract {
  using contract::contract;

  public:
      ballot( account_name self ) :
        contract(self),
        members(_self, _self),
        proposals(_self, _self)
        {}

      /**
       * Add a member to the democracy, can only be done by the contracts owner
       */
      //@abi action
      void addmember( account_name granter, account_name account ) {
        // ...
      }

      // @abi action
      void propose( account_name sender, string description ){
        // ...
      }

      /**
       * Vote for a specific ballot
       */
      //@abi action
      void vote( account_name account, uint64_t proposal_id ) {
        //...
      }

    private:

    	//@abi table member i64
      struct Member {
        account_name owner;
        uint64_t weight;
        account_name granter;
        bool invite_permission = false;

        account_name primary_key() const { return owner; }

        EOSLIB_SERIALIZE( Member, (owner)(weight))
      };

   		//@abi table proposal i64
      struct Proposal {
        uint64_t id;
        account_name owner = 0;
        string description;
        std::vector<account_name, uint32_t> votes;

        uint64_t primary_key() const { return id; }

        EOSLIB_SERIALIZE( Proposal, (id)(owner)(description)(votes))
      };

       /**
       * Requires the account to be a member, returns the member struct
       */
      Member retrieve_member( account_name voter) {
        auto iter = members.find(voter);
        eosio_assert(iter != members.end(), "Account is not a member of this democracy");

        return *iter;
      }

      Member create_member( account_name granter, account_name owner, int32_t weight, bool invite_permission) {
        auto new_member = members.emplace(_self, [&]( auto& member) {
          member.owner = owner;
          member.weight = weight;
          member.granter = granter;
          member.invite_permission = invite_permission;
        });

        return *new_member;
      }


      multi_index<N(Proposal), Proposal> proposals;
      multi_index<N(Member), Member> members;
};

EOSIO_ABI( ballot, (propose)(vote)(addmember) )




We will continue with the Ballot voting example in upcoming posts to continue advancing in the EOS endeavor.
Update:
As pointed out to me from other readers, they wanted to share their resources they have been working with, here are some resources to continue learnings:
Check out this video on EOS development: