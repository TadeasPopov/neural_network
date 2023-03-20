#pragma once
#include "./HeaderFiles.hpp"

class Neuron;

class Connection {
public:
	Connection( Neuron * parent, Neuron * child, float weight = get_random_float( 0.25f, 0.75f ) );

	inline float GetWeight() const { return weight_; }
	inline void SetWeight( float weight ) { weight_ = weight; }

	float GetParentValue() const;

private:
	Neuron * parent_ = nullptr;
	Neuron * child_ = nullptr;
	float weight_;
};
