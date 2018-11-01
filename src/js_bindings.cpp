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

}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("keygen", &js::keygen);
}

EMSCRIPTEN_BINDINGS(stl_wrappers) {
    emscripten::register_vector<std::string>("Keypair");
}
