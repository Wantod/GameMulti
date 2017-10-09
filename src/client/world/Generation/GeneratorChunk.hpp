#ifndef GENERATORCHUNK_HPP
# define GENERATORCHUNK_HPP

# include <iostream>
# include <vector>
# include <complex>
# include <unordered_map>


class Column;
class GeneratorChunk
{
public:
	GeneratorChunk(Column& col);
	~GeneratorChunk();
};


#endif // !GENERATORCHUNK_HPP