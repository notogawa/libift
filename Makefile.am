ACLOCAL_AMFLAGS = -I m4

SUBDIRS=\
script \
include \
src \
sample

EXTRA_DIST=\
LICENSE \
README.rst

pkgconfigdir=\
@pkgconfigdir@

pkgconfig_DATA=\
libift.pc

cscope:
	@cd $(top_srcdir) && \
	find . -name "*.[ch]pp" -o -name "*.[ch]" | sort > cscope.files && \
	cscope -b -q
