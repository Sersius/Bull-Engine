#ifndef __MODULEFILESYSTEM_H__
#define __MODULEFILESYSTEM_H__

#include "Module.h"

#include <vector>

struct SDL_RWops;
int close_sdl_rwops(SDL_RWops *rw);

struct aiFileIO;

struct File
{
	File() {}
	File(char* name, int64_t last_mod) { this->name = name;	this->last_mod = last_mod; }

	~File() {}

	std::string name;
	std::string path;
	int64_t last_mod = 0;

};

struct Directory
{
	Directory() {}
	Directory(char* name) { this->name = name; }

	~Directory() {}

	std::string name;
	std::vector<Directory> dir_vec;
	std::vector<File> file_vec;

};

enum File_type
{
	FILE_NONE = 0,
	FILE_MATERIAL,
	FILE_MODEL
};
//struct BASS_FILEPROCS;

class ModuleFileSystem : public Module
{
public:

	ModuleFileSystem(Application* app, bool start_enabled, const char* game_path = nullptr);

	// Destructor
	~ModuleFileSystem();

	// Called before render is available
	bool Init() override;

	// Called before quitting
	bool CleanUp() override;

	// Utility functions
	bool AddPath(const char* path_or_zip);
	bool Exists(const char* file) const;
	bool IsDirectory(const char* file) const;
	void CreateDirectory(const char* directory);
	void DiscoverFiles(const char* directory);
	bool CopyFromOutsideFS(const char* full_path, const char* destination);
	bool Copy(const char* source, const char* destination);
	void SplitFilePath(const char* full_path, std::string* path, std::string* file = nullptr, std::string* extension = nullptr) const;
	void NormalizePath(char* full_path) const;
	void NormalizePath(std::string& full_path) const;

	// Open for Read/Write
	unsigned int Load(const char* path, const char* file, char** buffer) const;
	unsigned int Load(const char* file, char** buffer) const;
	SDL_RWops* Load(const char* file) const;
	void* BassLoad(const char* file) const;

	// IO interfaces for other libs to handle files via PHYSfs
	aiFileIO* GetAssimpIO();
	
	File_type TypeFromExtension(const char* extension);

	unsigned int Save(const char* file, const void* buffer, unsigned int size, bool append = false) const;
	bool SaveUnique(std::string& output, const void* buffer, uint size, const char* path, const char* prefix, const char* extension);
	bool Remove(const char* file);

	const char* GetBasePath() const;
	const char* GetWritePath() const;
	const char* GetReadPaths() const;

private:

	void CreateAssimpIO();
	
public:
	uint resource_num = 0u;
	Directory* resources = nullptr;

private:

	aiFileIO* AssimpIO = nullptr;
};

#endif // __MODULEFILESYSTEM_H__