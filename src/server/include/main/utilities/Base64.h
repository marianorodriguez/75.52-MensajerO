#include <string>

/**
 *Usado para encriptar un stream de datos con el metodo de base64
 */
class base64{

public:
	/**
	 *\brief Codifica la informacion pasada.
	 *@param data La informacion a codificar.
	 *@param len Longitud de la informacion.
	 */
	static std::string encode(unsigned char const* data , unsigned int len);

	/**
	 * \brief Decodifica la informacion pasada.
	 * @param s informacion a decodificar.
	 */
	static std::string decode(std::string const& s);

};
