#ifndef PACKET_HPP
# define PACKET_HPP

# include <string>
# include <vector>
# include "Sockets.hpp"

class Packet
{
public:
	Packet();
	~Packet();

	const void* getData() const;
	std::size_t getDataSize() const;

	const void* onSend(std::size_t& size);
	void onReceive(const void* data, std::size_t size);

	void append(const void* data, std::size_t sizeInBytes);

	// read
	Packet& operator >>(uint8_t&	 	data);
	Packet& operator >>(uint16_t&	 	data);
	Packet& operator >>(uint32_t&	 	data);
	Packet& operator >>(uint64_t&	 	data);
	Packet& operator >>(std::string&	data);

	// write
	Packet& operator <<(uint8_t data);
	Packet& operator <<(uint16_t data);
	Packet& operator <<(uint32_t data);
	Packet& operator <<(uint64_t data);
	Packet& operator <<(const std::string&	data);
private:
	std::vector<char> m_data;
	std::size_t m_readPos;
	std::size_t m_sendPos;
};

#endif // !PACKET_HPP