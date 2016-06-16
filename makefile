all:
	gcc -Wall `pkg-config --cflags gtk+-2.0 lxpanel` -shared -fPIC lxpanel-plugin-xbacklight.c -o lxpanel-plugin-xbacklight.so `pkg-config --libs lxpanel`

clean:
	rm *.so

install:
	cp lxpanel-plugin-xbacklight.so /usr/lib/lxpanel/plugins/

uninstall:
	rm /usr/lib/lxpanel/plugins/lxpanel-plugin-xbacklight.so
