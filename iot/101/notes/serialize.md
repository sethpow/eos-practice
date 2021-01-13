EOSLIB_SERIALIZE( <StructName>, (field1)(field2)(field3) )

in: contracts/eosiolib/serialize.hpp
    - it is using `BOOST_PP_SEQ_FOR_EACH`

gives the struct extra operators for the serialization and deserialization of data to and from the multi_index table