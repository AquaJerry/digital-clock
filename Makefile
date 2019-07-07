bin = bin  # binary
cc = clang++  # cplusplus compiler
db = gdb  # debugger
format = clang-format  # code beautifier
format_flags = -i  # inplace
libs = SDL2  # libraries
lint = clang-tidy  # code checker
lint_flags = -checks=* -fix  # inplace
objs = main.cpp  # files to compile
std = c++2a  # standard

cc_flags = -g -l$(libs) -o$(bin) -std=$(std)  # libraries


db : $(bin)
	$($@) $< -ex r

$(bin) :
	make lint format cc

cc format lint : $(objs)
	$($@) $< $($@_flags)

clean :
	rm $(bin)
