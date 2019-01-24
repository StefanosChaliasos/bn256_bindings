#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 Stefanos Chaliasos <schaliasos@protonmail.com>
#
# Distributed under terms of the MIT license.

from setuptools import setup, find_packages
from setuptools.extension import Extension
from Cython.Build import cythonize
import os

os.environ['CC'] = 'c++'
os.environ['CXX'] = 'c++'

ext_modules = [Extension("bn256",
                         sources=["bn256/bn256.pyx",
                                  "src/bn256_functions.cpp"],
                         include_dirs=['include',
                                       '/usr/local/opt/openssl/include',
                                       '/usr/local/opt/gmp/include',
                                       'mcl/include'],
                         libraries=['mcl'],
                         library_dirs=['mcl/lib/',
                                       '/usr/local/opt/openssl/lib',
                                       '/usr/local/opt/gmp/lib'],
                         language="c++",
                         extra_compile_args=['-std=c++11', '-g3', '-Wall',
                                             '-Wextra', '-Wformat=2',
                                             '-Wcast-qual', '-Wcast-align',
                                             '-Wwrite-strings', '-Wfloat-equal',
                                             '-Wpointer-arith', '-m64',
                                             '-fomit-frame-pointer', '-DNDEBUG',
                                             '-O3', '-march=native', '-fPIC',
                                             '-DMCL_USE_LLVM=1',
                                             ],
                        extra_link_args=['-lgmp', '-lgmpxx', '-lcrypto', '-m64']
                        )
              ]

setup(
    name = "bn256",
    packages = [],
    ext_modules = cythonize(ext_modules)
)
