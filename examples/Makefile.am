AM_CPPFLAGS = -I../include

LDADD = ../libpythia8.la -llhapdfdummy

AM_DEFAULT_SOURCE_EXT = .cc

bin_PROGRAMS = main01 main02 main03 main04 main05 main06 main07 main08 main09 \
main10 main11 main12 main13 main14 main15 main16 main17 main18 main19 main20 \
main21 main22 main23 main24 main25 main26 main27 main28 main29 main30 main41 \
main42 main43 main44 main51 main71

if BUILD_HEPMC
bin_PROGRAMS += main31 main32
main31_LDADD = ../libpythia8.la ../liblhapdfdummy.la -lHepMC ../libhepmcinterface.la
main32_LDADD = ../libpythia8.la ../liblhapdfdummy.la -lHepMC ../libhepmcinterface.la
endif
main51_LDADD = ../libpythia8.la ../liblhapdfdummy.la -lpythia6

#examples/main61 # needs fastjet
