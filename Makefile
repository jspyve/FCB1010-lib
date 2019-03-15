TOUCH             = touch
SDCC              = sdcc

SDCC_BASE_OPTS    = --model-large --xram-loc 0x8000
#SDCC_COMPILE_OPTS = -mmcs51 $(SDCC_BASE_OPTS) --std-sdcc99 --nogcse --noinvariant --noinduction --nojtbound --noloopreverse --nolabelopt --nooverlay --no-peep --no-peep-return --nolospre
SDCC_COMPILE_OPTS = -mmcs51 $(SDCC_BASE_OPTS) --std-sdcc99
SDCC_LINK_OPTS    = $(SDCC_BASE_OPTS) --out-fmt-ihx --lib-path "c:\Program files\SDCC\lib\large"

SRCDIRS           := hardware led switch adc serial timer relay i2c eeprom mcu midi axe-fx fcb pedal

.PHONY: srcdirs
.PHONY: $(SRCDIRS)
.PHONY: root
.PHONY: all
.PHONY: clean
.PHONY: rebuild

all: root srcdirs AxeFCB.hex

srcdirs: $(SRCDIRS)

$(SRCDIRS):
	@$(MAKE) -C $@ --makefile=..\Makefile.subdir "SDCC_COMPILE_OPTS=$(SDCC_COMPILE_OPTS) -I.." "SDCC=$(SDCC)" "OBJDIR=..\obj"

root:
	@$(MAKE) --makefile=Makefile.subdir "SDCC_COMPILE_OPTS=$(SDCC_COMPILE_OPTS) -I." "SDCC=$(SDCC)" "OBJDIR=obj"

AxeFCB.hex: root srcdirs
	$(SDCC) $(SDCC_LINK_OPTS) -o AxeFCB.hex $(wildcard obj/*.rel)

clean:
	-@rm -f obj/*

rebuild:
	$(MAKE) clean
	$(MAKE) all
