#pragma once
#include "./HeaderFiles.hpp"
#include "./Neuron.hpp"

class Layer
{
public:
	Layer( int neuron_count );

	void Connect( Layer & parent );
	inline int GetNeuronCount() const { return neurons_.size(); }

	Neuron & operator[]( int index ) { return *neurons_[index]; }

private:
	std::vector<Neuron *> neurons_;
};
