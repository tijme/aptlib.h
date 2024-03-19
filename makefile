MODULES := $(wildcard ./modules/*)

all: $(MODULES)

$(MODULES):
	make -C $@ $(ACTION)

.PHONY: all $(MODULES)