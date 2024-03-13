MODULES := $(wildcard ./modules/*)

all: $(MODULES)

$(MODULES):
	make -C $@ all

.PHONY: all $(MODULES)