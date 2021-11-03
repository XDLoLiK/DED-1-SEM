CXX       = g++

FLAGS     = -g -std=c++14 -Wall -Wextra -Weffc++ -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Waggressive-loop-optimizations -Warray-bounds -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlarger-than=8192 -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wnarrowing -Wno-old-style-cast -Wvarargs -fcheck-new -fsized-deallocation -fstack-check -fstack-protector-all -fstrict-overflow -flto-odr-type-merging

PROCESSOR = Assembler\Assembler.cpp Disassembler\Disassembler.cpp Processor\Processor.cpp Processor\VideoDriver.cpp Terminal\Terminal.cpp main.cpp

EXTERNAL  = ..\Stack\Stack.cpp ..\Onegin\TextSort.cpp ..\general\Swapper.cpp

all:
	$(CXX) $(FLAGS) $(PROCESSOR) $(EXTERNAL) -o terminal.exe

