#!/usr/bin/env python3

###################################################################################################

from conans import CMake
from conans import ConanFile
from conans import tools

###################################################################################################

from pathlib import Path

###################################################################################################

class NanosslPackage(ConanFile):

    ###############################################################################################

    # attributes used by the Conan SDK

    ###############################################################################################

    author = 'theohax <theo@nano.org>'

    build_requires = ['gtest/1.11.0']

    default_options = {'shared': False,
                       'gtest:build_gmock': False,
                       'gtest:no_main': False,
                       '*:fPIC': True,
                       '*:shared': True}

    description = 'Modern C++ library, part of nanocurrency ecosystem, ' \
                  'that offers powerful cryptography, PKI & SSL abstractions'

    generators = ['cmake']

    homepage = 'https://nano.org'

    license = 'BSD 3-Clause'

    name = 'nanossl'

    options = {'shared': [True, False]}

    requires = ['openssl/1.1.1q',
                'spimpl/1.2-1']

    settings = ['os', 'compiler', 'build_type', 'arch']

    topics = ('nano', 'xno', 'ssl')

    url = 'https://github.com/theohax/nano-conan-recipes'

    version = '0.1-1'

    ###############################################################################################

    # attributes used by the recipe itself

    ###############################################################################################

    _build_subfolder = 'build'

    _cmake = None

    _repository_name = 'nano-ssl'

    _repository_revision = 'v{}'.format(version.rpartition('-')[0])

    _repository_url = 'https://github.com/theohax/{}.git'.format(_repository_name)

    ###############################################################################################

    # methods used by the Conan SDK

    ###############################################################################################

    def build(self):
        cmake = self._get_cmake()
        cmake.build()

    ###############################################################################################

    def imports(self):
        self.copy('libgtest*.*.dylib*', 'bin', '@libdirs')
        self.copy('libgtest*.*.so*', 'lib', '@libdirs')
        self.copy('libcrypto.*.*', 'lib', '@libdirs')
        self.copy('libssl.*.*', 'lib', '@libdirs')

    ###############################################################################################

    def package(self):
        cmake = self._get_cmake()
        cmake.install()

    ###############################################################################################

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)

    ###############################################################################################

    def source(self):
        git = tools.Git(folder=self._repository_name, runner=self.run)
        git.clone(self._repository_url,
                  args='-c advice.detachedHead=false',
                  branch=self._repository_revision)

    ###############################################################################################

    # methods used by the recipe itself

    ###############################################################################################

    def _get_cmake(self):
        if self._cmake:
            return self._cmake

        cmake = CMake(self)
        cmake.definitions['NANOSSL_BUILD_SHARED_LIBRARIES'] = self.options.shared

        source_folder = Path(self._repository_name)
        cmake.configure(build_folder=source_folder / self._build_subfolder,
                        source_folder=source_folder)

        self._cmake = cmake
        return cmake

###################################################################################################
