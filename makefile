SourcePath=src/common/compilers/pseudo

main.o: main.cpp
	g++ -std=c++11 -I ${SourcePath}/lang -I ${SourcePath}/lang/expression  -I ${SourcePath}/datastruct *.cpp ${SourcePath}/lang/*.cpp ${SourcePath}/lang/expression/*.cpp ${SourcePath}/datastruct/*.cpp -o FlowDiagramMaker.exe 