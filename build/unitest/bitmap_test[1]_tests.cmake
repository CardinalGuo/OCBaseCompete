add_test( test_bitmap.test_bitmap /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/bin/bitmap_test [==[--gtest_filter=test_bitmap.test_bitmap]==] --gtest_also_run_disabled_tests)
set_tests_properties( test_bitmap.test_bitmap PROPERTIES WORKING_DIRECTORY /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest)
set( bitmap_test_TESTS test_bitmap.test_bitmap)
