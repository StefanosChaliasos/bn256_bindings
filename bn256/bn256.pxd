from libcpp.string cimport string
from libcpp cimport bool
from libcpp.utility cimport pair
from libcpp.vector cimport vector


cdef extern from "bn256_functions.h" namespace "bindings":
    string get_modulus_serialized()

cdef extern from "bn256_functions.h" namespace "bindings":
    string get_order_serialized()

cdef extern from "bn256_functions.h" namespace "bindings":
    vector[string] get_generator_serialized()

cdef extern from "bn256_functions.h" namespace "bindings":
    pair[string, vector[string] ] keygen_serialized()

cdef extern from "bn256_functions.h" namespace "bindings":
    vector[string] int_to_element_serialized(string)

cdef extern from "bn256_functions.h" namespace "bindings":
    string element_to_int_serialized(vector[string], int)

cdef extern from "bn256_functions.h" namespace "bindings":
    bool is_valid_element_serialized(vector[string])

cdef extern from "bn256_functions.h" namespace "bindings":
    vector[string] get_random_element_serialized()

cdef extern from "bn256_functions.h" namespace "bindings":
    vector[string] mul_serialized(vector[string], string)

cdef extern from "bn256_functions.h" namespace "bindings":
    vector[string] add_serialized(vector[string], vector[string])

cdef extern from "bn256_functions.h" namespace "bindings":
    bool is_equal_serialized(vector[string], vector[string])

cdef extern from "bn256_functions.h" namespace "bindings":
    vector[string] inverse_serialized(vector[string])

cdef extern from "bn256_functions.h" namespace "bindings":
    vector[string] bls_sign(vector[string], string, string)

cdef extern from "bn256_functions.h" namespace "bindings":
    bool bls_verify(vector[string], vector[string], string)
