#include "Packet.hpp"
#include <cstdint>
#include <cstring>

Packet::Packet(std::size_t size) : _size(size) {
	_data = new uint8_t[_size];
	_read = 0;
	_write = 0;
}

// Packet::Packet(std::string & data) {
// 	_data = new uint8_t[data.size()];   //we need extra char for NUL
// 	std::memcpy(_data, data.c_str(), data.size());
// 	_size = data.size();
// }

Packet::~Packet() {
	delete[] _data;
	_data = nullptr;
	_size = 0;
}


std::size_t Packet::size() const {
	return _write - _read;
}

void Packet::clear() {
	_read = 0;
	_write = 0;
	_error = false;
}


void Packet::skip(std::size_t len) {
	if (_read + len < size()) {
		_read += len;
	}
}

void Packet::append(const void *data, std::size_t len) {
	if (data && len > 0 && _write + len < _size) {
		std::memcpy(_data + _write, data, len);
		_write += len;
	}
}

void Packet::appendSize(std::size_t len) {
	_write += len;
}

char* Packet::data() {
	return (char *)_data + _read;
}

const char* Packet::data() const {
	return (char *)_data + _read;
}

// WRITE
void Packet::append(std::string const &str) {
	uint16_t len = str.size();
	this->append(&len, sizeof len);
	this->append(str.c_str(), len * sizeof(std::string::value_type));
}

// READ

uint8_t Packet::readInt8() {
	uint8_t nb = 0;
	if (this->isBufferFlow(sizeof uint8_t)) {
		std::memcpy(&nb, data(), sizeof nb);
		_read += sizeof uint8_t;
	}
	return nb;
}

uint16_t Packet::readInt16() {
	uint16_t nb = 0;
	if (this->isBufferFlow(sizeof uint16_t)) {
		std::memcpy(&nb, data(), sizeof nb);
		_read += sizeof uint16_t;
	}
	return nb;
}

uint32_t Packet::readInt32() {
	uint32_t nb = 0;
	if (this->isBufferFlow(sizeof uint32_t)) {
		std::memcpy(&nb, data(), sizeof nb);
		_read += sizeof uint32_t;
	}
	return nb;
}

uint64_t Packet::readInt64() {
	uint64_t nb = 0;
	if (this->isBufferFlow(sizeof uint64_t)) {
		std::memcpy(&nb, data(), sizeof nb);
		_read += sizeof uint64_t;
	}
	return nb;
}

std::string Packet::readString() {
	uint16_t len = this->readInt16();
	std::string str;
	
	if (this->isBufferFlow(len)) {
		str.assign(data(), len);
		_read += len;
	}

	return str;
}

// template<T>
// T Packet::read() {
// }


/*
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
}*/

