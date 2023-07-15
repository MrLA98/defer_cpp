lint:
	clang-format -style=Google -i *.cc *.h *.hpp

run:
	mkdir -p bin && g++ -std=c++17 src/demo.cc -o bin/demo -I defer && ./bin/demo

clean:
	rm -rf bin