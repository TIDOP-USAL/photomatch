set(test_filename tst_claheprocess.cpp)
get_filename_component(test ${test_filename} NAME_WE)
DEFINE_TEST_PROCESS(${test} ${test_filename})