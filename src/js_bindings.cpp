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
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("keygen", &js::keygen);
    emscripten::function("int_to_element", &js::int_to_element);
    emscripten::function("encrypt", &js::encrypt);
}

EMSCRIPTEN_BINDINGS(stl_wrappers) {
    emscripten::register_vector<std::string>("Vector");
    // emscripten::register_vector<std::string>("Encrypted");
    // emscripten::register_vector<std::string>("Public");
    // emscripten::register_vector<std::string>("G2");
}
