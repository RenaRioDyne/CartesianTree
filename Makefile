CXXFLAGS := -std=c++20 -Wall -Wextra -O2

INCFLAGS = -Iinclude
LIBFLAGS =

TARGETS = main

OBJS = main.o \
       lccs_dp.o \
	   lccs_constructive.o \
	   cartesianTree.o \
	   parentDistance.o

SRCDIR := src/
OBJDIR := build/
DEPDIR := build/dep/

_MANGLED_OBJS = $(OBJS:%=$(OBJDIR)%)
_MANGLED_TARGETS = $(TARGETS:%=$(OBJDIR)%)
_MANGLED_DEPS = $(OBJS:%.o=$(DEPDIR)%.d)

.PHONY: all
all: $(_MANGLED_TARGETS)

.PHONY: clean
clean:
	rm -rf $(_MANGLED_OBJS) $(_MANGLED_TARGETS) $(OBJDIR)

$(_MANGLED_TARGETS): $(_MANGLED_OBJS)
	$(CXX) -o $@	$^	$(CXXFLAGS)	$(LIBFLAGS)

$(_MANGLED_OBJS): $(OBJDIR)%.o: $(SRCDIR)%.cpp | $(OBJDIR)
	$(CXX) -c -o $@	$<	$(CXXFLAGS)	$(INCFLAGS)

$(_MANGLED_DEPS): $(DEPDIR)%.d: $(SRCDIR)%.cpp | $(DEPDIR)
	$(CXX) -MF $@	$<	-MM -MP -MT '$(OBJDIR)$*.o'	$(INCFLAGS)

$(SRCDIR) $(OBJDIR) $(DEPDIR):
	mkdir -p $@

ifeq (,$(filter clean,$(MAKECMDGOALS)))
include $(_MANGLED_DEPS)
endif
