Accounts & Keys
----------------
    - 12 characters long
    - Keeps track of balance, TX's, tokens, resources
    - Creation of account can only be done by an already existing account
    - Accounts consist of key pairs
        - Private and public keys

    - One account has 2 (minimum) key pairs
        - Owner and active
        - Each key pair has 2 keys, public and private
        - Owner has ALL permissions; controls your account
            - Used mainly to create/deactivate keys
            - Advised to keep in cold storage
        - Active key; daily use
            - Can do everything owner can, EXCEPT invalidate/create keys
            - Use when interacting with dApps, send TX's, etc...

             Account
            /       \
           /         \
       Owner         Active
      /     \        /    \
    Pub    Priv    Pub   Priv