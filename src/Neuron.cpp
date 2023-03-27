#pragma once
#include "./Neuron.hpp"
#include "./Connection.hpp"

float Neuron::Model() {
	float sum = 0.f;
	for ( int i = 0; i < connections_.size(); i++ ) {
		sum += connections_[i]->GetParentValue() * connections_[i]->GetWeight();
	}
	// log &
	// return step05( sum );
	// line
	// return step( sum );
	return sigmoid( sum );
}

void Neuron::AddParent(Neuron & neuron, float weight ) {
	connections_.push_back( new Connection( &neuron, this, weight ) );
}
