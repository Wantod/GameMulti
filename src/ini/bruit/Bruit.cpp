#include "Bruit.hpp"
#include <iostream>

Bruit::Bruit(unsigned int seed, float min, float max)
	: _min(min), _max(max)
{
	this->setSeed(seed);
	_scale = 0.05f;

	for (size_t i = 0; i < 512; i++)
		perm[i] = i & 255;

	this->shuffle();
}

Bruit::~Bruit()
{}

void Bruit::setSeed(unsigned int seed)
{
	generator.seed(seed);
}

void Bruit::shuffle()
{
	std::uniform_int_distribution<int> distribution(0, 255);

	for (int i = 0; i < 256; i++)
		perm[i] = i;
	for (int i = 0; i < 256; i++) {
		int j = distribution(generator);
		//Swap perm[i] and perm[j]
		int aux = perm[i];
		perm[i] = perm[j];
		perm[j] = aux;
	}

	for (int i = 0; i < 256; i++)
	{
		perm[i + 256] = perm[i];
	}
}

void Bruit::setScale(float scale)
{
	_scale = scale;
}

int Bruit::fastfloor(float n)
{
	return (n >= 0) ? static_cast<int>(n) : static_cast<int>(n - 1);
}

double Bruit::value(int x, int y, int octaves, double frequency, double persistence)
{
	double bruit = 0.;
	double amplitude = 1.;

	for (int i = 0; i < octaves; i++)
	{
		//Translation du centre de symétrie en i * 4096
		int t = i * 4096;

		//Calcul du bruit translaté
		bruit += get(x * frequency + t, y * frequency + t) * amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	double geo_lim = (1 - persistence) / (1 - amplitude);

	return bruit * geo_lim;
}

double Bruit::value(int x, int y, int z, int octaves, double startFrequency, double persistence)
{
	double bruit = 0.0f;
	double normalizeFactor = 1.0f;

	double frequence = startFrequency;

	// amplitude max du bruit
	double amplitude = 1.0f;

	for (int i = 0; i < octaves; i++)
	{
		normalizeFactor += amplitude;

		// addition the simplex noise
		bruit += get(x * frequence, y * frequence, z * frequence) * amplitude;
		// on double la frequence pour octave suicant
		frequence *= 2;
		amplitude *= persistence;
	}

	return bruit / normalizeFactor;
}

float Bruit::value(int x, int y, float scale)
{
	return get(scale * x, scale* y);
}

float Bruit::value(int x, int y, int z, float scale)
{
	return get(x * scale, y * scale, z * scale);
}