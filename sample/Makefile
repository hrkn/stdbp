INCLUDE_PATH = ../include
LD_FLAGS =
CFLAGS = -std=c++98 -Wall

QUIET = @

TARGETS = $(shell find -name "*.cpp" | while read file; do echo "$${file%.*}"; done)

all: .sources.mk $(TARGETS)

clean:
	rm -f $(TARGETS) $(addsuffix .o,$(TARGETS))

%: %.o
	$(CXX) -o $@ $^ $(LD_FLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CFLAGS) $(addprefix -I,$(INCLUDE_PATH))

future/%: LD_FLAGS += -lpthread
thread/%: LD_FLAGS += -lpthread
mutex/%:  LD_FLAGS += -lpthread

showtarget:
	@ find -name "*.cpp" | while read file; do echo "$${file%.*}"; done

.PHONY: .sources.mk
.sources.mk:
	$(QUIET) rm -f $@
	$(QUIET) echo -n "samples: " >>$@ && echo $(TARGETS) >>$@ && echo >>$@
	$(QUIET) find -name "*.cpp" | \
		while read file; do echo "$${file%.*}: $${file%.*}.o" >>$@; done
	$(QUIET) find -name "*.cpp" | xargs $(CPP) $(addprefix -I,$(INCLUDE_PATH)) -MM $$source $(INCLUDE_FLAG) >>$@
	$(QUIET) mv $@ $@.bak
	$(QUIET) cat $@.bak | perl -p -e 's,^(.+?)\.o: (.+?)/\1\.c.*,$$2/$$&,;' >$@
	$(QUIET) rm $@.bak

-include .sources.mk
