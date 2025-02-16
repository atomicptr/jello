demo: build
    ./build/demo

build:
    cmake -B build
    cmake --build build -j8
