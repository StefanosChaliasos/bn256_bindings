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

S_keypair keygen_serialized();

}

#endif /* !BN256_FUNCTIONS_H */
