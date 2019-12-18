binaland: build/config/config_item.o build/config/config_property_tpl.o build/entry.o
	g++ -g -std=c++11 build/entry.o build/config/config_item.o build/config/config_property_tpl.o -o binaland -lboost_regex

build/config/config_item.o: src/config/ConfigItem.cpp src/config/ConfigItem.h
	g++ -g -std=c++11 -c src/config/ConfigItem.cpp -o build/config/config_item.o -lboost_regex

build/config/config_property_tpl.o: src/config/ConfigPropertyTpl.cpp src/config/ConfigItem.h
	g++ -g -std=c++11 -c src/config/ConfigPropertyTpl.cpp -o build/config/config_property_tpl.o

build/entry.o: src/main.cpp
	g++ -g -std=c++11 -c src/main.cpp -o build/entry.o

clear:
	rm -f build/config/*.o
	rm -f build/*.o
	rm -f binaland

install:
	cp binaland ~/bin/

