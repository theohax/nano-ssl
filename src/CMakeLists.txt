########################################################################################################################

# define the name of a new target
#
set(TARGET_NAME "nanossl")

# list its source files
#
set(SOURCE_FILES "private/impl/certificate_builder_impl.cpp"
                 "private/impl/certificate_impl.cpp"
                 "private/impl/key_pair_impl.cpp"
                 "private/openssl/bio.cpp"
                 "private/openssl/error.cpp"
                 "private/openssl/handles/buffer.cpp"
                 "private/expect/expect_or_throw.cpp"
                 "private/expect/expect_or_log.cpp"
                 "private/expect/detail/expect_impl.cpp"
                 "private/log/log.cpp"
                 "private/utils/recursion_guard.cpp"
                 "public/certificate.cpp"
                 "public/certificate_builder.cpp"
                 "public/key_pair.cpp"
                 "public/time_interval.cpp")

########################################################################################################################

# define and configure the target by specifying its name, type and list of source files
#
configure_target("${TARGET_NAME}" "SHARED_LIBRARY" "${SOURCE_FILES}")

########################################################################################################################
