#! /bin/bash

FILES=`find ./src ./test -iregex ".*\(c\|cpp\|m\|mm\)" -type f | sort`
clang-tidy -config= -p=build ${FILES}
