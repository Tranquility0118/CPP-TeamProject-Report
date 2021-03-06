#pragma once
#pragma comment(lib,"Ws2_32.lib")
#include <WinSock2.h>
#include <thread>

const int MAX_BUF = 4096;
const unsigned int UM_DISCONNECT_SERVER	= WM_USER + 1;
const unsigned int UM_RECV_TEXT			= WM_USER + 2;
const unsigned int UM_RECV_IMAGE		= WM_USER + 3;
const unsigned int UM_RECV_FILE			= WM_USER + 4;
const unsigned int UM_RECV_IMAGE_NAME	= WM_USER + 5;
const unsigned int UM_RECV_FILE_NAME	= WM_USER + 6;


enum DATA_TYPE  { _NICK, _TEXT, _IMAGE_NAME, _IMAGE, _FILE, _FILE_NAME, _UNKNOWN};

class Client : public CWnd
{
public:
	Client(CWnd* pParent);
	~Client();

public:
	
	static std::wstring getMyip();
	bool connectServer(std::wstring ip, int port);
	void disconnectServer();

	bool sendText(const std::wstring& msg, const DATA_TYPE& type = _TEXT);
	bool sendNick(const std::wstring& msg, const DATA_TYPE& type = _NICK);
	bool sendFile(const std::wstring& file_name, const std::wstring& file_path, const std::wstring& file_ext, const DATA_TYPE& type);


	static const std::string UnicodeToMultibyte(const unsigned int& code_page, const std::wstring& strWide);
	static const std::wstring MultibyteToUnicode(const unsigned int& code_page, const char* buf, const int& size);

	void recvFinished(const DATA_TYPE& type, const char* buf, const size_t& recv_size, const size_t& data_size);

	bool sendSocket(const char* buf, const size_t& size);

	char* ImageToBytes(const std::wstring& file_path, const std::wstring& file_ext, size_t& size);
	char* FileToBytes(const std::wstring& file_path, const std::wstring& file_ext, size_t& size);

	std::wstring getNick() { return m_nick; }

private:
	SOCKET client_sock;
	SOCKADDR_IN addr;
	std::thread *m_pRecvThread, *m_pSendThread;
	std::wstring m_nick;

public:
	CWnd* m_pParent;
	bool bRecv, bSend;
};

