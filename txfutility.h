/*
*	C++17 
*	
*
*
*
*
*	last-modified date 2019-2-26
*	author : tvman
*/


#pragma once
#include <stdarg.h>
#include <string>
#include <string_view>
#include <vector>
#include <random>
#include <ctime>
#include <functional>
#include <regex>
#include <chrono>
#include <locale.h>
#include <iostream>

namespace TXF
{
	class utility
	{
	public:
		utility() = delete;
		virtual ~utility() = default;

		
		static std::wstring StringToWstring(const std::string str);
		static std::string WstringToString(const std::wstring str);

		// 从路径中提前文件名,扩展名
		static std::pair<std::string, std::string> GetFileNameExt(std::string path);
		
		// Byte To Ascii
		static void ToAscii(char *databytes, int bytes);
		// ascii 转 16进制
		static std::byte Ascii2Hex(char ascii);
		// 计算 L CRC 
		static std::byte LRC8(std::byte * bytes, int count);
		// 计算 CRC16 
		static uint16_t crc16(uint8_t *buffer, uint16_t buffer_length);
		// 随机整数
		static int RandomInt(int Start, int End);
		// 取文件扩展名
		static std::string_view ExtractExtension(std::string_view fileName);
		// 字符串分割
		static int Strtok(const std::string& source, std::string_view strDelimit, std::vector<std::string>& vec);
		// 系统时间
		static std::string GetSystemTime();
		// 验证身份证
		static bool IsCardNOValid(std::string strCardNO);
		// 验证电子邮件
		static bool IsEmailValid(std::string email_address);
		// 验证是否整数
		static bool IsIntegerValid(std::string strValue);
		// 验证是否浮点数
		static bool IsFloatValid(std::string strValue);
	};
}



