modules = files


.PHONY: BuildObjects
BuildObjects:
	for current_module in ${modules}; do \
		g++ -c -fPIC ./src/MossLib/$$current_module.cpp -o ./build/objects/$$current_module.o; \
	done


.PHONY: BuildLib
BuildLib: BuildObjects
	g++ -shared -o ./build/lib/libMoss.so ./build/objects/*.o

