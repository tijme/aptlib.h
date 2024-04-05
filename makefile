MODULES := $(wildcard ./modules/*)


all: welcome $(MODULES)

welcome:
	@echo "[+] Starting all compilation & testing tasks"

$(MODULES):
	@make -C $@ $(ACTION)

.PHONY: all $(MODULES)