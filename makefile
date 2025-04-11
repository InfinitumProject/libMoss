modules = DataHandler network
tests = bimap TCP

LibName = MossLib

ValidateDirs = "./build/lib" "./build/objects" "./build/tests" "./include/MossLib" "./src" "./tests"

Debug = false

CompilerArgs = #-std=c++20
# Reminder to self on how to make it use libs in custom directory
# g++ ./test.cpp -Wl,-rpath,./build/lib -L./build/lib -lMoss -o Test

.PHONY: BuildLibDir
ValidateDirStruct:
	@mkdir -p ${ValidateDirs}
	@echo "Project directories validated"

.PHONY: BuildObjects
BuildObjects: ValidateDirStruct
	@for current_module in ${modules}; do \
		g++ ${CompilerArgs} -c -fPIC ./src/$$current_module.cpp -o ./build/objects/$$current_module.o; \
	done
	@echo "Objects built"

.PHONY: BuildLib
BuildLib: BuildObjects ValidateDirStruct
	@g++ ${CompilerArgs} -shared -o ./build/lib/libMoss.so ./build/objects/*.o
	@echo "Library '${LibName}' compiled"

.PHONY: BuildTests

BuildTests: BuildLib ValidateDirStruct
	@for current_module in ${tests}; do \
		if [ ! -d "./build/tests/$$current_module" ]; then \
			mkdir ./build/tests/$$current_module; \
		fi; \
		g++ ${CompilerArgs} ./tests/$$current_module/test.cpp -Wl,-rpath,\$$ORIGIN/../../lib -L./build/lib -lMoss -o ./build/tests/$$current_module/Test; \
	done
	@echo "Tests built"

.PHONY: RunTests
RunTests: BuildTests
	@for test in ${tests}; do \
		DEBUG=${Debug} ./build/tests/$$test/Test; \
		if [ $$? -ne 0 ]; then \
			echo "A tested module '$$test' failed!!"; \
		fi; \
	done;
	@echo "All tests have been run"