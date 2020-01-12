# cplusplus compiler
CXX = clang++

# debugger
DB = lldb

# run binary and quit
DBFLAGS = -o r -o q

# code beautifier
FORMAT = clang-format

# inplace
FORMATFLAGS = -i

# code checker
LINT = clang-tidy

# inplace
LINTFLAGS = -checks=* -fix


# binary directory
bin_dir = bin

# libraries
libs = SDL2

# files to compile
objs = main.cpp

# standard
std = c++2a


# binary
bin = $(bin_dir)/clock


# how to compile
CXXFLAGS = -g -l$(libs) -o$(bin) -std=$(std)


DB : $(bin)
	$($@) $($@FLAGS) $<

$(bin) : LINT FORMAT CXX

$(bin_dir) :
	mkdir $(bin_dir)

CXX : $(bin_dir)

CXX FORMAT LINT : $(objs)
	$($@) $($@FLAGS) $<

clean :
	rm -r $(bin_dir)
