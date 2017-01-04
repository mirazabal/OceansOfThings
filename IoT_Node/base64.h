/*
 * base64.h
 *
 *  Created on: 2016 eka. 29
 *      Author: mikel
 */

#ifndef BASE64_H_
#define BASE64_H_

#include <string>

namespace mirazabal {

class base64 {
public:
	base64();
	virtual ~base64();

	std::string encode(unsigned char const* bytes_to_encode, unsigned int in_len);
	std::string decode(std::string const& encoded_string);

};

} /* namespace mirazabal */

#endif /* BASE64_H_ */
