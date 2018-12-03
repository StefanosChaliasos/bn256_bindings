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

/*
 * use template
 */
std::vector<std::string> serialize_G1(mcl::bn256::G1 elem) {
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

/*
 * Use templates for the next two functions.
 */
std::string serialize_mpz(mpz_class elem) {
    std::stringstream ss;
    ss << elem;
    return ss.str();
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

mcl::bn256::G1 deserialize_G1(std::vector<std::string> s_elem) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    // The first coordinate is 1 because we have affine coordinates
    std::string temp = "1 ";
    for (auto i = s_elem.begin(); i != s_elem.end(); ++i)
        temp += " " + *i;
    mcl::bn256::G1 result;
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


/*
 * Check if it's possible.
 */
mcl::bn256::G2 int_to_element(mcl::bn256::Fr integer) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 Q(mcl::bn256::Fp2(aa, ab), mcl::bn256::Fp2(ba, bb));
    mcl::bn256::G2 elem;
    mcl::bn256::G2::mul(elem, Q, integer);
    return elem;
}

std::map<std::string, int> create_table(long n)
{
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 Q(mcl::bn256::Fp2(aa, ab), mcl::bn256::Fp2(ba, bb));

    std::map<std::string, int> table;
    for(int i = 1; i <= n; i++) {
        mcl::bn256::G2 elem;
        mcl::bn256::G2::mul(elem,Q,i);
        elem.setIoMode(10);
        std::stringstream ss;
        ss << elem;
        std::string s = ss.str();
        std::string key = ss.str();
        table[key] = i;
    }
    return table;
}

mcl::bn256::Fr element_to_int(mcl::bn256::G2 elem, long n) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    // Pass the map as parameter
    std::map<std::string, int> table = create_table(n);
    // Make it function
    elem.setIoMode(10);
    std::stringstream ss;
    ss << elem;
    std::string elem_str = ss.str();
    std::string str = std::to_string(table[elem_str]);
    mcl::bn256::Fr integer = deserialize_Fr(str);
    return integer;
}

mcl::bn256::G2 get_random_element() {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 Q(mcl::bn256::Fp2(aa, ab), mcl::bn256::Fp2(ba, bb));
    // Random exponent
    mcl::bn256::Fr r;
    r.setRand(rg);
    // Random Element
    mcl::bn256::G2 RANDOM;
    mcl::bn256::G2::mul(RANDOM, Q, r);
    return RANDOM;
}

// add bls namespace

void Hash(mcl::bn256::G1& P, const std::string& m)
{
	mcl::bn256::Fp t;
	t.setHashOf(m);
	mcl::bn256::mapToG1(P, t);
}

void KeyGen(mcl::bn256::Fr& s, mcl::bn256::G2& pub, const mcl::bn256::G2& Q)
{
	s.setRand();
	mcl::bn256::G2::mul(pub, Q, s); // pub = sQ
}

void Sign(mcl::bn256::G1& sign, const mcl::bn256::Fr& s, const std::string& m)
{
	mcl::bn256::G1 Hm;
	Hash(Hm, m);
	mcl::bn256::G1::mul(sign, Hm, s); // sign = s H(m)
}

bool Verify(const mcl::bn256::G1& sign, const mcl::bn256::G2& Q,
            const mcl::bn256::G2& pub, const std::string& m)
{
	mcl::bn256::Fp12 e1, e2;
	mcl::bn256::G1 Hm;
	Hash(Hm, m);
	mcl::bn256::pairing(e1, sign, Q); // e1 = e(sign, Q)
	mcl::bn256::pairing(e2, Hm, pub); // e2 = e(Hm, sQ)
	return e1 == e2;
}

namespace bindings {

std::string get_modulus_serialized() {
    mcl::bn::initPairing(mcl::BN_SNARK1);
    std::string modulus = serialize_mpz(mcl::bn::BN::param.p);
    return modulus;
}

std::string get_order_serialized() {
    mcl::bn::initPairing(mcl::BN_SNARK1);
    std::string order = serialize_mpz(mcl::bn::BN::param.r);
    return order;
}

std::vector<std::string> get_generator_serialized() {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 Q(mcl::bn256::Fp2(aa, ab), mcl::bn256::Fp2(ba, bb));
    std::vector<std::string> g = serialize_G2(Q);
    return g;
}

bindings::S_keypair keygen_serialized() {
    Keypair keypair = keygen();
    bindings::S_keypair s_keypair = serialize_keypair(keypair);
    return s_keypair;
}

std::vector<std::string> int_to_element_serialized(std::string integer) {
    std::vector<std::string> serialized_elem;
    mcl::bn256::Fr Fr_integer = deserialize_Fr(integer);
    mcl::bn256::G2 elem;
    elem = int_to_element(Fr_integer);
    serialized_elem = serialize_G2(elem);
    return serialized_elem;
}

std::string element_to_int_serialized(std::vector<std::string> str_elem,
                                      long n) {
    mcl::bn256::G2 elem = deserialize_G2(str_elem);
    mcl::bn256::Fr Fr_integer = element_to_int(elem, n);
    std::string integer = serialize_Fr(Fr_integer);
    return integer;
}

bool is_valid_element_serialized(std::vector<std::string> str_elem) {
    mcl::bn256::G2 elem = deserialize_G2(str_elem);
    return elem.isValid();
}

std::vector<std::string> get_random_element_serialized() {
    mcl::bn256::G2 elem = get_random_element();
    std::vector<std::string> serialized_elem = serialize_G2(elem);
    return serialized_elem;
}

std::vector<std::string> mul_serialized(std::vector<std::string> element,
                                        std::string integer) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 Q(mcl::bn256::Fp2(aa, ab), mcl::bn256::Fp2(ba, bb));
    mcl::bn256::G2 elem = deserialize_G2(element);
    mcl::bn256::Fr fr = deserialize_Fr(integer);
    mcl::bn256::G2 result;
    mcl::bn256::G2::mul(result, elem, fr);
    return serialize_G2(result);
}

std::vector<std::string> add_serialized(std::vector<std::string> element,
                                        std::vector<std::string> addent) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 Q(mcl::bn256::Fp2(aa, ab), mcl::bn256::Fp2(ba, bb));
    mcl::bn256::G2 elem = deserialize_G2(element);
    mcl::bn256::G2 add = deserialize_G2(addent);
    mcl::bn256::G2 result;
    mcl::bn256::G2::add(result, elem, add);
    return serialize_G2(result);
}

bool is_equal_serialized(std::vector<std::string> element1,
                         std::vector<std::string> element2) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 elem1 = deserialize_G2(element1);
    mcl::bn256::G2 elem2 = deserialize_G2(element2);
    return (elem1 == elem2);
}

std::vector<std::string> inverse_serialized(std::vector<std::string> element) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mpz_class o = mcl::bn::BN::param.r;
    mpz_class o_ = o - 1;
    mcl::bn256::G2 elem = deserialize_G2(element);
    mcl::bn256::G2 inverse;
    mcl::bn256::G2::mul(inverse, elem, o_);
    return serialize_G2(inverse);
}

std::vector<std::string> bls_sign(std::vector<std::string> pk,
                                  std::string secret,
                                  std::string m) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 Q(mcl::bn256::Fp2(aa, ab), mcl::bn256::Fp2(ba, bb));
    mcl::bn256::Fr s = deserialize_Fr(secret);
    mcl::bn256::G2 pub = deserialize_G2(pk);
    mcl::bn256::G1 sign;
    Sign(sign, s, m);
    return serialize_G1(sign);
/*     std::cout << "sign " << sign << std::endl; */
    // std::vector<std::string> temp = serialize_G1(sign);
    // print_vector(temp);
    // mcl::bn256::G1 temp2 = deserialize_G1(temp);
    /* std::cout << "sign " << sign << std::endl; */
}

bool bls_verify(std::vector<std::string> sign, std::vector<std::string> pk,
                std::string m) {
    mcl::bn256::initPairing(mcl::bn::CurveSNARK1);
    mcl::bn256::G2 Q(mcl::bn256::Fp2(aa, ab), mcl::bn256::Fp2(ba, bb));
    mcl::bn256::G1 signature = deserialize_G1(sign);
    mcl::bn256::G2 pub = deserialize_G2(pk);
    return Verify(signature, Q, pub, m);
}

}

int main() {
    // std::cout << bindings::get_order_serialized() << std::endl;
    // std::cout << bindings::get_modulus_serialized() << std::endl;
    std::vector<std::string> a = bindings::int_to_element_serialized("10");
    std::vector<std::string> ran = bindings::get_random_element_serialized();

    // EQUALS CHECK
    mcl::bn256::G2 aa = get_random_element();
    mcl::bn256::G2 bb = aa;
    mcl::bn256::G2 cc = get_random_element();
    if (aa == bb) {
        std::cout << "OK" << std::endl;
    }


    mcl::bn::initPairing(mcl::BN_SNARK1);

    // ORDER CHECK
    // std::string o = serialize_mpz(mcl::bn::BN::param.r);
    mpz_class o = mcl::bn::BN::param.r;
    // std::cout << o;
    // mcl::bn256::Fr order = deserialize_Fr(o);
    mcl::bn256::G2 dd;
    mcl::bn256::G2 ee;
    mcl::bn256::G2::mul(dd, aa, o);
    mcl::bn256::G2::mul(ee, cc, o);

    if (dd == ee) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "OUPS" << std::endl;
    }

    // INVERSE CHECK
    mpz_class o_ = o - 1;

    mcl::bn256::G2 n1 = get_random_element();
    mcl::bn256::G2 n1_inverse;
    mcl::bn256::G2::mul(n1_inverse, n1, o_);

    mcl::bn256::G2 one;
    mcl::bn256::G2::add(one, n1_inverse, n1);

    if (one == dd) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "OUPS" << std::endl;
    }

    // std::cout << bindings::is_valid_element_serialized(a) << std::endl;
    // std::string b = bindings::element_to_int_serialized(a, 20);
    // Keypair keypair = keygen();
    // print_keypair(keypair);

    // BLS Check
    mcl::bn256::Fr r;
    r.setRand(rg);
    std::string secret = serialize_Fr(r);
    std::vector<std::string> pub = bindings::int_to_element_serialized(secret);
    std::string message = "Hello there !@$#@$EDWS";
    std::vector<std::string> sign = bindings::bls_sign(pub, secret, message);
    if (bindings::bls_verify(sign, pub, message)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "OUPS" << std::endl;
    }
}
