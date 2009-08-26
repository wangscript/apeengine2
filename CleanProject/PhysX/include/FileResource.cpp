#include "FileResource.h"

namespace Nebula {

	FileResource::FileResource(const std::string& _path, ResourceAccess _r_w_or_rw) :
	mFile(0), mSize(0) {
		reuse(_path, _r_w_or_rw);
	}

	FileResource::~FileResource() {
		close();
	}

	std::string  FileResource::getResourceIdentifier() const {
		return mResourceIdentifier;
	}

	void FileResource::close() {

		if(mFile)
			fclose(mFile);
		mFile = 0;

	}

	void FileResource::seek(long pos) {
		fseek(mFile, pos, SEEK_SET);
	}

	void FileResource::skip(long pos) {
		fseek(mFile, pos, SEEK_CUR);
	}

	size_t FileResource::tell() const {
		return ftell(mFile);
	}

	void FileResource::reuse(const std::string& _path, ResourceAccess _r_w_or_rw) {
		
		if (mFile)
			close();

		bool reading = true;

		mResourceIdentifier = _path;

		std::string filename = _path;

		if (_r_w_or_rw == RA_ReadWrite || _r_w_or_rw == RA_Write)
			reading = false;

		#ifdef NX_PLATFORM_WINDOWS
			fopen_s(&mFile,filename.c_str(), reading ? "rb" : "wb");
		#else
			mFile = fopen(filename.c_str(), reading ? "rb" : "wb");
		#endif

		if (reading) {
			fseek(mFile, 0, SEEK_END);
			mSize = ftell(mFile);
			fseek(mFile, 0, SEEK_SET);
		}

	}

	NxU32 FileResource::size() const {
		return mSize;
	}

	void FileResource::rewind() {
		fseek(mFile, 0, SEEK_SET);
	}

	void FileResource::writeUChar(unsigned char data) {
		size_t w = fwrite(&data, sizeof(unsigned char), 1, mFile);
	}

	void FileResource::writeUShort(NxU16 data) {
		size_t w = fwrite(&data, sizeof(NxU16), 1, mFile);
	}

	void FileResource::writeUInt(unsigned int data) {
		size_t w = fwrite(&data, sizeof(unsigned int), 1, mFile);
	}

	void FileResource::writeFloat(float data) {
		size_t w = fwrite(&data, sizeof(float), 1, mFile);
	}

	void FileResource::writeDouble(double data) {
		size_t w = fwrite(&data, sizeof(double), 1, mFile);
	}

	void FileResource::writeString(std::string s) {
		for (NxU32 i=0;i < s.length();i++) {
			writeUChar(s[i]);
		}
		writeUChar(0);
	}

	void FileResource::write(const void* data, size_t l) {
		size_t w = fwrite(data, l, 1, mFile);
	}

	unsigned char FileResource::getUChar() const {
		unsigned char d=0;fread(&d, sizeof(unsigned char), 1, mFile);
		return d;
	}

	NxU16 FileResource::getShort() const {
		NxU16 d=0;fread(&d, sizeof(NxU16), 1, mFile);
		return d;
	}

	unsigned int FileResource::getUInt() const{
		unsigned int d=0;fread(&d, sizeof(unsigned int), 1, mFile);
		return d;
	}

	float FileResource::getFloat() const{
		float d=0;fread(&d, sizeof(float), 1, mFile);
		return d;
	}

	double FileResource::getDouble() const{
		double d=0;fread(&d, sizeof(double), 1, mFile);
		return d;
	}

	std::string FileResource::getString()	const {

		std::stringstream ss;
		char c;

		while (!feof(mFile)) {
			fread(&c, sizeof(NxU8), 1, mFile);
			if (c == 0) break;
			ss << c;
		}

		return ss.str();
	}

	void FileResource::get(void* buffer, size_t size) const {
		fread(buffer, size, 1, mFile);
	}

	NxU8   FileResource::readByte() const {
		return getUChar();
	}

	NxU16   FileResource::readWord() const {
		return getShort();
	}

	NxU32   FileResource::readDword() const {
		return getUInt();
	}

	NxReal   FileResource::readFloat() const {
		return getFloat();
	}

	double   FileResource::readDouble() const {
		return getDouble();
	}

	void   FileResource::readBuffer(void* buffer, NxU32 size) const {
		return get(buffer, size);
	}

	NxStream&   FileResource::storeByte(NxU8 b) {
		writeUChar(b);
		return *this;
	}

	NxStream&   FileResource::storeWord(NxU16 w) {
		writeUShort(w);
		return *this;
	}

	NxStream&   FileResource::storeDword(NxU32 d) {
		writeUInt(d);
		return *this;
	}

	NxStream&   FileResource::storeFloat(NxReal f) {
		writeFloat(f);
		return *this;
	}

	NxStream&   FileResource::storeDouble(NxF64 f) {
		writeDouble(f);
		return *this;
	}

	NxStream&   FileResource::storeBuffer(const void* buffer, NxU32 size) {
		write(buffer, size);
		return *this;
	}

} // end namespace