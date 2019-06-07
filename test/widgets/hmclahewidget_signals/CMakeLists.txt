set(test_filename tst_hmclahewidgetsignals.cpp)
get_filename_component(test ${test_filename} NAME_WE)
DEFINE_TEST_WIDGETS(${test} ${test_filename})