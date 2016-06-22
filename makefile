all:
	gcc -Wall `pkg-config --cflags gtk+-2.0 lxpanel` -shared -fPIC src/*.c -o lpbc.so `pkg-config --libs lxpanel`

clean:
	rm lpbc.so

install:
	cp lpbc.so /usr/lib/lxpanel/plugins/

uninstall:
	rm /usr/lib/lxpanel/plugins/lpbc.so
