PREFIX = /usr/local

LIB_TESTS = gethugepagesize test_root find_path unlinked_fd misalign \
	readback truncate shared private empty_mounts meminfo_nohuge \
	ptrace-write-hugepage icache-hygiene slbpacaflush \
	chunk-overcommit mprotect alloc-instantiate-race mlock \
	truncate_reserve_wraparound truncate_sigbus_versus_oom \
	map_high_truncate_2 truncate_above_4GB direct \
	misaligned_offset brk_near_huge task-size-overrun stack_grow_into_huge \
	counters quota heap-overflow
LIB_TESTS_64 = straddle_4GB huge_at_4GB_normal_below \
	huge_below_4GB_normal_above
NOLIB_TESTS = malloc malloc_manysmall dummy heapshrink
LDSCRIPT_TESTS = zero_filesize_segment
HUGELINK_TESTS = linkhuge linkhuge_nofd linkshare
STRESS_TESTS = mmap-gettest mmap-cow shm-gettest shm-getraw shm-fork
HELPERS = get_hugetlbfs_path
HELPER_LIBS = libheapshrink.so
BADTOOLCHAIN = bad-toolchain.sh

CFLAGS = -O2 -Wall -g
CPPFLAGS = -I..
LDLIBS = -ldl -lpthread
LDFLAGS32 = -L../obj32
LDFLAGS64 = -L../obj64
INSTALL = install

TESTS = $(LIB_TESTS) $(NOLIB_TESTS) $(STRESS_TESTS)
ifdef ELF32
TESTS += $(LDSCRIPT_TESTS) $(HUGELINK_TESTS) $(HUGELINK_TESTS:%=xB.%) \
	$(HUGELINK_TESTS:%=xBDT.%)
else
ifdef ELF64
TESTS += $(LDSCRIPT_TESTS) $(HUGELINK_TESTS) $(HUGELINK_TESTS:%=xB.%) \
	$(HUGELINK_TESTS:%=xBDT.%)
endif
endif

ifneq ($(ARCH),ia64)
TESTS_64 = $(LIB_TESTS_64)
endif

SCRIPTS=../ldscripts
SCRIPTS32 = $(SCRIPTS)/$(ELF32)
SCRIPTS64 = $(SCRIPTS)/$(ELF64)
HUGETLBFS_LD=../ld.hugetlbfs
INST_TESTSDIR32 = $(LIBDIR32)/libhugetlbfs/tests
INST_TESTSDIR64 = $(LIBDIR64)/libhugetlbfs/tests

ifdef V
VECHO = :
else
VECHO = echo "	"
.SILENT:
endif

DEPFILES = $(LIB_TESTS:%=%.d) $(NOLIB_TESTS:%=%.d) $(HUGELINK_TESTS:%=%.d) \
	$(HELPERS:%=%.d) testutils.d

ALLTESTS = $(foreach DIR,$(OBJDIRS),$(TESTS:%=$(DIR)/%))
ALLHELPERS = $(foreach DIR,$(OBJDIRS),$(HELPERS:%=$(DIR)/%))
ALLHELPERLIBS = $(foreach DIR,$(OBJDIRS),$(HELPER_LIBS:%=$(DIR)/%))
ifdef CC64
ALLTESTS += $(TESTS_64:%=obj64/%)
endif

all:	$(ALLTESTS) $(ALLHELPERS) $(ALLHELPERLIBS)

obj32/%.o: %.c
	@$(VECHO) CC32 $@
	@mkdir -p obj32
	$(CC32) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

obj64/%.o: %.c
	@$(VECHO) CC64 $@
	@mkdir -p obj64
	$(CC64) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

obj32/%-pic.o: %.c
	@$(VECHO) CC32 $@
	@mkdir -p obj32
	$(CC32) $(CPPFLAGS) $(CFLAGS) -fPIC -o $@ -c $<

obj64/%-pic.o: %.c
	@$(VECHO) CC64 $@
	@mkdir -p obj64
	$(CC64) $(CPPFLAGS) $(CFLAGS) -fPIC -o $@ -c $<

obj32/libheapshrink.so: obj32/heapshrink-helper-pic.o
	@$(VECHO) LD32 "(shared)" $@
	@mkdir -p obj32
	$(CC32) -Wl,-soname,$(notdir $@) -shared -o $@ $^

obj64/libheapshrink.so: obj64/heapshrink-helper-pic.o
	@$(VECHO) LD64 "(shared)" $@
	@mkdir -p obj64
	$(CC64) -Wl,-soname,$(notdir $@) -shared -o $@ $^

$(LIB_TESTS:%=obj32/%): %: %.o obj32/testutils.o
	@$(VECHO) LD32 "(lib test)" $@
	$(CC32) $(LDFLAGS) $(LDFLAGS32) -o $@ $^ $(LDLIBS) -lhugetlbfs 

$(LIB_TESTS:%=obj64/%) $(LIB_TESTS_64:%=obj64/%): %: %.o obj64/testutils.o
	@$(VECHO) LD64 "(lib test)" $@
	$(CC64) $(LDFLAGS) $(LDFLAGS64) -o $@ $^ $(LDLIBS) -lhugetlbfs 

$(NOLIB_TESTS:%=obj32/%): %: %.o obj32/testutils.o
	@$(VECHO) LD32 "(nolib test)" $@
	$(CC32) $(LDFLAGS) $(LDFLAGS32) -o $@ $^ $(LDLIBS)

$(NOLIB_TESTS:%=obj64/%): %: %.o obj64/testutils.o
	@$(VECHO) LD64 "(nolib test)" $@
	$(CC64) $(LDFLAGS) $(LDFLAGS64) -o $@ $^ $(LDLIBS)

$(LDSCRIPT_TESTS:%=obj32/%): obj32/%: %.ld obj32/%.o obj32/testutils.o
	@$(VECHO) LD32 "(preload test)" $@
	$(CC32) $(LDFLAGS) $(LDFLAGS32) -o $@ -Lobj32 $^ $(LDLIBS) || cp $(BADTOOLCHAIN) $@

$(LDSCRIPT_TESTS:%=obj64/%): obj64/%: %.ld obj64/%.o obj64/testutils.o
	@$(VECHO) LD64 "(preload test)" $@
	$(CC64) $(LDFLAGS) $(LDFLAGS64) -o $@ -Lobj64 $^ $(LDLIBS) || cp $(BADTOOLCHAIN) $@

$(HUGELINK_TESTS:%=obj32/%): %: %.o obj32/testutils.o
	@$(VECHO) LD32 "(hugelink test)" $@
	$(CC32) $(LDFLAGS) $(LDFLAGS32) -o $@ $^ $(LDLIBS)

$(HUGELINK_TESTS:%=obj64/%): %: %.o obj64/testutils.o
	@$(VECHO) LD64 "(hugelink test)" $@
	$(CC64) $(LDFLAGS) $(LDFLAGS64) -o $@ $^ $(LDLIBS)

$(STRESS_TESTS:%=obj32/%): %: %.o obj32/testutils.o
	@$(VECHO) LD32 "(lib test)" $@
	$(CC32) $(LDFLAGS) $(LDFLAGS32) -o $@ $^ $(LDLIBS) -lhugetlbfs 

$(STRESS_TESTS:%=obj64/%): %: %.o obj64/testutils.o
	@$(VECHO) LD64 "(lib test)" $@
	$(CC64) $(LDFLAGS) $(LDFLAGS64) -o $@ $^ $(LDLIBS) -lhugetlbfs 

obj32/xB.%: $(SCRIPTS32).xB $(HUGETLBFS_LD) obj32/%.o obj32/testutils.o
	@$(VECHO) LD32 "(xB test)" $@
	@mkdir -p obj32
	@ln -sf ../$(HUGETLBFS_LD) obj32/ld
	$(CC32) -B./obj32  $(LDFLAGS) $(LDFLAGS32) -o $@ $(LDLIBS) -Wl,--hugetlbfs-link=B $(filter %.o,$^)

obj64/xB.%: $(SCRIPTS64).xB $(HUGETLBFS_LD) obj64/%.o obj64/testutils.o
	@$(VECHO) LD64 "(xB test)" $@
	@mkdir -p obj64
	@ln -sf ../$(HUGETLBFS_LD) obj64/ld
	$(CC64) -B./obj64 $(LDFLAGS) $(LDFLAGS64) -o $@ $(LDLIBS) -Wl,--hugetlbfs-link=B $(filter %.o,$^)

obj32/xBDT.%: $(SCRIPTS32).xBDT $(HUGETLBFS_LD) obj32/%.o obj32/testutils.o
	@$(VECHO) LD32 "(xBDT test)" $@
	@mkdir -p obj32
	@ln -sf ../$(HUGETLBFS_LD) obj32/ld
	$(CC32) -B./obj32 $(LDFLAGS) $(LDFLAGS32) -o $@ $(LDLIBS) -Wl,--hugetlbfs-link=BDT $(filter %.o,$^)

obj64/xBDT.%: $(SCRIPTS64).xBDT $(HUGETLBFS_LD) obj64/%.o obj64/testutils.o
	@$(VECHO) LD64 "(xBDT test)" $@
	@mkdir -p obj64
	@ln -sf ../$(HUGETLBFS_LD) obj64/ld
	$(CC64) -B./obj64 $(LDFLAGS) $(LDFLAGS64) -o $@ $(LDLIBS) -Wl,--hugetlbfs-link=BDT $(filter %.o,$^)

$(HELPERS:%=obj32/%): %: %.o
	@$(VECHO) LD32 "(helper)" $@
	$(CC32) $(LDFLAGS) $(LDFLAGS32) -o $@ $^ $(LDLIBS) -lhugetlbfs 

$(HELPERS:%=obj64/%): %: %.o
	@$(VECHO) LD64 "(helper)" $@
	$(CC64) $(LDFLAGS) $(LDFLAGS64) -o $@ $^ $(LDLIBS) -lhugetlbfs 

clean:
	@$(VECHO) CLEAN "(tests)"
	rm -f *~ *.o *.so *.a *.d core a.out
	rm -rf obj*
	rm -f $(TESTS)

%.d: %.c
	@$(CC) $(CPPFLAGS) -MM -MT "$(foreach DIR,$(OBJDIRS),$(DIR)/$*.o) $@" $< > $@

-include $(DEPFILES)

obj32/install:
	@$(VECHO) INSTALL32 $(INST_TESTSDIR32)
	$(INSTALL) -d $(DESTDIR)$(INST_TESTSDIR32)
	$(INSTALL) -d $(DESTDIR)$(INST_TESTSDIR32)/obj32
	$(INSTALL) -m 755 $(TESTS:%=obj32/%) $(DESTDIR)$(INST_TESTSDIR32)/obj32
	$(INSTALL) -m 755 $(HELPERS:%=obj32/%) $(DESTDIR)$(INST_TESTSDIR32)/obj32
	$(INSTALL) -m 755 run_tests.sh $(DESTDIR)$(INST_TESTSDIR32)

obj64/install:
	@$(VECHO) INSTALL64 $(INST_TESTSDIR64)
	$(INSTALL) -d $(DESTDIR)$(INST_TESTSDIR64)
	$(INSTALL) -d $(DESTDIR)$(INST_TESTSDIR64)/obj64
	$(INSTALL) -m 755 $(TESTS:%=obj64/%) $(DESTDIR)$(INST_TESTSDIR64)/obj64
	$(INSTALL) -m 755 $(HELPERS:%=obj64/%) $(DESTDIR)$(INST_TESTSDIR64)/obj64
	$(INSTALL) -m 755 $(TESTS_64:%=obj64/%) $(DESTDIR)$(INST_TESTSDIR64)/obj64
	$(INSTALL) -m 755 run_tests.sh $(DESTDIR)$(INST_TESTSDIR64)

install: $(OBJDIRS:%=%/install)
