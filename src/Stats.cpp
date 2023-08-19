#include "Stats.h"

Stats::Stats() {
	this->InitTime = this->GetMilliSinceEpoch();

	if (!std::filesystem::is_directory("./temp")) {
		std::filesystem::create_directory("./temp");
	}
	this->m_FilePath = std::filesystem::path("./temp/" + this->GenerateID()).string();

	if (!std::filesystem::is_directory("./saves")) {
		std::filesystem::create_directory("./saves");
	}

	this->m_File.open(this->m_FilePath, std::ios::binary | std::ios::out | std::ios::in | std::ios::trunc);

	this->SetWritePos(0);
	this->m_File.write((new char[C_DATAPOS] {0}), C_DATAPOS);

	this->SetWritePos(0);
	this->SetWritePos(C_HASHPOS);
	this->m_File.write((new char[C_HASHLEN] {0}), C_HASHLEN);

	this->SetWritePos(C_SAVETIMEPOS);
	this->m_File.write((char*)&this->InitTime, C_SAVETIMELEN);

	this->UpdateHash();
}

Stats::~Stats() {
	this->m_File.close();
}

std::string Stats::GenerateID() const {
	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
	UUIDv4::UUID uuid = uuidGenerator.getUUID();
	return uuid.str();
}

uint64_t Stats::GetMilliSinceEpoch() const {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int32_t Stats::GetReadPos() {
	return this->m_File.tellg();
}

int32_t Stats::GetWritePos() {
	return this->m_File.tellp();
}

void Stats::SetReadPos(int32_t ReadOffsetBytes, int32_t StartPosBytes = 0) {
	this->m_File.seekg(ReadOffsetBytes, StartPosBytes);
}

void Stats::SetWritePos(int32_t WriteOffsetBytes) {
	this->m_File.seekp(WriteOffsetBytes);
}

int32_t Stats::GetFileSize() {
	int32_t CurrRPos = GetReadPos();
	this->SetReadPos(0, this->m_File.end);
	int32_t FileSize = GetReadPos();
	this->SetReadPos(CurrRPos);
	return FileSize;
}

std::string Stats::GetHash() {
	int32_t CurrRPos = this->GetReadPos();
	int32_t CurrWPos = this->GetWritePos();
	this->SetReadPos(0, this->m_File.end);
	int32_t FileSize = this->GetFileSize();
	char* Buf = new char[FileSize - C_HASHLEN] {0};
	this->SetReadPos(C_HASHLEN);
	this->m_File.read(Buf, FileSize - C_HASHLEN);
	this->SetReadPos(CurrRPos);
	
	std::string Content = std::string(Buf, FileSize - C_HASHLEN);
	
	SHA256 SHA;
	SHA.update(Content);
	uint8_t* Digest = SHA.digest();

	std::string Hash = SHA256::toString(Digest);
	delete[] Digest;
	delete[] Buf;
	return Hash;

}

void Stats::UpdateHash() {
	std::string Hash = this->GetHash();
	int32_t CurrWPos = this->GetWritePos();
	this->SetWritePos(0);
	this->m_File.write(Hash.c_str(), Hash.length());
	this->SetWritePos(CurrWPos);
}

void Stats::AddData(char* Data, int32_t Size, bool AutoSpacing, int32_t WritePos) {
	int32_t CurrPos = this->GetWritePos();
	WritePos == -1 ? this->SetWritePos(this->CurrDataPos) : this->SetWritePos(WritePos);
	this->m_File.write(Data, Size);
	if (WritePos == -1) {
		this->CurrDataPos += Size;
		this->CurrDataPos = AutoSpacing ? (this->CurrDataPos % 16 != 0) * (this->CurrDataPos / 16 + 1) * 16 : this->CurrDataPos;
	}
	else {
		this->SetWritePos(CurrPos);
	}
	this->UpdateHash();
}

uint64_t Stats::GetMilliSinceInit() const {
	return this->GetMilliSinceEpoch() - this->InitTime;
}

void Stats::Save(std::string FileName) {
	if (!std::filesystem::is_directory("./saves")) {
		std::filesystem::create_directory("./saves");
	}
	this->m_CachePath = this->m_FilePath;
	if (std::filesystem::is_regular_file("./saves/" + FileName)) {
		this->m_FilePath = std::filesystem::path("./saves/" + FileName + "_" + this->GenerateID()).string();
	}
	
	std::filesystem::copy_file(std::filesystem::path(this->m_CachePath), std::filesystem::path(this->m_FilePath));
}