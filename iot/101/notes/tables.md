persistant storage
    persist data across multiple actions
    stores and saves data, even when smart contract is not being used

basis for EOS Tables are C++ struct's
    - uses primary key for lookups

struct {
    int id;         assign PK to the id
    std::string name;
    int age;
}

table example:
    People
___________________
|id  |name  |age  |
|=================|
|0   |pete  |25   |
|1   |seth  |27   |
|_________________|

once table is defined, there is no way we can change it
can insert, modify, or delete data


Scopes
----------
table   acc    scope
people(people, people)              global scope
people(people, male/female)         group scope
people(people, EOS acc name)        individual scope