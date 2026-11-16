# vbcc's ppc-amigaos target: startup code and the C, math, amiga.lib and
# auto-open libraries, each library also in a small-data (-sd) version.
#
#   make SDK_INCLUDE=<AmigaOS 4 SDK>/include/include_h
#   make install PREFIX=<toolchain prefix>
#
# vbccppc, vasmppc_std and ppc-amigaos-ar are taken from PATH unless VBCC,
# VASM and AR say otherwise.  vbccppc must have been built with HAVE_AOS4
# (machines/ppc/machine.h defines it).

VBCC ?= vbccppc
VASM ?= vasmppc_std
# make has a default AR (the host's ar), so ?= would not do here.
ifeq ($(origin AR),default)
AR = ppc-amigaos-ar
endif
O ?= build
SDK_INCLUDE ?= $(error set SDK_INCLUDE to the AmigaOS 4 SDK's include/include_h)

CFLAGS = -quiet -elf -no-regnames -no-multiple-ccs -madd -use-commons \
	-D__amigaos4__ -O=991 -Iinclude -I$(SDK_INCLUDE)
VASMFLAGS = -quiet -Felf -opt-branch -nowarn=62

# Sources of each library
VC_DIRS = libsrc libsrc/ctype libsrc/locale libsrc/setjmp libsrc/signal \
	libsrc/stdio libsrc/stdlib libsrc/string libsrc/time libsrc/vbcc
srcs = $(sort $(foreach d,$(1),$(wildcard $(d)/*.c $(d)/*.s)))
VC_SRC = $(call srcs,$(VC_DIRS))
VBCC_SRC = $(call srcs,libsrc/vbcc libsrc/libvbcc)
M_SRC = $(call srcs,libsrc/math libsrc/math/fdlibm)
AMIGA_SRC = $(call srcs,libsrc/AmigaLib)

# $(call objs,n|sd,sources)
objs = $(patsubst %,$(O)/$(1)/%.o,$(basename $(2)))

LIBS = libvc libvcs libvbcc libm libms libamiga libamigas \
	libauto libautos libraauto libraautos
all: $(O)/lib/startup.o $(O)/lib/minstart.o $(LIBS:%=$(O)/lib/%.a)

$(O)/lib/libvc.a: $(call objs,n,$(VC_SRC))
$(O)/lib/libvcs.a: $(call objs,sd,$(VC_SRC))
$(O)/lib/libvbcc.a: $(call objs,n,$(VBCC_SRC))
$(O)/lib/libm.a: $(call objs,n,$(M_SRC))
$(O)/lib/libms.a: $(call objs,sd,$(M_SRC))
$(O)/lib/libamiga.a: $(call objs,n,$(AMIGA_SRC))
$(O)/lib/libamigas.a: $(call objs,sd,$(AMIGA_SRC))

$(O)/lib/%.a:
	@mkdir -p $(@D)
	rm -f $@
	$(AR) rcsD $@ $^

$(O)/lib/%.o: startup/%.s
	@mkdir -p $(@D)
	$(VASM) $(VASMFLAGS) $< -o $@

$(O)/n/%.o: %.c
	@mkdir -p $(@D)
	$(VBCC) $(CFLAGS) $< -o=$(@:.o=.asm)
	$(VASM) $(VASMFLAGS) -no-regnames $(@:.o=.asm) -o $@

$(O)/sd/%.o: %.c
	@mkdir -p $(@D)
	$(VBCC) $(CFLAGS) -sd $< -o=$(@:.o=.asm)
	$(VASM) $(VASMFLAGS) -no-regnames $(@:.o=.asm) -o $@

$(O)/n/%.o: %.s
	@mkdir -p $(@D)
	$(VASM) $(VASMFLAGS) $< -o $@

$(O)/sd/%.o: %.s
	@mkdir -p $(@D)
	$(VASM) $(VASMFLAGS) $< -o $@

# libauto and libraauto: one object per auto.tab entry, compiled from the
# template for its kind.  auto.mk lists them and their -D options.
AUTO_TAB = libsrc/auto/auto.tab
AUTO_TPL = libsrc/auto/lib.c libsrc/auto/ver.c libsrc/auto/iface.c

$(O)/auto.mk: $(AUTO_TAB) Makefile
	@mkdir -p $(@D)
	sed -e 's/#.*//' $(AUTO_TAB) | awk '\
	  function add(name, src, defs) { \
	    for (i = 1; i <= nlibs; i++) printf "AUTO_%s += %s\n", libs[i], name; \
	    for (v = 1; v <= 2; v++) { \
	      t = "$$(O)/" (v == 1 ? "n" : "sd") "/auto/" name ".o"; \
	      printf "%s: AUTOSRC = libsrc/auto/%s\n%s: AUTODEFS = %s\n", t, src, t, defs; \
	    } \
	  } \
	  $$1 == "lib" { nlibs = split($$4, libs, ","); \
	    add($$2, "lib.c", "-DBASE=" $$2 " %%-DNAME=\"" $$3 "\"%%"); \
	    add($$2 "Ver", "ver.c", "-DBASE=" $$2); } \
	  $$1 == "iface" { nlibs = split($$6, libs, ","); \
	    add($$2, "iface.c", "-DIFACE=" $$2 " -DBASE=" $$3 " %%-DNAME=\"" $$4 "\"%% -DVERSION=" $$5); }' \
	| sed -e "s/%%/'/g" > $@

ifeq ($(filter clean,$(MAKECMDGOALS)),)
-include $(O)/auto.mk
endif

$(O)/lib/libauto.a: $(AUTO_auto:%=$(O)/n/auto/%.o)
$(O)/lib/libautos.a: $(AUTO_auto:%=$(O)/sd/auto/%.o)
$(O)/lib/libraauto.a: $(AUTO_raauto:%=$(O)/n/auto/%.o)
$(O)/lib/libraautos.a: $(AUTO_raauto:%=$(O)/sd/auto/%.o)

$(O)/n/auto/%.o: $(AUTO_TPL) $(AUTO_TAB)
	@mkdir -p $(@D)
	$(VBCC) $(CFLAGS) $(AUTODEFS) $(AUTOSRC) -o=$(@:.o=.asm)
	$(VASM) $(VASMFLAGS) -no-regnames $(@:.o=.asm) -o $@

$(O)/sd/auto/%.o: $(AUTO_TPL) $(AUTO_TAB)
	@mkdir -p $(@D)
	$(VBCC) $(CFLAGS) -sd $(AUTODEFS) $(AUTOSRC) -o=$(@:.o=.asm)
	$(VASM) $(VASMFLAGS) -no-regnames $(@:.o=.asm) -o $@

# Installs the target where aosppc.config expects it and the config beside
# vc, as aosppc and as the default vc.config.
PREFIX ?= /usr/local
VBCC_DIR = $(PREFIX)/ppc-amigaos/vbcc

install: all
	mkdir -p $(DESTDIR)$(VBCC_DIR)/include $(DESTDIR)$(VBCC_DIR)/lib $(DESTDIR)$(PREFIX)/bin
	cp -R include/. $(DESTDIR)$(VBCC_DIR)/include/
	cp $(O)/lib/*.a $(O)/lib/*.o startup/script $(DESTDIR)$(VBCC_DIR)/lib/
	for c in aosppc vc.config; do \
	  sed 's|PREFIX|$(PREFIX)|g' aosppc.config > $(DESTDIR)$(PREFIX)/bin/$$c || exit 1; \
	done

clean:
	rm -rf $(O)

.PHONY: all install clean
.SECONDARY:
