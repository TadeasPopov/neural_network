#pragma once
#include "./NeuralNetwork.hpp"

void NeuralNetwork::Add( int neuron_count ) {
	layers_.push_back( new Layer( neuron_count ) );

	// first layer is input
	if (layers_.size() > 1) {
		Layer parent_layer = *layers_[layers_.size() - 2];
		Layer child_layer = *layers_[layers_.size() - 1];
		child_layer.Connect( parent_layer );
	}
}

void NeuralNetwork::Print() {
	for ( int layer_index = layers_.size() - 1; layer_index >= 0; layer_index-- ) {
		std::cout << "[Layer " << layer_index << "]" << std::endl;
		Layer & layer = *layers_[layer_index];
		for ( int neuron_index = 0; neuron_index < layer.GetNeuronCount(); neuron_index++) {
			Neuron & neuron = layer[neuron_index];
			std::cout << "[Neuron " << neuron_index << "]" << std::endl;
			std::cout << "lv: " << neuron.GetLastValue() << std::endl;
			for ( int connection_index = 0; connection_index < neuron.GetConnectionCount(); connection_index++ ) {
				Connection & connection = neuron[connection_index];
				std::cout << "c" << connection_index << ": " << connection.GetWeight() << std::endl;
			}
			std::cout << std::endl;
		}
	}
}

void NeuralNetwork::Train(std::vector<std::pair<std::vector<float>, std::vector<float>>> & train_sets, int batch_size, int epoch_count) {
	float best_error = -1.f;
	int best_epoch = -1;

	int layers_last_index = layers_.size() - 1;

	for ( int epoch = 0; epoch < epoch_count; epoch++ ) {
		float error = 0.f;
		// std::cout << "epoch: " << epoch << "\n";

		for ( int batch = 0; batch < batch_size; batch++ ) {
			int batch_index = batch % train_sets.size();
			// std::cout << "\tbatch: " << batch << "\n";
			std::vector<float> output = Model( train_sets[batch_index].first );
			/* std::cout << "\t\t" <<
				train_sets[batch_index].first[0] << " OR " <<
				train_sets[batch_index].first[1] << " = " <<
				train_sets[batch_index].second[0] << " | " <<
				output[0] <<
				"\n"; */

			for ( int layer_index = layers_last_index; layer_index >= 1; layer_index-- ) {
				Layer & layer = *layers_[layer_index];
				// std::cout << "layer: " << layer_index << "\n";

				if (layer_index == layers_last_index) {
					float total_neuron_error = 0.f;
					for ( int neuron_index = 0; neuron_index < layer.GetNeuronCount(); neuron_index++ ) {
						Neuron & neuron = layer[neuron_index];
						// std::cout << "neuron: " << neuron_index << "\n";
						// std::cout << output.size() << " " << train_sets[batch_index].second.size() << "\n";
						float neuron_error = train_sets[batch_index].second[neuron_index] - output[neuron_index];
						// std::cout << "neuron: " << neuron_index << " error: " << neuron_error << "\n";
						if ( neuron_error != 0 ) {
							total_neuron_error++;
							// float delta = neuron_error * (output[neuron_index] * (1.f - output[neuron_index]));
							float delta = neuron_error;
							// Print();
							for ( int connection_index = 0; connection_index < neuron.GetConnectionCount(); connection_index++ ) {
								Connection & connection = neuron[connection_index];
								/* std::cout <<
									"\t\tl: " << layer_index <<
									" n: " << neuron_index <<
									" c: " << connection_index <<
									" delta: " << delta <<
									" pv: " << connection.GetParentValue() <<
									" oldW: " << connection.GetWeight() <<
									" newW: " << connection.GetWeight() + 0.1f * delta * connection.GetParentValue() <<
									"\n"; */
								connection.SetWeight(connection.GetWeight() + 0.1f * delta * connection.GetParentValue());
							}
						}
					}
					error += total_neuron_error / layer.GetNeuronCount();
				}
			}
		}

		error /= batch_size;
		std::cout << "epoch: " << epoch << " error: " << error << "\n";

		/* if (epoch == 0 || error < best_error) {
			best_error = error;
			best_epoch = epoch;
		} */
	}
}

std::vector<float> NeuralNetwork::Model(std::vector<float> & input) {
	std::vector<float> output;
	for ( int layer_index = 0; layer_index < layers_.size(); layer_index++ ) {
		Layer & layer = *layers_[layer_index];

		if (layer_index == 0) {
			for ( int input_index = 0; input_index < input.size(); input_index++) {
				Neuron & neuron = layer[input_index];
				neuron.SetLastValue(input[input_index]);
			}
		} else {
			for ( int neuron_index = 0; neuron_index < layer.GetNeuronCount(); neuron_index++) {
				Neuron & neuron = layer[neuron_index];
				float value = neuron.Model();
				neuron.SetLastValue( value );

				if (layer_index == layers_.size() - 1) {
					output.push_back(value);
				}
			}
		}
	}
	return output;
}
