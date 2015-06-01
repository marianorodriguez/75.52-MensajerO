#include <map>
#include <string>
#include <cstdio>

#include "../../include/main/services/QueryParams.h"

const std::string QueryParams::kParamToken("&");
const std::string QueryParams::kKeyValueToken("=");

QueryParams::QueryParams(const std::string& paramString){
	parseParams(paramString);
}

std::map< std::string, std::string >& QueryParams::getParams(){
	return this->params;
}

void QueryParams::parseParams(const std::string& paramString) {
	size_t tokenPos = paramString.find(kParamToken);
	std::string firstParam(paramString.substr(0, tokenPos));
	parseKeyValue(firstParam);
	if ((tokenPos == std::string::npos) || (tokenPos == paramString.length())){
		return;
	}
	parseParams(paramString.substr(tokenPos + 1));
}

void QueryParams::parseKeyValue(const std::string& param){
	size_t tokenPos = param.find(kKeyValueToken);
	if ((tokenPos == std::string::npos) || (tokenPos == param.length())){
		return;
	}
	std::string key(param.substr(0, tokenPos));
	this->params[key] = param.substr(tokenPos + 1);
}
