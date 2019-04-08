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

		// ��·������ǰ�ļ���,��չ��
		static std::pair<std::string, std::string> GetFileNameExt(std::string path);
		
		// Byte To Ascii
		static void ToAscii(char *databytes, int bytes);
		// ascii ת 16����
		static std::byte Ascii2Hex(char ascii);
		// ���� L CRC 
		static std::byte LRC8(std::byte * bytes, int count);
		// ���� CRC16 
		static uint16_t crc16(uint8_t *buffer, uint16_t buffer_length);
		// �������
		static int RandomInt(int Start, int End);
		// ȡ�ļ���չ��
		static std::string_view ExtractExtension(std::string_view fileName);
		// �ַ����ָ�
		static int Strtok(const std::string& source, std::string_view strDelimit, std::vector<std::string>& vec);
		// ϵͳʱ��
		static std::string GetSystemTime();
		// ��֤���֤
		static bool IsCardNOValid(std::string strCardNO);
		// ��֤�����ʼ�
		static bool IsEmailValid(std::string email_address);
		// ��֤�Ƿ�����
		static bool IsIntegerValid(std::string strValue);
		// ��֤�Ƿ񸡵���
		static bool IsFloatValid(std::string strValue);
	};
}



