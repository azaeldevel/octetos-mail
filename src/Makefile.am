

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = octetos_mail

octetos_mail_SOURCES = \
	main.cc mail.cc

octetos_mail_LDFLAGS = $(LIBCURL_CFLAGS) $(LIBXML2_CFLAGS)

octetos_mail_LDADD = $(LIBCURL_LIBS) $(LIBXML2_LIBS) 


