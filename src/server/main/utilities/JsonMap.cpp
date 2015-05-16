#include "JsonMap.h"
#include "json.h"

#include <iostream>

JsonMap::JsonMap(){
}

JsonMap::JsonMap(const std::string& json){
	Json::Reader jsonReader;
	Json::Value jsonRoot(json);
	bool parsingSuccessful = jsonReader.parse(json, jsonRoot, false);
	//TODO esto está hardcodeado para los mapas de servicio, revisar formato de jsons
	Json::ValueIterator it = jsonRoot.begin();
	for (; it != jsonRoot.end(); ++it){
		this->map[it.key().asString()] = it->asString();
	}
}

std::map< std::string, std::string > JsonMap::getMap() const{
	return this->map;
}
