#pragma once
#include "./Connection.hpp"
#include "./Neuron.hpp"

Connection::Connection( Neuron * parent, Neuron * child, float weight ) {
	parent_ = parent;
	child_ = child;
	weight_ = weight;
}

float Connection::GetParentValue() const {
	return parent_->GetLastValue();
}
