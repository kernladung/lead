######  BUILD  ######

INCLUDES = -Isrc -I/usr/include -I/usr/include/qt -I/usr/include/qt/QtWidgets -I/usr/include/qt/QtGui -I/usr/include/qt/QtCore
COMPILER = clang -std=c++11 -Wall -O3 -fPIC -MMD $(INCLUDES) -c $< -o $@
MOC = moc $(INCLUDES) -o $@ $<
LINKER = g++ -o $@ $^ -lQt5Xdg -lQt5Widgets -lQt5Gui -lQt5Core
MKDIR = mkdir -p $(dir $@)


# this prevents make from deleting the generated moc_*.cpp files
# so that the including of the dep-files will not fail
.SECONDARY:


data/usr/bin/lead: build/main.o build/app.o build/sensor.o build/screenname.o build/moc_app.o build/moc_sensor.o build/moc_screenname.o
	$(MKDIR)
	$(LINKER)

build/%.o: src/%.cpp
	$(MKDIR)
	$(COMPILER)

build/moc_%.o: build/moc_%.cpp
	$(MKDIR)
	$(COMPILER)

build/moc_%.cpp: src/%.h
	$(MKDIR)
	$(MOC)

-include build/*.d


######  CLEAN  ######

clean:
	rm -f build/*
	rm -f data/usr/bin/lead


######  INSTALL  ######

install:
	cp -r data/* /


######  UNINSTALL  ######

uninstall:
	rm -f /usr/bin/lead


.PHONY: clean install uninstall