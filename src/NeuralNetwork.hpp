#pragma once
#include "./HeaderFiles.hpp"
#include "./Neuron.hpp"
#include "./Connection.hpp"
#include "./Layer.hpp"

inline float sigmoid_derivative(float value) {
	return value * ( 1.f - value );
}

class NeuralNetwork {
public:
	void Add( int neuron_count );
	void Print();
	void Train( std::vector<std::pair<std::vector<float>, std::vector<float>>> & train_sets, int batch_size = 16, int epoch_count = 4 );
	std::vector<float> Model( std::vector<float> & input );

private:
	std::vector<Layer *> layers_;
};
