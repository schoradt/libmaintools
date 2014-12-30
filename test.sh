#!/bin/sh

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:.

# test 1
./test_1.t --test=testparam --testparam=12.23 -r tester --te p1 p2 p3 -- --p4 12 12.23

#test 2
ln -s test/testrc .test_2.trc

./test_2.t test/testrc

rm -f .test_2.trc
