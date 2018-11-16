/*
 * bn256_functions.cpp
 * Copyright (C) 2018 Stefanos Chaliasos <schaliasos@protonmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BN256_FUNCTIONS_H
#define BN256_FUNCTIONS_H

#include <string>
#include <mcl/bn256.hpp>

namespace bindings {

using S_keypair = std::pair<std::string, std::vector<std::string> >;

std::string get_modulus_serialized();

std::string get_order_serialized();

std::vector<std::string> get_generator_serialized();

S_keypair keygen_serialized();

std::vector<std::string> int_to_element_serialized(std::string integer);

std::string element_to_int_serialized(std::vector<std::string> str_elem,
                                      long n);

bool is_valid_element_serialized(std::vector<std::string> str_elem);

std::vector<std::string> get_random_element_serialized();

std::vector<std::string> mul_serialized(std::vector<std::string> element,
                                        std::string integer);

std::vector<std::string> add_serialized(std::vector<std::string> element,
                                        std::vector<std::string> addent);

}


#endif /* !BN256_FUNCTIONS_H */
