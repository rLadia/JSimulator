CC=~/bin/emscripten/emcc
OUT=~/Dropbox/TheFishcube/dev/pages/JSimulator/js

main:
	$(CC) -DNDEBUG src/*.cpp --bind jsimulator.cpp -o c++simulator.js
	mv c++simulator.js* $(OUT)

test:
	g++ -std=c++11 *.cpp test/*.cpp -o TestAll
