EXTRA_DIST = CMakeLists.txt keys jwt_tests.h

TESTS =			\
	jwt_new		\
	jwt_grant	\
	jwt_header	\
	jwt_dump	\
	jwt_encode	\
	jwt_rsa		\
	jwt_ec		\
	jwt_validate	\
	jwt_rsa_pss	\
	jwt_eddsa	\
	jwt_crypto	\
	jwt_es256k

# JWKS tests are OpenSSL 3 only
if HAVE_OPENSSL
TESTS += jwt_jwks jwt_jwks_errors jwt_jwks_ec jwt_jwks_rsa
endif

check_PROGRAMS = $(TESTS)

AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -Wall $(CHECK_CFLAGS) -DKEYDIR="\"$(srcdir)/keys\"" -D_GNU_SOURCE
AM_LDFLAGS = -L$(top_builddir)/libjwt
LDADD = -ljwt $(CHECK_LIBS)

CODE_COVERAGE_IGNORE_PATTERN = '/usr/**' '**/ll.h'
@CODE_COVERAGE_RULES@
@VALGRIND_CHECK_RULES@
