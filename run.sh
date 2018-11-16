#! /bin/sh
#
# run.sh
# Copyright (C) 2018 Stefanos Chaliasos <schaliasos@protonmail.com>
#
# Distributed under terms of the MIT license.
#


c++ -I/usr/local/opt/openssl/include -I/usr/local/opt/gmp/include -g3 -Wall -Wextra -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings -Wfloat-equal -Wpointer-arith -m64 -I mcl/include -I include -fomit-frame-pointer -DNDEBUG -O3 -march=native  -fPIC -DMCL_USE_LLVM=1 -c src/bn256_functions.cpp -o obj/bn256_functions.o -MMD -MP -MF obj/bn256_functions.d && \
    c++ obj/bn256_functions.o -o bin/bn_256_functions mcl/lib/libmcl.a -L/usr/local/opt/openssl/lib -L/usr/local/opt/gmp/lib -lgmp -lgmpxx -lcrypto -m64 && \
    ./bin/bn_256_functions
