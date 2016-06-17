all:
	gcc -Wall `pkg-config --cflags gtk+-2.0 lxpanel` -shared -fPIC lxpanel-plugin-brightness-control.c -o lxpanel-plugin-brightness-control.so `pkg-config --libs lxpanel`

clean:
	rm *.so

install:
	cp lxpanel-plugin-brightness-control.so /usr/lib/lxpanel/plugins/

uninstall:
	rm /usr/lib/lxpanel/plugins/lxpanel-plugin-brightness-control.so
