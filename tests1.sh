#!/bin/bash

test_count=1
do_test() {
	printf "\e[32m${test_count}: $1\e[1;32m\t\t$2\e[0m\n"
	eval $2
	let "test_count++"
}







do_test "no args" "./ft_ssl"
do_test "invalid cmd" "./ft_ssl foobar"
do_test "invalid cmd" "./ft_ssl foobar foobar2"
do_test "non existing file" "./ft_ssl md5 foobar"
do_test "file no rights" "./ft_ssl md5 norights"
do_test "invalid option" "./ft_ssl md5 -"
do_test "invalid option" "./ft_ssl md5 -l"
do_test "invalid option" "./ft_ssl md5 -l file"
do_test "invalid option" "./ft_ssl md5 -s test -l file"
