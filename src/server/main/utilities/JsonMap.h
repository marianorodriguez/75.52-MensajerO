#ifndef JSONMAP_H
#define JSONMAP_H

#include <map>
#include <string>

// TODO mlafroce agregarle más funcionalidad
class JsonMap{
public:
	/**
	 * Constructor default
	 */
	JsonMap();
	/**
	 * Carga las variables del json
	 */
	JsonMap(const std::string& json);
	/**
	 * Devuelve un mapa STL con los contenidos cargados
	 */
	std::map<std::string, std::string> getMap() const;
private:
	std::map<std::string, std::string> map;
};

#endif // JSONMAP_H
