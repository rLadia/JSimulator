EMCC=~/bin/emscripten/emcc
OUT=../jsimulator/js

SRC_DIR=NBodySimulator/src

src = gravity.cpp \
      model.cpp \
      modelobject.cpp \
      nbodysimulator.cpp \
      overlap.cpp \

test_src = display.cpp \
           main.cpp \
           tablelogger.cpp \
           test_data.cpp \
           test_model.cpp \
           util.cpp \

objects = $(src:%.cpp=$(SRC_DIR)/%.cpp)
test_objects = $(test_src:%.cpp=$(OBJ_DIR)/%.o)

main:
	$(EMCC) -DNDEBUG $(objects) --bind jsimulator.cpp -o c++simulator.js
	mv c++simulator.js* $(OUT)

