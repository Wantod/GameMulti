#include "Packet.hpp"

Packet::Packet() :
	m_readPos(0),
	m_sendPos(0)
{}

Packet::~Packet()
{}

const void* Packet::getData() const {
    return !m_data.empty() ? &m_data[0] : NULL;
}

std::size_t Packet::getDataSize() const {
    return m_data.size();
}

void Packet::append(const void* data, std::size_t sizeInBytes)
{
	std::size_t start = m_data.size();
	m_data.resize(start + sizeInBytes);
	std::memcpy(&m_data[start], data, sizeInBytes);
}

const void* Packet::onSend(std::size_t& size)
{
    size = getDataSize();
    return getData();
}

void Packet::onReceive(const void* data, std::size_t size)
{
    append(data, size);
}

// read
Packet& Packet::operator >>(uint8_t& data) {
	data = *reinterpret_cast<const uint8_t*>(&m_data[m_readPos]);
	m_readPos += sizeof(data);
	return *this;
}

Packet& Packet::operator >>(uint16_t& data) {
	data = ntohs(*reinterpret_cast<const uint16_t*>(&m_data[m_readPos]));
	m_readPos += sizeof(data);
	return *this;
}
Packet& Packet::operator >>(uint32_t& data) {
	data = ntohl(*reinterpret_cast<const uint32_t*>(&m_data[m_readPos]));
	m_readPos += sizeof(data);
	return *this;
}
Packet& Packet::operator >>(uint64_t& data) {
	const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&m_data[m_readPos]);
	data =	(static_cast<uint64_t>(bytes[0]) << 56) |
			(static_cast<uint64_t>(bytes[1]) << 48) |
			(static_cast<uint64_t>(bytes[2]) << 40) |
			(static_cast<uint64_t>(bytes[3]) << 32) |
			(static_cast<uint64_t>(bytes[4]) << 24) |
			(static_cast<uint64_t>(bytes[5]) << 16) |
			(static_cast<uint64_t>(bytes[6]) <<  8) |
			(static_cast<uint64_t>(bytes[7])      );
	m_readPos += sizeof(data);
	return *this;
}
Packet& Packet::operator >>(std::string& data) {
	// First extract string length
	uint32_t length = 0;
	*this >> length;

	data.clear();
	// Then extract characters
	//data.assign(&m_data[m_readPos], length);

	// Update reading position
	m_readPos += length;
	return *this;
}


// write
Packet& Packet::operator <<(uint8_t data) {
	append(&data, sizeof(data));
	return *this;
}
Packet& Packet::operator <<(uint16_t data) {
	uint16_t toWrite = htons(data);
	append(&toWrite, sizeof(toWrite));
	return *this;
}
Packet& Packet::operator <<(uint32_t data) {
	uint32_t toWrite = htonl(data);
	append(&toWrite, sizeof(toWrite));
	return *this;
}
Packet& Packet::operator <<(uint64_t data) {
	uint8_t toWrite[] =
	{
		static_cast<uint8_t>((data >> 56) & 0xFF),
		static_cast<uint8_t>((data >> 48) & 0xFF),
		static_cast<uint8_t>((data >> 40) & 0xFF),
		static_cast<uint8_t>((data >> 32) & 0xFF),
		static_cast<uint8_t>((data >> 24) & 0xFF),
		static_cast<uint8_t>((data >> 16) & 0xFF),
		static_cast<uint8_t>((data >>  8) & 0xFF),
		static_cast<uint8_t>((data      ) & 0xFF)
	};
	append(&toWrite, sizeof(toWrite));
	return *this;
}
Packet& Packet::operator <<(const std::string& data) {
	uint32_t length = static_cast<uint32_t>(data.size());
	*this << length;

	// Then insert characters
	if (length > 0)
		append(data.c_str(), length * sizeof(std::string::value_type));

	return *this;
}