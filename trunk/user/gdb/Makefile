SRC_NAME=gdb-6.8

CFLAGS += -O3 -ffunction-sections -fdata-sections
LDFLAGS += -Wl,--gc-sections

all: config_test
	$(MAKE) -C $(SRC_NAME)/gdb/gdbserver

config_test:
	( if [ -f ./config_done ]; then \
		echo "the same configuration"; \
	else \
		make configure && touch config_done; \
	fi )

configure:
	( cd $(SRC_NAME)/gdb/gdbserver ; \
	./configure \
		--prefix=/usr \
		--host=$(HOST_TARGET) \
		--build=$(HOST_BUILD) ; \
	)

clean:
	if [ -f $(SRC_NAME)/Makefile ] ; then \
		$(MAKE) -C $(SRC_NAME)/gdb/gdbserver distclean ; \
	fi ; \
	rm -f config_done

romfs:
	$(ROMFSINST) $(SRC_NAME)/gdb/gdbserver/gdbserver /sbin/gdbserver
