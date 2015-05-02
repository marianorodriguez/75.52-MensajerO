#ifndef SERVER_CONFIGURATION_H
#define SERVER_CONFIGURATION_H
#include <map>
#include <string>

typedef std::map<std::string, std::string> OptionMap;

class ServerOptions{
public:
	/**
	 * Constructor
	 */
	ServerOptions();
	/**
	 * Carga las opciones default y las que se encuentran en el mapa
	 * priorizando las últimas.
	 */
	ServerOptions(const OptionMap& optionMap);
	/**
	 * Obtiene la ruta al directorio del archivo de configuracion
	 */
	std::string getConfigPath();
	/**
	 * Obtiene la ruta al directorio de la base de datos
	 */
	std::string getDatabasePath();
	/**
	 * Obtiene el tiempo entre llamadas al socket (configuracion de mongoose)
	 */
	int getPollDelay();
	/**
	 * Obtiene puerto por el que escucha los requests el servidor
	 */
	int getServerPort();
	/**
	 * Obtiene el tiempo que se considera que el usuario está conectado
	 */
	int getUserAliveTime();
private:
	/**
	 * Carga configuracion default
	 */
	void loadDefaultValues();
	/**
	 * Carga la configuracion desde un archivo en el path configurado
	 */
	OptionMap loadValuesFromFile();
	/**
	 * Interpreta el contenido del archivo de configuracion
	 */
	OptionMap parseJson(std::ifstream& configFile);
	std::string configPath;
	std::string databasePath;
	int pollDelay;
	int serverPort;
	int userAliveTime;
	// Constantes
	static const std::string kDefaultConfigPath;
	static const std::string kDefaultDatabasePath;
	static const int kDefaultPollDelay;
	static const int kDefaultServerPort;
	static const int kDefaultUserAliveTime;
	static const std::string kJsonServerRoot;
};

class ArgsParser{
public:
	/**
	 * Toma los argumentos con los que fue iniciada la aplicación y los
	 * carga en un mapa de strings
	 */
	static OptionMap parseArgs(int argc, char** argv);
	static const std::string kAliveTimeKey;
	static const std::string kConfigKey;
	static const std::string kDatabaseKey;
	static const std::string kPollDelayKey;
	static const std::string kServerPortKey;
	private:
	// TODO mlafroce: sacar esta función a algo más dinámico
	static void printHelp();
};

#endif // SERVER_CONFIGURATION_H
