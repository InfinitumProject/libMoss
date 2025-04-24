modules ?= network
tests = bimap TCP/Streamlike

LibName = libMoss

ValidateDirs = "./build/lib" "./build/objects" "./build/tests" "./include/MossLib" "./src" "./tests" "./build/packages"

compiler?=g++
# 
# x86_64-w64-mingw32-g++-posix

Debug = false

CompilerArgs = -std=c++17
# Reminder to self on how to make it use libs in custom directory
# ${compiler} ./test.cpp -Wl,-rpath,./build/lib -L./build/lib -lMoss -o Test

.PHONY: BuildLibDir
ValidateDirStruct:
	@mkdir -p ${ValidateDirs}
	@echo "Project directories validated"

.PHONY: BuildObjects
BuildObjects: ValidateDirStruct
	@for current_module in ${modules}; do \
		${compiler} ${CompilerArgs} -c -fPIC ./src/$$current_module.cpp -o ./build/objects/$$current_module.o; \
	done
	@echo "Objects built"

.PHONY: BuildLib
BuildLib: BuildObjects ValidateDirStruct
	@${compiler} ${CompilerArgs} -shared -o ./build/lib/${LibName}.so ./build/objects/*.o
	@echo "Library '${LibName}' compiled"

.PHONY: BuildTests

BuildTests: BuildLib ValidateDirStruct
	@for current_module in ${tests}; do \
		if [ ! -d "./build/tests/$$current_module" ]; then \
			mkdir -p ./build/tests/$$current_module; \
		fi; \
		${compiler} ${CompilerArgs} ./tests/$$current_module/test.cpp -Wl,-rpath,\$$ORIGIN/../../lib -L./build/lib -lMoss -o ./build/tests/$$current_module/Test; \
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

.PHONY: PackageArch
PackageArch: build_scripts/PKGBUILD ValidateDirStruct
	@echo "Now making Arch Linux package"
	@makepkg -fcD ./build_scripts
	@echo "cleaning directories"
	@rm -rf ./build_scripts/${LibName};
	@echo "Removing debug build"
	@rm -f ./build_scripts/${LibName}-debug*.pkg.tar.zst
	@echo "Moving finished package to 'build/packages'"
	@mv ./build_scripts/${LibName}*.pkg.tar.zst ./build/packages

.PHONY: PackageDeb
PackageDeb: build_scripts/package_debian.sh ValidateDirStruct
	@echo "Now making Debian Linux package"
	@./build_scripts/package_debian.sh
	@echo "Moving finished package to 'build/packages'"
	@mv ./${LibName}*.deb ./build/packages

