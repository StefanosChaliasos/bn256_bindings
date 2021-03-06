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

void print_vector(std::vector<std::string> v);

std::string get_modulus_serialized();

std::string get_order_serialized();

std::vector<std::string> get_generator_serialized();

S_keypair keygen_serialized();

std::vector<std::string> prove_key(std::vector<std::string> pk,
                                   std::string secret);

std::vector<std::string> int_to_element_serialized(std::string integer);

std::string element_to_int_serialized(std::vector<std::string> str_elem,
                                      long n);

bool is_valid_element_serialized(std::vector<std::string> str_elem);

std::vector<std::string> get_random_element_serialized();

std::vector<std::string> mul_serialized(std::vector<std::string> element,
                                        std::string integer);

std::vector<std::string> add_serialized(std::vector<std::string> element,
                                        std::vector<std::string> addent);

bool is_equal_serialized(std::vector<std::string> elem1,
                         std::vector<std::string> elem2);

std::vector<std::string> inverse_serialized(std::vector<std::string> element);

std::vector<std::string> bls_sign(std::vector<std::string> pk,
                                  std::string secret,
                                  std::string message);

bool bls_verify(std::vector<std::string> sign, std::vector<std::string> pk,
                std::string m);

std::vector<std::string> encrypt(std::vector<std::string> message,
                                 std::vector<std::string> pub);

std::string integer_from_elements_hash_s(std::vector<std::string> elements);

std::vector<std::string> prove_encryption(std::vector<std::string> alpha,
                                          std::vector<std::string> beta,
                                          std::string secret);

std::vector<std::string> compute_decryption_factor(
        std::vector<std::string> alpha,
        std::string secret);
}


#endif /* !BN256_FUNCTIONS_H */
