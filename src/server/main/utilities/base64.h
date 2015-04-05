#include <string>

/**
 *Used to encrypt a stream of data with base64 method.
 */
class base64{

public:
	/**
	 *\brief Encodes the given data.
	 *@param data The data to encrypt.
	 *@param len Length of the data.
	 */
	static std::string encode(unsigned char const* data , unsigned int len);

	/**
	 * \brief Decodes the given data.
	 * @param s Data to decode.
	 */
	static std::string decode(std::string const& s);

};
