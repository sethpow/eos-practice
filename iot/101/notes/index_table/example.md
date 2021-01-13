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