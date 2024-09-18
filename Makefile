BUILD_DIR := build

# Run dart pub get on tool directory.
get:
	@ cd ./tool; dart pub get

# Remove all build outputs and intermediate files.
clean:
	@ rm -rf $(BUILD_DIR)
	@ rm -rf gen

# Run the tests for every chapter's version of clox.
test: debug
	@ dart tool/bin/test.dart c -i build/clox

# Compile a debug build of clox.
debug:
	./nob
