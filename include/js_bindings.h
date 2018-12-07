/*
 * js_bindigs.h
 * Copyright (C) 2018 Stefanos Chaliasos <schaliasos@protonmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef JS_BINDIGS_H
#define JS_BINDIGS_H

#include <string>
#include <vector>

namespace js {

    std::vector<std::string> keygen();

    std::vector<std::string> int_to_element(std::string message);

    std::vector<std::string> encrypt(std::vector<std::string> pub,
                                     std::vector<std::string> message);
}

#endif /* !JS_BINDIGS_H */
