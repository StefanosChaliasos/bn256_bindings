/*
 * js_bindings.cpp
 * Copyright (C) 2018 Stefanos Chaliasos <schaliasos@protonmail.com>
 *
 * https://github.com/zandaqo/iswasmfast/blob/master/src/wasm.cpp
 * Distributed under terms of the MIT license.
 */

#include <js_bindings.h>
#include <bn256_functions.h>
#include <emscripten/bind.h>

namespace js {

    /*
     * We need this function because emscripten doesn't support pairs.
     * @return A vector of strings where the first string is the secret key
     *         and the others are the public key
     */
    std::vector<std::string> keygen() {
        bindings::S_keypair keypair = bindings::keygen_serialized();
        std::vector<std::string> result = keypair.second;
        result.insert(result.begin(), keypair.first);
        std::vector<std::string> proofs =
            bindings::prove_key(keypair.second, keypair.first);
        result.insert(result.end(), proofs.begin(), proofs.end());
        return result;
    }

    /*
     * Convert integer to G2 element
     * @return A vector of string that contains the coordinates of G2.
     */
    std::vector<std::string> int_to_element(std::string message) {
        std::vector<std::string> mes =
            bindings::int_to_element_serialized(message);
        return mes;
    }

    /*
     * Encrypt message.
     * @return A vector of strings that contains aplha, beta and secret.
     */
    std::vector<std::string> encrypt(std::vector<std::string> pub,
                                     std::vector<std::string> message) {
        std::vector<std::string> encrypted = bindings::encrypt(message, pub);
        return encrypted;
    }

    /*
     * Prove encryption.
     * @return A vector of strings that contains
     *      commitment, challenge, response.
     */
    std::vector<std::string> prove_encryption(std::vector<std::string> alpha,
                                              std::vector<std::string> beta,
                                              std::string secret) {
        std::vector<std::string> proofs = bindings::prove_encryption(alpha,
                                                                     beta,
                                                                     secret);
        return proofs;
    }

    /*
     * Compute decryption factors for a ciphertext.
     * @return A vector of string that contains
     *      data,
     *      base_commitment, message_commitment, challenge, response (proof).
     */
    std::vector<std::string> compute_decryption_factor(
            std::vector<std::string> alpha,
            std::string secret) {
        std::vector<std::string> results =
            bindings::compute_decryption_factor(alpha, secret);
        return results;
    }
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("keygen", &js::keygen);
    emscripten::function("int_to_element", &js::int_to_element);
    emscripten::function("encrypt", &js::encrypt);
    emscripten::function("prove_encryption", &js::prove_encryption);
    emscripten::function("compute_decryption_factor",
            &js::compute_decryption_factor);
}

EMSCRIPTEN_BINDINGS(stl_wrappers) {
    emscripten::register_vector<std::string>("Vector");
    // emscripten::register_vector<std::string>("Encrypted");
    // emscripten::register_vector<std::string>("Public");
    // emscripten::register_vector<std::string>("G2");
}
