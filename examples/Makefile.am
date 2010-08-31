AM_CPPFLAGS = -I$(top_srcdir)/include

LDADD = ../libpythia8.la -llhapdfdummy

AM_DEFAULT_SOURCE_EXT = .cc

check_PROGRAMS = main01 main02 main03 main04 main05 main06 main07 main08 main09 \
main10 main11 main12 main13 main14 main15 main16 main17 main18 main19 main20 \
main21 main22 main23 main24 main25 main26 main27 main28 main29 main30 main41 \
main42 main43 main44 main51 main71

TESTS = main01 main02 test03 test04 main05 test06 test07 test08 main09 main10 main11 main12 main13 main14 main15 test16 test17 main18 main19 main20 main21 test22 main23 main24 main25 main26 main27 main28 test29 main30 main41 main42 test43 main44 main51 main71

test03:
	./main03 main03.cmnd
test04:
	./main04 main04.cmnd
test06:
	./main06 main06.cmnd
test07:
	./main07 main07.cmnd
test08:
	./main08 main08.cmnd
test16:
	./main16 main16.cmnd
test17:
	./main17 main17.cmnd
test22:
	./main22 main22.cmnd
test29:
	./main29 main29.cmnd
test32:
	./main32 main32.cmnd
test43:
	./main43 main43.cmnd

if BUILD_HEPMC
check_PROGRAMS += main31 main32
TESTS += main31 test32
main31_LDADD = ../libpythia8.la ../liblhapdfdummy.la -lHepMC ../libhepmcinterface.la
main32_LDADD = ../libpythia8.la ../liblhapdfdummy.la -lHepMC ../libhepmcinterface.la
endif
main51_LDADD = ../libpythia8.la ../liblhapdfdummy.la -lpythia6

#examples/main61 # needs fastjet
