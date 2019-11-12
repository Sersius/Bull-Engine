#include "Config.h"
#include <vector>
SceneConfig::SceneConfig()
{
	json_root = json_value_init_object();
	root = json_value_get_object(json_root);
}

SceneConfig::~SceneConfig()
{

}

void SceneConfig::SetArray()
{
	json_root = json_value_init_array();
	json_array = json_value_get_array(json_root);

}

bool SceneConfig::SetString(const char * name, const char* value)
{
	bool ret = false;
	if (json_object_set_string(root, name, value))
	{
		ret = true;
	}
	return ret;
}

bool SceneConfig::NewArray(const SceneConfig & conf)
{
	if (json_array != nullptr)
	{
		return json_array_append_value(json_array, json_value_deep_copy(conf.json_root));
	}

	else
	{
		return false;
	}
}

void SceneConfig::Save(const char* scene_name)
{
	bool returned = false;
	std::string extension = ".json";
	std::string final_name = scene_name + extension;
	json_serialize_to_file_pretty(json_root, final_name.c_str());


}