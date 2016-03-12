libdir=$(prefix)/lib

CPPFLAGS=-Wall -g -fPIC -I ../submodules/ecclesandking1969/include \
	-I ../submodules/rpiozhogin2012/include
CPP=g++

XURONGLAN2015_SRC=xuronglan2015.C \
	../submodules/ecclesandking1969/src/ecclesandking1969.C \
	../submodules/rpiozhogin2012/src/rpiozhogin2012.C
XURONGLAN2015_OBJ=$(XURONGLAN2015_SRC:.C=.o)

build: libXuronglan2015.a libXuronglan2015.so

libXuronglan2015.a: $(XURONGLAN2015_OBJ)
	ar rc $@ $^

libXuronglan2015.so: $(XURONGLAN2015_OBJ)
	$(CPP) -shared -Wl,-soname,$@ -o $@ $^

install: $(libdir)/libXuronglan2015.a $(libdir)/libXuronglan2015.so

$(libdir)/libXuronglan2015.a $(libdir)/libXuronglan2015.so: libXuronglan2015.a libXuronglan2015.so
	cp libXuronglan2015.a libXuronglan2015.so $(libdir)

uninstall:
	- rm -f $(libdir)/libXuronglan2015.a $(libdir)/libXuronglan2015.so

clean:
	- rm -f libXuronglan2015.a libXuronglan2015.so $(XURONGLAN2015_OBJ)
