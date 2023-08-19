#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "SHA256.h"
#include <random>
#include <UUID4/uuid_v4.h>
#include <UUID4/endianness.h>
#include <filesystem>
#include <chrono>

class Stats {
private:
	int32_t CurrDataPos = 256;
	uint64_t InitTime = 0;

	std::string GenerateID() const;
	uint64_t GetMilliSinceEpoch() const;
	int32_t GetReadPos();
	int32_t GetWritePos();
	void SetReadPos(int32_t ReadPosBytes, int32_t StartPosBytes);
	void SetWritePos(int32_t WriteOffsetBytes);
	int32_t GetFileSize();
	std::string GetHash();
	void UpdateHash();

	std::fstream m_File;
	std::string m_FilePath;
	std::string m_CachePath;
public:

	const int32_t C_HASHPOS = 1;
	const int32_t C_HASHLEN = 64;
	const int32_t C_SAVETIMEPOS = 64;
	const int32_t C_SAVETIMELEN = 8;
	const int32_t C_MAXLIVESPOS = 72;
	const int32_t C_MAXLIVESLEN = 1;
	const int32_t C_CORRECTVALUESPOS = 73;
	const int32_t C_CORRECTVALUESLEN = 81;
	const int32_t C_DATAPOS = 256;

	Stats();
	~Stats();
	void AddData(char* Data, int32_t Size, bool AutoSpacing = true, int32_t WritePos = -1);
	uint64_t GetMilliSinceInit() const;
	void Save(std::string FileName);
};