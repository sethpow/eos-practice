*** CREATE: WALLETS, KEYS, & ACCOUNTS
cleos create key --to-console
cleos wallet import         (enter private key generated ^^)

    -------------
    After you have imported your first keypair to your wallet, you need to add the eosio account. You do this by running: cleos wallet import. It will query you for a key, enter the EOSIO private key. 
    -------------


    -------------
    **  cleos create account <account paying for creation of account> <account name> <pub key for owner permission> <public key for active permission>

    cleos create account eosio account1 owner_permission_pub_key active_permission_pub_key
    -------------

cleos get account <account name>



*** COMMAND LINE ACTION
Compilation

Compilation is done with eosio-cpp. The general command we will use looks like this. The output will be a web assembly file (.wasm) and an abi file (.abi). This should be executed while standing in your project directory:
    eosio-cpp -abigen -o <OUTPUT> <SOURCE FILE>

The -abigen flag tells eosio-cpp to generate an abi file. Which will be used in deployment together will the web assembly file. -o let's us specify an output directory.

IoT
An example of this command in action looks like this:
    eosio-cpp -abigen -o dogcontract.wasm src/dogcontract.cpp

Block 1
    eosio-cpp -abigen ./src/ordercontrct.cpp -o ./ordercontrct.wasm
_________________________________________________________________________


Deployment

After compilation we can use our .wasm and .abi files to deploy our contract. To do this we need to use cleos. We use the "set contract" command to deploy code in eos. The general command we will use looks like this:
    cleos set contract <ACCOUNT> <CONTRACT-DIR> <WASM-FILE> --abi <ABI-FILE> -p <ACCOUNT>@<PERMISSION>

Where the <ACCOUNT> is the account we are setting the contract to. <CONTRACT DIR> is where you need to put the absolute path to your contract directory. The path you copied after running "pwd" in your terminal. An example of this command in action looks like this:
    cleos set contract dogcontract /Users/admin/Documents/eos-contracts/course-payable ./dogcontract.wasm --abi dogcontract.abi -p dogcontract@active

Block 1
    cleos set contract ordercontrct .
_________________________________________________________________________


Sending Actions to Contracts

After deployment we can execute our code by sending actions to the account where our contract is deployed. This is also done with cleos. The general command we will use looks like this:
    cleos push action <CONTRACT-ACCOUNT> <ACTION-NAME> <ARGUMENTS> -p <ACCOUNT>@<PERMISSION>

An example of this command in action looks like this. Take a close look at how arguments are sent. They are sent as an array with the arguments in order. The entire array should always be wrapped in single quotes:
    cleos push action dogcontract insert '["bob", "doggo", 100]' -p bob@active
_________________________________________________________________________


Getting Table Rows

We can fetch data from a table using cleos as well. The general command looks like this.
    cleos get table <ACCOUNT> <SCOPE> <TABLE-NAME>

An example would be:
    cleos get table bob bob dogs
_________________________________________________________________________


Get ABI
    cleos get abi <ordercontrct>
_________________________________________________________________________


Get table
                     account        scope
    cleos get table <ordercontrct> <ordercontrct> orders
_________________________________________________________________________


Push actions
                       contract      action       data                                               permission
cleos push action <ordercontrct> <addorder> '{"userid": 0, "items": [2, 23], "status": "returned"}' -p ordercontrct@active