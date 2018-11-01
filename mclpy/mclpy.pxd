from libcpp.string cimport string
from libcpp.utility cimport pair
from libcpp.vector cimport vector


cdef extern from "bn256_functions.h" namespace "bindings":
    pair[string, vector[string] ] keygen_serialized()
