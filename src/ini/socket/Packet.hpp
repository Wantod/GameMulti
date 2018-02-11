#ifndef PACKET_HPP
# define PACKET_HPP

# include <string>
# include <vector>
# include "Sockets.hpp"

class Packet
{
public:
	Packet(std::size_t size);
	Packet(const Packet &p) {
		_size = p.size();
		_read = 0;
		_write = _size;
		_data = new uint8_t[_size];
		std::memcpy(_data, p._data, _size);
	}

	~Packet();

	// info & get data
	void clear();
	void skip(std::size_t len);
	char* data();
	const char* data() const;
	const char* dataBegin() const;
	std::size_t size() const;
	std::size_t fullSize() const { return _size; }

	// write
	void append(const void *, std::size_t len);
	void append(std::string const &str);
	void appendSize(std::size_t len);

	// read
	uint8_t readInt8();
	uint16_t readInt16();
	uint32_t readInt32();
	uint64_t readInt64();
	std::string readString();


	bool getError() const {
		return _error;
	}

private:
	bool isBufferFlow(std::size_t size) {
		if (_read + size < _size)
			return true;
		_error = true;
		return false;
	}

	bool bufferPefect() {
		uint8_t *new_data = new uint8_t[_write];
		std::memcpy(new_data, _data, _write);
		delete[] _data;
		_data = new_data;
		_size = _size;
		return true;
	}

	uint8_t *_data;
	std::size_t _read;
	std::size_t _write;
	std::size_t _size;

	bool _error = false;
};

//template<T>
//T read();
// buffer = new uint8_t[numBytes];
// and get rid of your buffer using:
// delete[] buffer;

// class Packet
// {
// public:
// 	Packet();
// 	~Packet();

// 	const void* getData() const;
// 	std::size_t getDataSize() const;
// 	// read
// 	Packet& operator >>(uint8_t&	 	data);
// 	Packet& operator >>(uint16_t&	 	data);
// 	Packet& operator >>(uint32_t&	 	data);
// 	Packet& operator >>(uint64_t&	 	data);
// 	Packet& operator >>(std::string&	data);

// 	// write
// 	Packet& operator <<(uint8_t data);
// 	Packet& operator <<(uint16_t data);
// 	Packet& operator <<(uint32_t data);
// 	Packet& operator <<(uint64_t data);
// 	Packet& operator <<(const std::string&	data);
// 	const void* onSend(std::size_t& size);
// 	void onReceive(const void* data, std::size_t size);

// 	void append(const void* data, std::size_t sizeInBytes);

// private:
// 	std::vector<unsigned char> m_data;
// 	std::size_t m_readPos;
// 	std::size_t m_sendPos;
// };

#endif // !PACKET_HPP