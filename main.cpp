#include <iostream>
#include <string>
#include <memory>

using namespace std;


std::string ToNarrow( const std::wstring &wide_byte );
std::wstring ToWiden( const std::string &multi_byte );




int main( void )
{
	std::string str = "abc";
	auto wb_str = ToWiden( str );
	std::wcout << "WIDE: " << wb_str << std::endl;
	auto mb_str = ToNarrow( wb_str );
	std::cout << "NARROT: " << mb_str << std::endl;

	return 0;
}


/**
 * @brief Change wide byte string to multi byte string.
 *
 * @note Use std::locale() before execute this method.
 * @param wide_byte[in] converted string
 * @return multi byte string instance
 */
std::string ToNarrow( const std::wstring &wide_byte )
{
	constexpr int NULL_LENGTH = 1;
	const int MB_LENGTH = wide_byte.length() * MB_CUR_MAX + NULL_LENGTH;
	auto multi_byte = std::make_unique<char[]>( MB_LENGTH );

	wcstombs( multi_byte.get(), wide_byte.c_str(), MB_LENGTH );
	return std::string( multi_byte.get() );
}


/**
 * @brief Change multi byte string to wide byte string.
 *
 * @note Use std::locale() before execute this method.
 * @param multi_byte[in] converted string
 * @return wide byte string instance
 */
std::wstring ToWiden( const std::string &multi_byte )
{
	constexpr int NULL_LENGTH = 1;
	const int WB_LENGTH = multi_byte.length() + NULL_LENGTH;
	auto wide_byte = std::make_unique<wchar_t[]>( WB_LENGTH );
	mbstowcs( wide_byte.get(), multi_byte.c_str(), WB_LENGTH );
	return std::wstring( wide_byte.get() );
}