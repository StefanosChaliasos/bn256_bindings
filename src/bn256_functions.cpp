/*
 * bn256_functions.cpp
 * Copyright (C) 2018 Stefanos Chaliasos <schaliasos@protonmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <bn256_functions.h>
#include <iostream>
#include <cybozu/random_generator.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <mcl/bn256.hpp>
#include <cybozu/option.hpp>

static cybozu::RandomGenerator rg;

using Keypair = std::pair<mcl::bn256::Fr, mcl::bn256::G2>;
using Ciphertext = std::pair<mcl::bn256::G2, mcl::bn256::G2>;
using S_ciphertext = std::pair<std::vector<std::string>,
                               std::vector<std::string> >;
using Encrypted = std::pair<Ciphertext, mcl::bn256::Fr>;

const char *aa =
    "15267802884793550383558706039165621050290089775961208824303765753922461897946";
const char *ab =
    "9034493566019742339402378670461897774509967669562610788113215988055021632533";
const char *ba =
    "644888581738283025171396578091639672120333224302184904896215738366765861164";
const char *bb =
    "20532875081203448695448744255224543661959516361327385779878476709582931298750";

/**
 * Serialize G2 element to a vector with affine cordinates/
 *
 * \param elem G2 element.
 * \result result Vector of strings.
 */
std::vector<std::string> serialize_G2(mcl::bn256::G2 elem) {
    // Set affine representation
    elem.setIoMode(10);
    std::stringstream ss;
    ss << elem;
    std::string string_elem = ss.str();
    std::vector<std::string> result;
    std::string coordinate;
    std::istringstream coordinateStream(string_elem);
    while (std::getline(coordinateStream, coordinate, ' ')) {
        result.push_back(coordinate);
    }
    // Remove first coordinate which always is 1
    result.erase(result.begin());
    return result;
}

std::string serialize_Fr(mcl::bn256::Fr elem) {
    std::stringstream ss;
    ss << elem;
    return ss.str();
}

mcl::bn256::G2 deserialize_G2(std::vector<std::string> s_elem) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 Q(mcl::bn256::Fp2(aa, ab), mcl::bn256::Fp2(ba, bb));
    // The first coordinate is 1 because we have affine coordinates
    std::string temp = "1 ";
    for (auto i = s_elem.begin(); i != s_elem.end(); ++i)
        temp += " " + *i;
    mcl::bn256::G2 result;
    std::stringstream ssresult;
    ssresult.str(temp);
    ssresult >> result;
    return result;
}

mcl::bn256::Fr deserialize_Fr(std::string s_elem) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::Fr result;
    std::stringstream sss_elem;
    sss_elem.str(s_elem);
    sss_elem >> result;
    return result;
}

bindings::S_keypair serialize_keypair(Keypair keypair) {
    std::string sk = serialize_Fr(keypair.first);
    std::vector<std::string> pk = serialize_G2(keypair.second);
    return std::make_pair(sk, pk);
}

void print_vector(std::vector<std::string> v) {
    for (auto i = v.begin(); i != v.end(); ++i)
        std::cout << *i << std::endl;
}

void print_keypair(Keypair keypair) {
    bindings::S_keypair serialized = serialize_keypair(keypair);
    // Secret Key
    std::cout << "Secret Key" << std::endl;
    std::cout << serialized.first << std::endl;
    // Public Key
    std::cout << "Public Key" << std::endl;
    print_vector(serialized.second);
}

Keypair keygen() {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 Q(mcl::bn256::Fp2(aa, ab), mcl::bn256::Fp2(ba, bb));
    // secret key
    mcl::bn256::Fr s;
    s.setRand(rg);
    // public key
    mcl::bn256::G2 PK;
    mcl::bn256::G2::mul(PK, Q, s);
    return std::make_pair(s, PK);
}

namespace bindings {

bindings::S_keypair keygen_serialized() {
    Keypair keypair = keygen();
    bindings::S_keypair s_keypair = serialize_keypair(keypair);
    return s_keypair;
}

}

/* int main() { */
    // Keypair keypair = keygen();
    // print_keypair(keypair);
/* } */
