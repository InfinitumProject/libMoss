modules = files script cli
tests = script cli

# Reminder to self on how to make it use libs in custom directory
# g++ ./test.cpp -Wl,-rpath,./build/lib -L./build/lib -lMoss -o Test

.PHONY: BuildLibDir
ValidateDirStruct:
	if [ ! -d "./build" ]; then \
		mkdir ./build; \
	fi; \
	for dir in lib objects tests; do \
		if [ ! -d "./build/'$$dir'" ]; then \
			mkdir ./build/$$dir; \
		fi; \
	done;

.PHONY: BuildObjects
BuildObjects: ValidateDirStruct
	for current_module in ${modules}; do \
		g++ -c -fPIC ./src/MossLib/$$current_module.cpp -o ./build/objects/$$current_module.o; \
	done

.PHONY: BuildLib
BuildLib: BuildObjects ValidateDirStruct
	g++ -shared -o ./build/lib/libMoss.so ./build/objects/*.o

.PHONY: BuildTests

BuildTests: BuildLib ValidateDirStruct
	for current_module in ${tests}; do \
		if [ ! -d "./build/tests/'$$current_module'" ]; then \
			mkdir ./build/tests/$$current_module; \
		fi; \
		g++ ./tests/$$current_module/test.cpp -Wl,-rpath,./build/lib -L./build/lib -lMoss -o ./build/tests/$$current_module/Test; \
	done