EXEC = mcast speed

RP_VERSION=3.12
CFLAGS += -O3
#CFLAGS += $(if $(CONFIG_RAETH_GMAC2),,-DUSE_SINGLE_MAC)

all: $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ -fPIC $^

mcast:  mcast.o ifaddr.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

speed:  speed.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	
romfs:
	$(ROMFSINST) mcast /usr/bin/mcast
	$(ROMFSINST) speed /usr/bin/speed
clean:
	rm -f $(EXEC) *.o
