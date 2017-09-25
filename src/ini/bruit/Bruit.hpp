#ifndef BRUIT_HPP
# define BRUIT_HPP

# include <random>

class Bruit
{
public:
	Bruit(unsigned int seed = 0, float min = 0, float max = 255);
	virtual ~Bruit();

	void setSeed(unsigned int seed);
	void setScale(float scale);
	void shuffle();

	virtual float get(float x, float y) = 0;
	virtual float get(float x, float y, float z) = 0;

	int fastfloor(float n);

	virtual float value(int x, int y, float scale);
	virtual float value(int x, int y, int z, float scale);
	
	virtual double value(int x, int y, int octaves, double frequency, double percistence);
	virtual double value(int x, int y, int z, int octaves, double frequency, double percistence);

protected:
	unsigned int perm[512];
	float _scale;
	float _min;
	float _max;
private:
	std::mt19937 generator;
};

#endif // !BRUIT_HPP