modules = files script
tests = script

# Reminder to self on how to make it use libs in custom directory
# g++ ./test.cpp -Wl,-rpath,./build/lib -L./build/lib -lMoss -o Test

.PHONY: BuildObjects
BuildObjects:
	for current_module in ${modules}; do \
		g++ -c -fPIC ./src/MossLib/$$current_module.cpp -o ./build/objects/$$current_module.o; \
	done


.PHONY: BuildLib
BuildLib: BuildObjects
	g++ -shared -o ./build/lib/libMoss.so ./build/objects/*.o

.PHONY: BuildTests

BuildTests: BuildLib
	for current_module in ${tests}; do \
		g++ ./tests/$$current_module/test.cpp -Wl,-rpath,./build/lib -L./build/lib -lMoss -o ./build/tests/$$current_module/Test; \
	done