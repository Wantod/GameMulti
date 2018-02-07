#ifndef PACKET_HPP
# define PACKET_HPP

# include <string>
# include <vector>
# include "Sockets.hpp"

class Packet
{
public:
	Packet();
	Packet(std::string &data);
	~Packet();

	void setSize(std::size_t size);
	std::size_t getSize() const;
	const char* getData() const;
	uint8_t* getDataPtr();
private:
	uint8_t *_data;
	uint8_t *_pos;
	std::size_t _size;
};

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

// 	const void* onSend(std::size_t& size);
// 	void onReceive(const void* data, std::size_t size);

// 	void append(const void* data, std::size_t sizeInBytes);

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
// private:
// 	std::vector<unsigned char> m_data;
// 	std::size_t m_readPos;
// 	std::size_t m_sendPos;
// };

#endif // !PACKET_HPP