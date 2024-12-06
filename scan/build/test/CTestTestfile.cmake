# CMake generated Testfile for 
# Source directory: /home/ivan/Documents/dev/scan/test
# Build directory: /home/ivan/Documents/dev/scan/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ScanTestSuite "/home/ivan/Documents/dev/scan/build/test/net_recon_tests")
set_tests_properties(ScanTestSuite PROPERTIES  _BACKTRACE_TRIPLES "/home/ivan/Documents/dev/scan/test/CMakeLists.txt;41;add_test;/home/ivan/Documents/dev/scan/test/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
