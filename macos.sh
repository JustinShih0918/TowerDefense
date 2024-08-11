export PKG_CONFIG_PATH=/opt/homebrew/Cellar/allegro/5.2.9.1/lib:$PKG_CONFIG_PATH &&
export PKG_CONFIG_PATH=/opt/homebrew/Cellar/allegro/5.2.9.1/lib/pkgconfig:$PKG_CONFIG_PATH &&
cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++ - &&
DCMAKE_C_COMPILER=/usr/bin/gcc . &&

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM="ninja" -G Ninja -S "$(pwd)" -B "$(pwd)/cmake-build-debug" &&
cmake --build "$(pwd)/cmake-build-debug" --target 2024_I2P2_TowerDefense_with_answer &&
"$(pwd)/cmake-build-debug/2024_I2P2_TowerDefense_with_answer"
