cmake_minimum_required(VERSION 3.23)
project("neural-network")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable("${PROJECT_NAME}"
	"./src/main.cpp"
	"./src/NeuralNetwork.cpp"
	"./src/Layer.cpp"
	"./src/Neuron.cpp"
	"./src/Connection.cpp"
)

target_link_libraries("${PROJECT_NAME}"
	${OpenCV_LIBS}
)
