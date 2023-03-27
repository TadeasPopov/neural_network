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
		std::string layer_name = std::to_string( layer_index );
		if (layer_index == 0) {
			layer_name = "OUTPUT";
		}
		if (layer_index == layers_.size() - 1) {
			layer_name = "INPUT";
		}
		std::cout << "[Layer " << layer_index << "]" << std::endl;
		Layer & layer = *layers_[layer_index];
		for ( int neuron_index = 0; neuron_index < layer.GetNeuronCount(); neuron_index++) {
			Neuron & neuron = layer[neuron_index];
			std::cout << "\t[Neuron " << neuron_index << "]" << std::endl;
			std::cout << "\tlv: " << neuron.GetLastValue() << std::endl;
			std::cout << "\tld: " << neuron.GetLastDelta() << std::endl;
			for ( int connection_index = 0; connection_index < neuron.GetConnectionCount(); connection_index++ ) {
				Connection & connection = neuron[connection_index];
				std::cout << "\tc" << connection_index << ": " << connection.GetWeight() << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

void NeuralNetwork::Train(std::vector<std::pair<std::vector<float>, std::vector<float>>> & train_sets, int batch_size, int epoch_count) {
	float best_error = -1.f;
	int best_epoch = -1;

	int layers_last_index = layers_.size() - 1;
	float error = 1.f;

	for ( int epoch = 0; epoch < epoch_count && error > 0.f; epoch++ ) {
		error = 0.f;
		// std::cout << "epoch: " << epoch << "\n";

		for ( int batch = 0; batch < batch_size; batch++ ) {
			int batch_index = batch % train_sets.size();
			// std::cout << "\tbatch: " << batch << " | " << train_sets[batch_index].first[0] << " " << train_sets[batch_index].first[1] << "\n";
			std::vector<float> output = Model( train_sets[batch_index].first );
			// std::cout << "R: " << output[0] << "\n";

			for ( int layer_index = layers_last_index; layer_index >= 1; layer_index-- ) {
				Layer & layer = *layers_[layer_index];

				if (layer_index == layers_last_index) {
					float total_neuron_error = 0.f;
					for ( int neuron_index = 0; neuron_index < layer.GetNeuronCount(); neuron_index++ ) {
						Neuron & neuron = layer[neuron_index];
						float neuron_error = train_sets[batch_index].second[neuron_index] - output[neuron_index];
						if ( neuron_error != 0 ) {
							total_neuron_error++;
							float delta = neuron_error * sigmoid_derivative( output[neuron_index] );
							neuron.SetLastDelta( delta );
							// std::cout << "OUTPUT: " << neuron_index << " | " << delta << "\n";
							/* for ( int connection_index = 0; connection_index < neuron.GetConnectionCount(); connection_index++ ) {
								Connection & connection = neuron[connection_index];
								// std::cout <<
								// 	"\t\tl: " << layer_index <<
								// 	" n: " << neuron_index <<
								// 	" c: " << connection_index <<
								// 	" delta: " << delta <<
								// 	" pv: " << connection.GetParentValue() <<
								// 	" oldW: " << connection.GetWeight() <<
								// 	" newW: " << connection.GetWeight() + 0.1f * delta * connection.GetParentValue() <<
								// 	"\n";
								connection.SetWeight(connection.GetWeight() + 0.1f * delta * connection.GetParentValue());
							} */
						}
					}
					// error += total_neuron_error / layer.GetNeuronCount();
				} else {
					Layer & last_layer = *layers_[layer_index + 1];

					for ( int neuron_index = 0; neuron_index < layer.GetNeuronCount(); neuron_index++ ) {
						Neuron & neuron = layer[neuron_index];
						float sum = 0.f;
						for ( int last_neuron_index = 0; last_neuron_index < last_layer.GetNeuronCount(); last_neuron_index++ ) {
							Neuron & last_neuron = last_layer[last_neuron_index];
							sum += last_neuron.GetLastDelta() * last_neuron[neuron_index].GetWeight();
						}
						float delta = sum * sigmoid_derivative(neuron.GetLastValue());
						neuron.SetLastDelta( delta );
						// std::cout << "HIDDEN: " << neuron_index << " | " << delta << "\n";
					}
				}
			}

			for ( int layer_index = 1; layer_index < layers_.size(); layer_index++ ) {
				Layer & layer = *layers_[layer_index];

				for ( int neuron_index = 0; neuron_index < layer.GetNeuronCount(); neuron_index++ ) {
					Neuron & neuron = layer[neuron_index];

					for ( int connection_index = 0; connection_index < neuron.GetConnectionCount(); connection_index++ ) {
						Connection & connection = neuron[connection_index];
						if (layer_index == 1) {
							// std::cout << "UP-HIDDEN: " << neuron_index << " c: " << connection_index << " | " << connection.GetWeight() + 0.1f * neuron.GetLastDelta() * connection.GetParentValue() << " | " <<  neuron.GetLastDelta() << " " << connection.GetParentValue() << "\n";
						} else {
							// std::cout << "UP-OUTPUT: " << neuron_index << " c: " << connection_index << " | " << connection.GetWeight() + 0.1f * neuron.GetLastDelta() * connection.GetParentValue() << " | " <<  neuron.GetLastDelta() << " " << connection.GetParentValue() << "\n";
						}
						connection.SetWeight(connection.GetWeight() + 0.1f * neuron.GetLastDelta() * connection.GetParentValue());
					}

					neuron.SetLastDelta( 0.f );
				}
			}

			error += 0.5f * std::pow( train_sets[batch_index].second[0] - output[0], 2 );
		}

		// error /= batch_size;
		if (epoch % 1000 == 0) {
			std::cout << "epoch: " << epoch << " error: " << error << "\n";
		}

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
				// std::cout << "L: " << layer_index - 1 << " N: " << neuron_index << " w: " << value << "\n";

				if (layer_index == layers_.size() - 1) {
					output.push_back(value);
				}
			}
		}
	}
	return output;
}
