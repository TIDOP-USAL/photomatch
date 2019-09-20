set(test_filename tst_msddetector.cpp)
get_filename_component(test ${test_filename} NAME_WE)
DEFINE_TEST_CORE(${test} ${test_filename})