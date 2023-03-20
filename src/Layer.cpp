#pragma once
#include "./Layer.hpp"

Layer::Layer( int neuron_count ) {
	for ( int i = 0; i < neuron_count; i++ ) {
		neurons_.push_back(new Neuron());
	}
}

void Layer::Connect( Layer & parent ) {
	for ( int i = 0; i < parent.GetNeuronCount(); i++ ) {
		for ( int j = 0; j < neurons_.size(); j++ ) {
			neurons_[j]->AddParent( parent[i] );
		}
	}
}
