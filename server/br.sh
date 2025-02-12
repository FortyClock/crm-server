sudo rm -rf build && mkdir build && cd build && sudo cmake .. && sudo make && \
cd test && ./utils_test && \
cd ../ && ./server