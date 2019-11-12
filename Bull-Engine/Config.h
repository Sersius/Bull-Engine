#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Globals.h"
#include "JSON/parson.h"

struct json_object_t;
typedef struct json_object_t JSON_Object;

struct json_value_t;
typedef struct json_value_t  JSON_Value;

struct json_array_t;
typedef struct json_array_t  JSON_Array;

class SceneConfig
{
public:
	SceneConfig();
	~SceneConfig();

	void SetArray();
	bool SetString(const char* name, const char* value = "");
	bool NewArray(const SceneConfig &conf);
	void Save(const char* name_scene);
private:
	JSON_Array*		json_array = nullptr;
	JSON_Value*		json_root = nullptr;
	JSON_Object*	root = nullptr;
};

#endif