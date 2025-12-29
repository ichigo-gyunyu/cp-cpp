files:= cf.cpp in.txt

run: build
	< in.txt > out.txt ./out
	cat out.txt

sprint: release
	< in.txt > out.txt ./out
	cat out.txt

build:
	g++ -std=c++23 -Wall -Wextra -g -fsanitize=address,undefined -o out cf.cpp -DICHIDBG

release:
	g++ -std=c++23 -O3 -o out cf.cpp

gen: gen.cpp
	g++ -std=c++23 -O2 -o gen gen.cpp

brute: brute.cpp
	g++ -std=c++23 -O2 -o brute brute.cpp
