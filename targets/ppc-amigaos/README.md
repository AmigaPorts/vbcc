# vbcc target ppc-amigaos

The AmigaOS 4 target for vbcc, built from source: the startup code and the
libraries vc links against, in the layout of vbcc's own
`vbcc_target_ppc-amigaos` archive.

| Library | Contents |
| --- | --- |
| `startup.o`, `minstart.o` | startup code (`startup/`) |
| `libvc.a` | the C library, vclib (`libsrc/` except the directories below) |
| `libm.a` | floating point: math functions, `printf`/`scanf` with floats (`libsrc/math/`) |
| `libamiga.a` | amiga.lib functions (`libsrc/AmigaLib/`) |
| `libauto.a`, `libraauto.a` | open the libraries and interfaces a program uses (`libsrc/auto/`) |
| `libvbcc.a` | the compiler's 64-bit arithmetic helpers, for use without vclib (`libsrc/vbcc/`, `libsrc/libvbcc/`) |

Each library except `libvbcc.a` also comes as a small-data version, built
with `-sd`: `libvcs.a`, `libms.a`, `libamigas.a`, `libautos.a`,
`libraautos.a`.  `include/` holds vclib's headers, `startup/script` the
linker script, `aosppc.config` a config for vc on a Unix host.

## Building

    make SDK_INCLUDE=<AmigaOS 4 SDK>/include/include_h
    make install PREFIX=<toolchain prefix>

This needs vbccppc built from this repository (its ppc backend defines
`HAVE_AOS4`, which the AmigaOS 4 interface calls need), vasmppc_std and
ppc-amigaos-ar, from `PATH` or given as `VBCC=`, `VASM=` and `AR=`.  The
build goes into `build/`, or `O=<dir>`.

`make install` puts the headers and libraries into
`PREFIX/ppc-amigaos/vbcc/{include,lib}`, and `aosppc.config` with `PREFIX`
filled in into `PREFIX/bin` as `aosppc` and as the default `vc.config`.
`vc` reads its config from beside itself, and the config names every tool
and file by its path, so `vc` and `vc +aosppc` work without `VBCC` or
`PATH` set.  The config expects `vbccppc`, `vscppc`, `vasmppc_std` and
`vlink` in `PREFIX/bin`, and the SDK's headers in
`PREFIX/ppc-amigaos/SDK/include/include_h`.

## Where the sources come from

vclib's sources start from the public domain vclib for the PowerUp target
in the 1998 vbcc distribution (`machines/amigappc/libsrc`), with its
directory layout.  They are updated to vclib as vbcc 0.9h's target archive
(2022-05-22) ships it for AmigaOS 4: AmigaOS 4 interfaces instead of
PowerUp calls, C99 additions (`long long`, `snprintf`, `strtoll`,
`<inttypes.h>` functions, ...), the stdio, startup and exit code as
AmigaOS 4 has it, and the parts that are new since (`libauto`,
`__so_init`, ...).  The assembly sources are those parts of the archive's
libraries as vasm source.

Compiled by vbcc 0.9h patch 2 with `-O=991` (`vc -O1`), as the archive's
libraries were, every object of every library is identical to the
archive's, except:

- `strftime`: the archive's `%p` reads the AM/PM string from past the end
  of its string table; this one uses `AM_STR` from `<locale.h>`.
- `atan`, `atan2`, `cos`, `exp`, `log`, `log10`, `pow`, `sin` and `sqrt`:
  the archive has Motorola's libmoto object code for these, which comes
  without source; `libsrc/math/fdlibm/` has Sun's fdlibm for them instead
  (under Sun's notice in each file).  fdlibm divides by zero to make
  infinities and NaNs, which vbcc would work out at compile time, so it
  divides by a `volatile` zero there.

Two oddities of the originals are kept, each with a comment: `InvertString()` allocates with `AllocMem()` what
`FreeIEvents()` frees with `FreeVec()`, and `scanf()` of a float with more
than 35 decimals never stops reading.

`libauto` and `libraauto` are one object per entry of
`libsrc/auto/auto.tab`, compiled from the template for its kind
(`lib.c`, `ver.c`, `iface.c`).
