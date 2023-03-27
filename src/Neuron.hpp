#pragma once
#include "./HeaderFiles.hpp"

class Connection;

inline float sgn(float value) {
	return (0.f < value) - (value < 0.f);
}

inline float step(float value) {
	return ( value >= 0.f );
}

inline float step05(float value) {
	return ( value >= 0.5f );
}

inline float sigmoid(float x) {
	return 1.f / ( 1.f + std::exp( -x ) );
}

class Neuron {
public:
	void AddParent( Neuron & neuron, float weight = get_random_float( 0.25f, 0.75f ) );

	float Model();

	inline void SetLastValue( float value ) { last_value_ = value; }
	inline float GetLastValue() const { return last_value_; }

	inline void SetLastDelta( float delta ) { last_delta_ = delta; }
	inline float GetLastDelta() const { return last_delta_; }

	inline int GetConnectionCount() const { return connections_.size(); }
	Connection & operator[]( int index ) { return *connections_[index]; }

private:
	std::vector<Connection *> connections_;
	float last_value_ = 0.f;
	float last_delta_ = 0.f;
};
