MODEL_DIR = Model
CONTROLLER_DIR = Controller
MODEL_FILE := $(wildcard $(MODEL_DIR)/*.cpp)
CONTROLLER_FILE := $(wildcard $(CONTROLLER_DIR)/*.cpp)

main: $(MODEL_FILE) Data/OBJImporter.cpp Data/Importer.cpp Data/Exporter.cpp Data/OBJExporter.cpp $(CONTROLLER_FILE) View/View.cpp main.cpp
	g++ -o main $^

debug: $(MODEL_FILE) $(CONTROLLER_FILE) Data/OBJImporter.cpp Data/Importer.cpp Data/Exporter.cpp Data/OBJExporter.cpp View/View.cpp main.cpp
	g++ -o debug $^ -g
	gdb debug

clean:
	rm main debug


