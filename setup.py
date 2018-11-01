#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 Stefanos Chaliasos <schaliasos@protonmail.com>
#
# Distributed under terms of the MIT license.

from distutils.core import setup
from distutils.sysconfig import get_python_lib
from distutils.extension import Extension
from Cython.Distutils import build_ext
import os

os.environ['CC'] = 'c++'
os.environ['CXX'] = 'c++'

#  major = str(sys.version_info.major)
#  minor = str(sys.version_info.minor)

#  ROOT_PATH = os.path.dirname(os.path.abspath(__file__))
#  VERSION = 'python' + major + '.' + minor
#  LIB_PATH = get_python_lib()

ext_modules = [Extension("mclpy",
                         sources=["mclpy/mclpy.pyx",
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
                         extra_compile_args=['-std=c++17', '-g3', '-Wall',
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

setup(cmdclass = {'build_ext': build_ext}, ext_modules = ext_modules)
