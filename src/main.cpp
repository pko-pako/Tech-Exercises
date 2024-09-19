#include <string>
#include <format>
#include <iostream>
#include <map>
#include <queue>
#include <WinSock2.h>
#include <cstddef> // for std::byte
#include <sstream>
#include <iomanip> // For std::setfill and std::setw
#include <chrono>

using std::cout;
using std::endl;

std::queue<std::pair<std::string, std::string>> q;

struct header
{
	uint16_t a;
	uint32_t b;
	uint16_t c;
	uint16_t d;
	uint16_t e;
};

struct headerStruct
{
	uint16_t byte_data_type;
	uint32_t total_length;
	uint16_t video_codec;
	uint16_t sequence_number;
	uint16_t is_keyframe;
	// uint64_t last_sync_timestamp;
	// uint64_t timestamp;
	// uint16_t reserved1;
	// uint16_t reserved2;
};

enum class _GenericByteDataType : uint16_t
{
	VIDEO = 0x0010,
	AUDIO = 0x0002,
	CONTROL = 0x0003,
};

enum class _VideoCodecType : uint16_t
{
	H264 = 0x0001,
	H265 = 0x0002,
	VP8 = 0x0003,
	VP9 = 0x0004,
	VIDEO = 0x000A,
};

uint64_t lastSyncTimestamp = 0;
uint16_t sequenceNumber = 0;
const uint32_t GENERIC_BYTE_DATA_BLOCK_HEADER_SIZE = 32;

using fullFrame = std::pair<std::vector<std::byte>, std::string>; // header and data

template <typename T>
void serialize_value(T value, std::vector<std::byte> &bytes, size_t &offset)
{
	std::memcpy(bytes.data() + offset, &value, sizeof(T));
	offset += sizeof(T);
}

std::vector<std::byte> NewGenerateDataBlockWithHeader(_GenericByteDataType byte_data_type, _VideoCodecType video_codec, bool is_keyframe, uint64_t timestamp, size_t data_size)
{
	if (is_keyframe)
	{
		lastSyncTimestamp = timestamp;
	}

	uint32_t total_length = data_size + GENERIC_BYTE_DATA_BLOCK_HEADER_SIZE;

	std::vector<std::byte> header(GENERIC_BYTE_DATA_BLOCK_HEADER_SIZE);
	size_t offset = 0;

	serialize_value(htons((u_short)byte_data_type), header, offset);
	serialize_value(htonl(total_length), header, offset);
	serialize_value(htons((u_short)video_codec), header, offset);
	serialize_value(htons(sequenceNumber), header, offset);
	serialize_value(htons(is_keyframe ? 0x0001 : 0x0000), header, offset);
	serialize_value(htonll(lastSyncTimestamp), header, offset);
	serialize_value(htonll(timestamp), header, offset);
	serialize_value(htons(0), header, offset);
	serialize_value(htons(0), header, offset);
	sequenceNumber++;

	return header;
}

std::pair<std::unique_ptr<BYTE[]>, uint32_t> GenerateDataBlockWithHeader(_GenericByteDataType byte_data_type, _VideoCodecType video_codec, bool is_keyframe, uint64_t timestamp, std::string &data)
{
	if (is_keyframe)
	{
		lastSyncTimestamp = timestamp;
	}

	uint32_t total_length = data.size() + GENERIC_BYTE_DATA_BLOCK_HEADER_SIZE;
	auto buffer = std::make_unique<BYTE[]>(total_length);

	*((uint16_t *)&buffer[0]) = htons((u_short)byte_data_type);
	*((uint32_t *)&buffer[2]) = htonl(total_length);
	*((uint16_t *)&buffer[6]) = htons((u_short)video_codec);
	*((uint16_t *)&buffer[8]) = htons(sequenceNumber);
	*((uint16_t *)&buffer[10]) = htons(is_keyframe ? 0x0001 : 0x0000);
	*((uint64_t *)&buffer[12]) = htonll(lastSyncTimestamp);
	*((uint64_t *)&buffer[20]) = htonll(timestamp);
	*((uint16_t *)&buffer[28]) = htons(0);
	*((uint16_t *)&buffer[30]) = htons(0);
	sequenceNumber++;

	return std::make_pair(std::move(buffer), GENERIC_BYTE_DATA_BLOCK_HEADER_SIZE);
}

int main()
{
	auto [header, body] = fullFrame();
	cout << header.size() << header.empty() << endl;
	cout << body.size() << body.empty() << endl;

	// Test the function and track time on average per execution
	int iterations = 1000000;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < iterations; i++)
	{
		std::string data1(1781, 'a');
		auto res1 = GenerateDataBlockWithHeader(_GenericByteDataType::VIDEO, _VideoCodecType::VIDEO, true, 1725535934442, data1);

		std::string data2(13, 'a');
		auto res2 = GenerateDataBlockWithHeader(_GenericByteDataType::VIDEO, _VideoCodecType::VIDEO, false, 1725535934460, data2);
	}
	auto end = std::chrono::high_resolution_clock::now();
	cout << "Old Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;

	// Test the function and track time on average per execution
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < iterations; i++)
	{
		std::string data1(1781, 'a');
		auto res1 = NewGenerateDataBlockWithHeader(_GenericByteDataType::VIDEO, _VideoCodecType::VIDEO, true, 1725535934442, data1.size());

		std::string data2(13, 'a');
		auto res2 = NewGenerateDataBlockWithHeader(_GenericByteDataType::VIDEO, _VideoCodecType::VIDEO, false, 1725535934460, data2.size());
	}
	end = std::chrono::high_resolution_clock::now();
	cout << "New Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
}
