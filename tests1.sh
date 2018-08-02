#!/bin/bash

test_count=1
do_test() {
	printf "\e[32m${test_count}: %-40s\e[1;32m$2\e[0m\n" "${1}"
	eval $2
	# echo "1arg: $1"
	let "test_count++"
}







# do_test "no args" "./ft_ssl"
# do_test "invalid cmd" "./ft_ssl foobar"
# do_test "invalid cmd" "./ft_ssl foobar foobar2"

echo "====== TESTS WITH MD5 ======"

# do_test "non existing file" "./ft_ssl md5 foobar"
# do_test "file no rights" "./ft_ssl md5 norights"
# do_test "invalid option" "./ft_ssl md5 -"
# do_test "invalid option" "./ft_ssl md5 -l"
# do_test "invalid option" "./ft_ssl md5 -l file"
# do_test "invalid option" "./ft_ssl md5 -s test -l file"
# do_test "no string after -s" "./ft_ssl md5 -s"
# do_test "-r opt" "./ft_ssl md5 -r file"
# do_test "-r and -s options" "./ft_ssl md5 -r -s test"
# do_test "-r and -s and -q options" "./ft_ssl md5 -q -r -s test"
# do_test "-r and -q options" "./ft_ssl md5 -q -r file"
# do_test "-q option" "./ft_ssl md5 -q file"
# do_test "read from stdin" "echo \"And above all\" | ./ft_ssl md5"
# do_test "read from stdin with -p" "echo \"And above all\" | ./ft_ssl md5 -p"
# do_test "read from stdin with -p" "echo \"And above all\" | ./ft_ssl md5 -p -r"

# echo "===== TESTS WITH SHA256 ====="

do_test "-r and -s options" "./ft_ssl sha256 -r -s test"
do_test "-r and -s and -q options" "./ft_ssl sha256 -q -r -s test"
do_test "-r and -q options" "./ft_ssl sha256 -q -r file"
do_test "-q option" "./ft_ssl sha256 -q file"
do_test "read from stdin" "echo \"And above all\" | ./ft_ssl sha256"
do_test "read from stdin with -p" "echo \"And above all\" | ./ft_ssl sha256 -p"
do_test "read from stdin with -p" "echo \"And above all\" | ./ft_ssl sha256 -p -r"