#include <iostream>
#include <string>
#include <sstream>
#include <locale>
#include <codecvt>

#include <comdef.h>
#include <winscard.h>

static const WCHAR* listW[] = { nullptr, L"SCard$AllReaders\000", L"SCard$DefaultReaders\000",
	                            L"SCard$LocalReaders\000", L"SCard$SystemReaders\000" };
static const char* listA[] = { nullptr, "SCard$AllReaders\000", "SCard$DefaultReaders\000",
	                           "SCard$LocalReaders\000", "SCard$SystemReaders\000" };

static std::string scope2str(DWORD scope)
{
	switch (scope)
	{
		case SCARD_SCOPE_USER:
			return "SCARD_SCOPE_USER";
		case SCARD_SCOPE_TERMINAL:
			return "SCARD_SCOPE_TERMINAL";
		case SCARD_SCOPE_SYSTEM:
			return "SCARD_SCOPE_SYSTEM";
		default:
			return "UNKNOWN";
	}
}

static std::string err2str(LONG code)
{
	switch (code)
	{
		case ERROR_BROKEN_PIPE:
			return "ERROR_BROKEN_PIPE";
		case SCARD_E_BAD_SEEK:
			return "SCARD_E_BAD_SEEK";
		case SCARD_E_CANCELLED:
			return "SCARD_E_CANCELLED";
		case SCARD_E_CANT_DISPOSE:
			return "SCARD_E_CANT_DISPOSE";
		case SCARD_E_CARD_UNSUPPORTED:
			return "SCARD_E_CARD_UNSUPPORTED";
		case SCARD_E_CERTIFICATE_UNAVAILABLE:
			return "SCARD_E_CERTIFICATE_UNAVAILABLE";
		case SCARD_E_COMM_DATA_LOST:
			return "SCARD_E_COMM_DATA_LOST";
		case SCARD_E_DIR_NOT_FOUND:
			return "SCARD_E_DIR_NOT_FOUND";
		case SCARD_E_DUPLICATE_READER:
			return "SCARD_E_DUPLICATE_READER";
		case SCARD_E_FILE_NOT_FOUND:
			return "SCARD_E_FILE_NOT_FOUND";
		case SCARD_E_ICC_CREATEORDER:
			return "SCARD_E_ICC_CREATEORDER";
		case SCARD_E_ICC_INSTALLATION:
			return "SCARD_E_ICC_INSTALLATION";
		case SCARD_E_INSUFFICIENT_BUFFER:
			return "SCARD_E_INSUFFICIENT_BUFFER";
		case SCARD_E_INVALID_ATR:
			return "SCARD_E_INVALID_ATR";
		case SCARD_E_INVALID_CHV:
			return "SCARD_E_INVALID_CHV";
		case SCARD_E_INVALID_HANDLE:
			return "SCARD_E_INVALID_HANDLE";
		case SCARD_E_INVALID_PARAMETER:
			return "SCARD_E_INVALID_PARAMETER";
		case SCARD_E_INVALID_TARGET:
			return "SCARD_E_INVALID_TARGET";
		case SCARD_E_INVALID_VALUE:
			return "SCARD_E_INVALID_VALUE";
		case SCARD_E_NO_ACCESS:
			return "SCARD_E_NO_ACCESS";
		case SCARD_E_NO_DIR:
			return "SCARD_E_NO_DIR";
		case SCARD_E_NO_FILE:
			return "SCARD_E_NO_FILE";
		case SCARD_E_NO_KEY_CONTAINER:
			return "SCARD_E_NO_KEY_CONTAINER";
		case SCARD_E_NO_MEMORY:
			return "SCARD_E_NO_MEMORY";
		case SCARD_E_NO_PIN_CACHE:
			return "SCARD_E_NO_PIN_CACHE";
		case SCARD_E_NO_READERS_AVAILABLE:
			return "SCARD_E_NO_READERS_AVAILABLE";
		case SCARD_E_NO_SERVICE:
			return "SCARD_E_NO_SERVICE";
		case SCARD_E_NO_SMARTCARD:
			return "SCARD_E_NO_SMARTCARD";
		case SCARD_E_NO_SUCH_CERTIFICATE:
			return "SCARD_E_NO_SUCH_CERTIFICATE";
		case SCARD_E_NOT_READY:
			return "SCARD_E_NOT_READY";
		case SCARD_E_NOT_TRANSACTED:
			return "SCARD_E_NOT_TRANSACTED";
		case SCARD_E_PCI_TOO_SMALL:
			return "SCARD_E_PCI_TOO_SMALL";
		case SCARD_E_PIN_CACHE_EXPIRED:
			return "SCARD_E_PIN_CACHE_EXPIRED";
		case SCARD_E_PROTO_MISMATCH:
			return "SCARD_E_PROTO_MISMATCH";
		case SCARD_E_READ_ONLY_CARD:
			return "SCARD_E_READ_ONLY_CARD";
		case SCARD_E_READER_UNAVAILABLE:
			return "SCARD_E_READER_UNAVAILABLE";
		case SCARD_E_READER_UNSUPPORTED:
			return "SCARD_E_READER_UNSUPPORTED";
		case SCARD_E_SERVER_TOO_BUSY:
			return "SCARD_E_SERVER_TOO_BUSY";
		case SCARD_E_SERVICE_STOPPED:
			return "SCARD_E_SERVICE_STOPPED";
		case SCARD_E_SHARING_VIOLATION:
			return "SCARD_E_SHARING_VIOLATION";
		case SCARD_E_SYSTEM_CANCELLED:
			return "SCARD_E_SYSTEM_CANCELLED";
		case SCARD_E_TIMEOUT:
			return "SCARD_E_TIMEOUT";
		case SCARD_E_UNEXPECTED:
			return "SCARD_E_UNEXPECTED";
		case SCARD_E_UNKNOWN_CARD:
			return "SCARD_E_UNKNOWN_CARD";
		case SCARD_E_UNKNOWN_READER:
			return "SCARD_E_UNKNOWN_READER";
		case SCARD_E_UNKNOWN_RES_MNG:
			return "SCARD_E_UNKNOWN_RES_MNG";
		case SCARD_E_UNSUPPORTED_FEATURE:
			return "SCARD_E_UNSUPPORTED_FEATURE";
		case SCARD_E_WRITE_TOO_MANY:
			return "SCARD_E_WRITE_TOO_MANY";
		case SCARD_F_COMM_ERROR:
			return "SCARD_F_COMM_ERROR";
		case SCARD_F_INTERNAL_ERROR:
			return "SCARD_F_INTERNAL_ERROR";
		case SCARD_F_UNKNOWN_ERROR:
			return "SCARD_F_UNKNOWN_ERROR";
		case SCARD_F_WAITED_TOO_LONG:
			return "SCARD_F_WAITED_TOO_LONG";
		case SCARD_P_SHUTDOWN:
			return "SCARD_P_SHUTDOWN";
		case SCARD_S_SUCCESS:
			return "SCARD_S_SUCCESS";
		case SCARD_W_CANCELLED_BY_USER:
			return "SCARD_W_CANCELLED_BY_USER";
		case SCARD_W_CACHE_ITEM_NOT_FOUND:
			return "SCARD_W_CACHE_ITEM_NOT_FOUND";
		case SCARD_W_CACHE_ITEM_STALE:
			return "SCARD_W_CACHE_ITEM_STALE";
		case SCARD_W_CACHE_ITEM_TOO_BIG:
			return "SCARD_W_CACHE_ITEM_TOO_BIG";
		case SCARD_W_CARD_NOT_AUTHENTICATED:
			return "SCARD_W_CARD_NOT_AUTHENTICATED";
		case SCARD_W_CHV_BLOCKED:
			return "SCARD_W_CHV_BLOCKED";
		case SCARD_W_EOF:
			return "SCARD_W_EOF";
		case SCARD_W_REMOVED_CARD:
			return "SCARD_W_REMOVED_CARD";
		case SCARD_W_RESET_CARD:
			return "SCARD_W_RESET_CARD";
		case SCARD_W_SECURITY_VIOLATION:
			return "SCARD_W_SECURITY_VIOLATION";
		case SCARD_W_UNPOWERED_CARD:
			return "SCARD_W_UNPOWERED_CARD";
		case SCARD_W_UNRESPONSIVE_CARD:
			return "SCARD_W_UNRESPONSIVE_CARD";
		case SCARD_W_UNSUPPORTED_CARD:
			return "SCARD_W_UNSUPPORTED_CARD";
		case SCARD_W_WRONG_CHV:
			return "SCARD_W_WRONG_CHV";
		default:
			return "UNKNOWN";
	}
}

static std::wstring err2wstr(LONG code)
{
	auto str = err2str(code);
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}

static bool test_valid(SCARDCONTEXT context)
{
	auto rc = SCardIsValidContext(context);
	if (rc)
		std::cerr << "SCardIsValidContext failed with " << err2str(rc) << std::endl;
	return true;
}

static void print_list_readers_a(LONG rc, LPCSTR cur, LPCSTR mszReaders,
                                 DWORD chReaders) {
  std::string c = cur ? cur : "nullptr";
  if (rc != SCARD_S_SUCCESS) {
    std::cerr << "SCardListReadersA [" << c << "] failed with " << err2str(rc)
              << std::endl;
  } else {
    auto start = mszReaders;
    auto end = &mszReaders[chReaders];

    std::cout << "SCardListReadersA [" << c << "] " << chReaders << " [";
    while (start < end) {
      std::cout << start << ", ";
      start += strnlen(start, chReaders) + 2;
    }
    std::cout << "]" << std::endl;
  }
}

static bool test_list_readers_a(SCARDCONTEXT context)
{
	for (auto cur : listA)
	{
		LPSTR mszReaders = nullptr;
		DWORD chReaders = SCARD_AUTOALLOCATE;
		auto rc = SCardListReadersA(context, cur, reinterpret_cast<LPSTR>(&mszReaders), &chReaders);
                print_list_readers_a(rc, cur, mszReaders, chReaders);
                SCardFreeMemory(context, mszReaders);
                for (DWORD x = 0; x < 256; x += 13) {
                  CHAR mszReaders[1024] = {};
                  DWORD chReaders = x;
                  auto rc =
                      SCardListReadersA(context, cur, mszReaders, &chReaders);
                  print_list_readers_a(rc, cur, mszReaders, chReaders);
                }
        }

	return true;
}

static void print_list_readers_w(LONG rc, LPCWSTR cur, LPCWSTR mszReaders,
                                 DWORD chReaders) {
  std::wstring c = cur ? cur : L"nullptr";
  if (rc != SCARD_S_SUCCESS) {
    std::wcerr << L"SCardListReadersW [" << c;
    std::cerr << "] failed with " << err2str(rc) << std::endl;
  } else {
    auto start = mszReaders;
    auto end = &mszReaders[chReaders];

    std::wcout << L"SCardListReadersW [" << c << L"] " << chReaders << L" [";
    while (start < end) {
      std::wcout << start << L", ";
      start += wcsnlen(start, chReaders) + 2;
    }
    std::wcout << L"]" << std::endl;
  }
}

static bool test_list_readers_w(SCARDCONTEXT context)
{
	for (auto cur : listW)
	{
		LPWSTR mszReaders = nullptr;
		DWORD chReaders = SCARD_AUTOALLOCATE;
		auto rc =
		    SCardListReadersW(context, cur, reinterpret_cast<LPWSTR>(&mszReaders), &chReaders);
                print_list_readers_w(rc, cur, mszReaders, chReaders);
                SCardFreeMemory(context, mszReaders);
                for (DWORD x = 0; x < 246; x += 11) {
                  WCHAR mszReaders[1024] = {};
                  DWORD chReaders = x;
                  auto rc = SCardListReadersW(
                      context, cur, reinterpret_cast<LPWSTR>(&mszReaders),
                      &chReaders);
                  print_list_readers_w(rc, cur, mszReaders, chReaders);
                }
        }

	return true;
}

static bool test_list_reader_groups_a(SCARDCONTEXT context)
{
	LPSTR mszReaders = nullptr;
	DWORD chReaders = SCARD_AUTOALLOCATE;
	auto rc = SCardListReaderGroupsA(context, reinterpret_cast<LPSTR>(&mszReaders), &chReaders);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardListReaderGroupsA failed with " << err2str(rc) << std::endl;
	}
	else
	{
		auto start = mszReaders;
		auto end = &mszReaders[chReaders];

		std::cout << "SCardListReaderGroupsA " << chReaders << " [";
		while (start < end)
		{
			std::cout << start << ", ";
			start += strnlen(start, chReaders) + 2;
		}
		std::cout << "]" << std::endl;
	}
	SCardFreeMemory(context, mszReaders);

	return true;
}

static bool test_list_reader_groups_w(SCARDCONTEXT context)
{
	LPWSTR mszReaders = nullptr;
	DWORD chReaders = SCARD_AUTOALLOCATE;
	auto rc = SCardListReaderGroupsW(context, reinterpret_cast<LPWSTR>(&mszReaders), &chReaders);
	if (rc != SCARD_S_SUCCESS)
	{
		std::wcerr << L"SCardListReaderGroupsW failed with " << err2wstr(rc) << std::endl;
	}
	else
	{
		auto start = mszReaders;
		auto end = &mszReaders[chReaders];

		std::wcout << L"SCardListReaderGroupsW " << chReaders << L" [";
		while (start < end)
		{
			std::wcout << start << L", ";
			start += wcsnlen(start, chReaders) + 2;
		}
		std::wcout << L"]" << std::endl;
	}
	SCardFreeMemory(context, mszReaders);

	return true;
}

static bool test_introduce_forget_reader_groups_a(SCARDCONTEXT context)
{
	LPSTR group = "somefancygroup";

	auto rc = SCardIntroduceReaderGroupA(context, group);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardIntroduceReaderGroupA failed with " << err2str(rc) << std::endl;
		return false;
	}
	else
	{
		rc = SCardForgetReaderGroupA(context, group);
		if (rc != SCARD_S_SUCCESS)
		{
			std::cerr << "SCardForgetReaderGroupA failed with " << err2str(rc) << std::endl;
			return false;
		}
		return true;
	}
}

static bool test_introduce_forget_reader_groups_w(SCARDCONTEXT context)
{
	LPWSTR group = L"somefancygroup";

	auto rc = SCardIntroduceReaderGroupW(context, group);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardIntroduceReaderGroupW failed with " << err2str(rc) << std::endl;
		return false;
	}
	else
	{
		rc = SCardForgetReaderGroupW(context, group);
		if (rc != SCARD_S_SUCCESS)
		{
			std::cerr << "SCardForgetReaderGroupW failed with " << err2str(rc) << std::endl;
			return false;
		}
		return true;
	}
}

static bool test_introduce_forget_reader_a(SCARDCONTEXT context)
{
	LPSTR reader = "somefancygroup";
	LPSTR device = "otherfancy";

	auto rc = SCardIntroduceReaderA(context, reader, device);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardIntroduceReaderA failed with " << err2str(rc) << std::endl;
		return false;
	}
	else
	{
		rc = SCardForgetReaderA(context, reader);
		if (rc != SCARD_S_SUCCESS)
		{
			std::cerr << "SCardForgetReaderA failed with " << err2str(rc) << std::endl;
			return false;
		}
		return true;
	}
}

static bool test_introduce_forget_reader_w(SCARDCONTEXT context)
{
	LPWSTR reader = L"somefancygroup";
	LPWSTR device = L"otherfancy";

	auto rc = SCardIntroduceReaderW(context, reader, device);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardIntroduceReaderW failed with " << err2str(rc) << std::endl;
		return false;
	}
	else
	{
		rc = SCardForgetReaderW(context, reader);
		if (rc != SCARD_S_SUCCESS)
		{
			std::cerr << "SCardForgetReaderW failed with " << err2str(rc) << std::endl;
			return false;
		}
		return true;
	}
}

static bool test_list_cards_a(SCARDCONTEXT context)
{
	DWORD chCards = SCARD_AUTOALLOCATE;
	LPSTR mszCards = nullptr;
	auto rc =
	    SCardListCardsA(context, nullptr, nullptr, 0, reinterpret_cast<LPSTR>(&mszCards), &chCards);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardListCardsA failed with " << err2str(rc) << std::endl;
	}
	else
	{
		auto start = mszCards;
		auto end = &mszCards[chCards];
		std::cout << "SCardListCardsA " << chCards << " [";
		while (start < end)
		{
			std::cout << start << ", ";
			start += strnlen(start, chCards) + 2;
		}
		std::cout << "]" << std::endl;
	}
	return true;
}

static bool test_list_cards_w(SCARDCONTEXT context)
{
	DWORD chCards = SCARD_AUTOALLOCATE;
	LPWSTR mszCards = nullptr;
	auto rc = SCardListCardsW(context, nullptr, nullptr, 0, reinterpret_cast<LPWSTR>(&mszCards),
	                          &chCards);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardListCardsW failed with " << err2str(rc) << std::endl;
	}
	else
	{
		auto start = mszCards;
		auto end = &mszCards[chCards];
		std::cout << "SCardListCardsW " << chCards << " [";
		while (start < end)
		{
			std::wcout << start << L", ";
			start += wcsnlen(start, chCards) + 2;
		}
		std::cout << "]" << std::endl;
	}
	return true;
}

static bool test_cache_a(SCARDCONTEXT context)
{
	BYTE wdata[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	const DWORD wdatalen = sizeof(wdata);
	BYTE data[32] = {};
	DWORD datalen = sizeof(data);
	LPSTR name = "testdata";
	UUID id = {};

	auto rc = SCardWriteCacheA(context, &id, 0, name, wdata, wdatalen);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardWriteCacheA failed with " << err2str(rc) << std::endl;
		return false;
	}

	rc = SCardReadCacheA(context, &id, 0, name, data, &datalen);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardReadCacheA failed with " << err2str(rc) << std::endl;
		return false;
	}

	if (wdatalen != datalen)
	{
		std::cerr << "SCardWriteCacheA wrote " << wdatalen << "bytes, SCardReadCacheA read "
		          << datalen << "bytes" << std::endl;
		return false;
	}

	if (memcmp(wdata, data, wdatalen) != 0)
	{
		std::cerr << "SCardWriteCacheA / SCardReadCacheA data corruption detected" << std::endl;
		return false;
	}

	return true;
}

static bool test_cache_w(SCARDCONTEXT context)
{
	BYTE wdata[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	const DWORD wdatalen = sizeof(wdata);
	BYTE data[32] = {};
	DWORD datalen = sizeof(data);
	LPWSTR name = L"testdata";
	UUID id = {};

	auto rc = SCardWriteCacheW(context, &id, 0, name, wdata, wdatalen);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardWriteCacheW failed with " << err2str(rc) << std::endl;
		return false;
	}

	rc = SCardReadCacheW(context, &id, 0, name, data, &datalen);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardReadCacheW failed with " << err2str(rc) << std::endl;
		return false;
	}

	if (wdatalen != datalen)
	{
		std::cerr << "SCardReadCacheW wrote " << wdatalen << "bytes, SCardReadCacheW read "
		          << datalen << "bytes" << std::endl;
		return false;
	}

	if (memcmp(wdata, data, wdatalen) != 0)
	{
		std::cerr << "SCardReadCacheW / SCardReadCacheW data corruption detected" << std::endl;
		return false;
	}

	return true;
}

static bool test_started_event() {
  auto handle = SCardAccessStartedEvent();
  SCardReleaseStartedEvent();
  return true;
}

static bool test_reader_icon_a(SCARDCONTEXT context)
{
	LPSTR name = "Gemalto PC Twin Reader 00 00\0\0";
	LPBYTE pbIcon = nullptr;
	DWORD cbIcon = SCARD_AUTOALLOCATE;

	auto rc = SCardGetReaderIconA(context, name, reinterpret_cast<LPBYTE>(&pbIcon), &cbIcon);
	SCardFreeMemory(context, pbIcon);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardGetReaderIconA failed with " << err2str(rc) << std::endl;
		return false;
	}

        for (DWORD x = 0; x < 256; x++) {
          LPBYTE pbIcon = nullptr;
          DWORD cbIcon = x;
          auto rc = SCardGetReaderIconA(context, name, pbIcon, &cbIcon);
          if (rc != SCARD_S_SUCCESS) {
            std::cerr << "SCardGetReaderIconW failed with " << err2str(rc)
                      << std::endl;
            return false;
          }
        }

        return true;
}

static bool test_reader_icon_w(SCARDCONTEXT context)
{
	LPWSTR name = L"Gemalto PC Twin Reader 00 00\0\0";
	LPBYTE pbIcon = nullptr;
	DWORD cbIcon = SCARD_AUTOALLOCATE;

	auto rc = SCardGetReaderIconW(context, name, reinterpret_cast<LPBYTE>(&pbIcon), &cbIcon);
	SCardFreeMemory(context, pbIcon);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardGetReaderIconW failed with " << err2str(rc) << std::endl;
		return false;
	}

        for (DWORD x = 0; x < 256; x++) {
          LPBYTE pbIcon = nullptr;
          DWORD cbIcon = x;
          auto rc = SCardGetReaderIconW(context, name, pbIcon, &cbIcon);
          if (rc != SCARD_S_SUCCESS) {
            std::cerr << "SCardGetReaderIconW failed with " << err2str(rc)
                      << std::endl;
            return false;
          }
        }
        return true;
}

static bool test_locate_cards_a(SCARDCONTEXT context)
{
	LPSTR name = "Gemalto PC Twin Reader 00 00\0\0";
	SCARD_READERSTATEA rgReaderStates[16] = {};

	auto rc = SCardLocateCardsA(context, name, rgReaderStates, ARRAYSIZE(rgReaderStates));
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardLocateCardsA failed with " << err2str(rc) << std::endl;
		return false;
	}

	return true;
}

static bool test_locate_cards_w(SCARDCONTEXT context)
{
	LPWSTR name = L"Gemalto PC Twin Reader 00 00\0\0";
	SCARD_READERSTATEW rgReaderStates[16] = {};

	auto rc = SCardLocateCardsW(context, name, rgReaderStates, ARRAYSIZE(rgReaderStates));
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardLocateCardsW failed with " << err2str(rc) << std::endl;
		return false;
	}

	return true;
}

static bool test_locate_cards_by_atr_a(SCARDCONTEXT context)
{
  SCARD_READERSTATEA rgReaderStates[6] = {};
  SCARD_ATRMASK rgAtrMasks[6] = {};

  rgAtrMasks[3].cbAtr = 11;
  rgReaderStates[1].szReader = "foobar";
  auto rc = SCardLocateCardsByATRA(context, rgAtrMasks, ARRAYSIZE(rgAtrMasks),
                                   rgReaderStates, ARRAYSIZE(rgReaderStates));
  if (rc != SCARD_S_SUCCESS) {
    std::cerr << "SCardLocateCardsByATRA failed with " << err2str(rc)
              << std::endl;
    return false;
  }

  return true;
}

static bool test_locate_cards_by_atr_w(SCARDCONTEXT context)
{
  SCARD_READERSTATEW rgReaderStates[6] = {};
  SCARD_ATRMASK rgAtrMasks[6] = {};

  rgAtrMasks[3].cbAtr = 11;
  rgReaderStates[1].szReader = L"foobar";
  auto rc = SCardLocateCardsByATRW(context, rgAtrMasks, ARRAYSIZE(rgAtrMasks),
                                   rgReaderStates, ARRAYSIZE(rgReaderStates));
  if (rc != SCARD_S_SUCCESS) {
    std::cerr << "SCardLocateCardsByATRW failed with " << err2str(rc)
              << std::endl;
  }

  return true;
}

static bool test_devicetype_id_a(SCARDCONTEXT context)
{
	LPSTR name = "testdata";
	DWORD type;

	auto rc = SCardGetDeviceTypeIdA(context, name, &type);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardGetDeviceTypeIdA failed with " << err2str(rc) << std::endl;
		return false;
	}

	return true;
}

static bool test_devicetype_id_w(SCARDCONTEXT context)
{
	LPWSTR name = L"testdata";
	DWORD type;

	auto rc = SCardGetDeviceTypeIdW(context, name, &type);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardGetDeviceTypeIdW failed with " << err2str(rc) << std::endl;
		return false;
	}

	return true;
}

static bool test_transaction(SCARDHANDLE card)
{
    auto rc = SCardBeginTransaction(card);
    if (rc != SCARD_S_SUCCESS)
    {
        std::cerr << "SCardBeginTransaction failed with " << err2str(rc) << std::endl;
        return false;
    }

    BYTE buffer[1024] = {};
    DWORD bufferSize = sizeof(buffer);
    for (auto id : {SCARD_ATTR_ATR_STRING, SCARD_ATTR_VENDOR_NAME, SCARD_ATTR_DEVICE_FRIENDLY_NAME_A, SCARD_ATTR_DEVICE_FRIENDLY_NAME_W}) {
        rc = SCardGetAttrib(card, id, buffer, &bufferSize);
        if (rc != SCARD_S_SUCCESS)
        {
            std::cerr << "SCardGetAttrib " << id << "  failed with " << err2str(rc) << std::endl;
        }
        DWORD count = 0;
        rc = SCardGetTransmitCount(card, &count);
        if (rc != SCARD_S_SUCCESS)
            std::cerr << "SCardGetTransmitCount failed with " << err2str(rc) << std::endl;
        else
            std::cout << " SCardGetTransmitCount " << count << std::endl;
    }
    rc = SCardEndTransaction(card, SCARD_LEAVE_CARD);
    if (rc != SCARD_S_SUCCESS)
    {
        std::cerr << "SCardEndTransaction failed with " << err2str(rc) << std::endl;
        return false;
    }
    return true;
}

static bool test_control(SCARDCONTEXT context, SCARDHANDLE card) {
  CHAR input[128] = {};
  CHAR output[128] = {};
  DWORD out;

  auto rc =
      SCardControl(card, 0, input, sizeof(input), output, sizeof(output), &out);
  if (rc != SCARD_S_SUCCESS) {
    std::cerr << "SCardControl failed with " << err2str(rc) << std::endl;
    return false;
  }
  return true;
}

static bool test_transmit(SCARDCONTEXT context, SCARDHANDLE card) {
  BYTE pbSendBuffer[128] = {};
  BYTE pbRecvBuffer[128] = {};
  DWORD recvLen = sizeof(pbRecvBuffer);
  auto rc =
      SCardTransmit(card, SCARD_PCI_T0, pbSendBuffer, sizeof(pbSendBuffer),
                    nullptr, pbRecvBuffer, &recvLen);
  if (rc != SCARD_S_SUCCESS) {
    std::cerr << "SCardTransmit failed with " << err2str(rc) << std::endl;
    return false;
  }
  return true;
}

static bool test_transmitcount(SCARDHANDLE handle)
{
	DWORD count;

	auto rc = SCardGetTransmitCount(handle, &count);
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardGetTransmitCount failed with " << err2str(rc) << std::endl;
		return false;
	}
	std::cout << "SCardGetTransmitCount() " << count << std::endl;
	return true;
}

static bool test_state(SCARDCONTEXT context, SCARDHANDLE handle) {
  DWORD state, protocol;
  DWORD attrLen = SCARD_AUTOALLOCATE;
  LPBYTE attrs = nullptr;

  auto rc = SCardState(handle, &state, &protocol, (LPBYTE)&attrs, &attrLen);
  SCardFreeMemory(context, attrs);
  if (rc != SCARD_S_SUCCESS) {
    std::cerr << "SCardState failed with " << err2str(rc) << std::endl;
    return false;
  }
  BYTE sattrs[1024] = {};
  attrLen = sizeof(sattrs);
  rc = SCardState(handle, &state, &protocol, sattrs, &attrLen);
  if (rc != SCARD_S_SUCCESS) {
    std::cerr << "SCardState failed with " << err2str(rc) << std::endl;
    return false;
  }
  return true;
}

static bool test_status_a(SCARDCONTEXT context, SCARDHANDLE handle)
{
    LPSTR names = NULL;
    LPBYTE attrs = NULL;
    DWORD len = SCARD_AUTOALLOCATE;
    DWORD attrLen = SCARD_AUTOALLOCATE;
    DWORD state, protocol;

    auto rc = SCardStatusA(handle, (LPSTR)&names, &len, &state, &protocol, (LPBYTE)&attrs, &attrLen);
        SCardFreeMemory(context, names);
        SCardFreeMemory(context, attrs);
	    if (rc != SCARD_S_SUCCESS) {
            std::cerr << "SCardStatusA failed with " << err2str(rc) << std::endl;
	        return false;
        }
        names = nullptr; attrs = nullptr;
        len = attrLen = SCARD_AUTOALLOCATE;
        rc = SCardStatusA(handle, (LPSTR)&names, &len, nullptr, &protocol, (LPBYTE)&attrs, &attrLen);
        SCardFreeMemory(context, names);
        SCardFreeMemory(context, attrs);
        if (rc != SCARD_S_SUCCESS) {
            std::cerr << "SCardStatusA failed with " << err2str(rc) << std::endl;
            return false;
        }
        names = nullptr; attrs = nullptr;
        len = attrLen = SCARD_AUTOALLOCATE;
        rc = SCardStatusA(handle, (LPSTR)&names, &len, &state, nullptr, (LPBYTE)&attrs, &attrLen);
        SCardFreeMemory(context, names);
        SCardFreeMemory(context, attrs);
        if (rc != SCARD_S_SUCCESS) {
            std::cerr << "SCardStatusA failed with " << err2str(rc) << std::endl;
            return false;
        }
        names = nullptr; attrs = nullptr;
        len = attrLen = SCARD_AUTOALLOCATE;
        rc = SCardStatusA(handle, (LPSTR)&names, &len,nullptr, nullptr, (LPBYTE)&attrs, &attrLen);
        SCardFreeMemory(context, names);
        SCardFreeMemory(context, attrs);
        if (rc != SCARD_S_SUCCESS) {
            std::cerr << "SCardStatusA failed with " << err2str(rc) << std::endl;
            return false;
        }
        CHAR snames[1024] ={};
        BYTE sattrs[1024] ={};
        len = attrLen = 1024;
        rc = SCardStatusA(handle, snames, &len,nullptr, nullptr, sattrs, &attrLen);
        if (rc != SCARD_S_SUCCESS) {
            std::cerr << "SCardStatusA failed with " << err2str(rc) << std::endl;
            return false;
        }
	return true;
}


static bool test_status_w(SCARDCONTEXT context, SCARDHANDLE handle)
{
    LPWSTR names = NULL;
    LPBYTE attrs = NULL;
    DWORD len = SCARD_AUTOALLOCATE;
    DWORD attrLen = SCARD_AUTOALLOCATE;
    DWORD state, protocol;

    auto rc = SCardStatusW(handle, (LPWSTR)&names, &len, &state, &protocol, (LPBYTE)&attrs, &attrLen);
    SCardFreeMemory(context, names);
    SCardFreeMemory(context, attrs);
    if (rc != SCARD_S_SUCCESS) {
        std::cerr << "SCardStatusW failed with " << err2str(rc) << std::endl;
        return false;
    }
    names = nullptr; attrs = nullptr;
    len = attrLen = SCARD_AUTOALLOCATE;
    rc = SCardStatusW(handle, (LPWSTR)&names, &len, nullptr, &protocol, (LPBYTE)&attrs, &attrLen);
    SCardFreeMemory(context, names);
    SCardFreeMemory(context, attrs);
    if (rc != SCARD_S_SUCCESS) {
        std::cerr << "SCardStatusW failed with " << err2str(rc) << std::endl;
        return false;
    }
    names = nullptr; attrs = nullptr;
    len = attrLen = SCARD_AUTOALLOCATE;
    rc = SCardStatusW(handle, (LPWSTR)&names, &len, &state, nullptr, (LPBYTE)&attrs, &attrLen);
    SCardFreeMemory(context, names);
    SCardFreeMemory(context, attrs);
    if (rc != SCARD_S_SUCCESS) {
        std::cerr << "SCardStatusW failed with " << err2str(rc) << std::endl;
        return false;
    }
    names = nullptr; attrs = nullptr;
    len = attrLen = SCARD_AUTOALLOCATE;
    rc = SCardStatusW(handle, (LPWSTR)&names, &len,nullptr, nullptr, (LPBYTE)&attrs, &attrLen);
    SCardFreeMemory(context, names);
    SCardFreeMemory(context, attrs);
    if (rc != SCARD_S_SUCCESS) {
        std::cerr << "SCardStatusW failed with " << err2str(rc) << std::endl;
        return false;
    }
    WCHAR snames[1024] ={};
    BYTE sattrs[1024] ={};
    len = attrLen = 1024;
    rc = SCardStatusW(handle, snames, &len,nullptr, nullptr, sattrs, &attrLen);
    if (rc != SCARD_S_SUCCESS) {
        std::cerr << "SCardStatusW failed with " << err2str(rc) << std::endl;
        return false;
    }
    return true;
}

static bool test_get_attrib(SCARDCONTEXT context, SCARDHANDLE handle)
{
    for (auto id : {SCARD_ATTR_ATR_STRING, SCARD_ATTR_VENDOR_NAME, SCARD_ATTR_DEVICE_FRIENDLY_NAME_A, SCARD_ATTR_DEVICE_FRIENDLY_NAME_W}) {
        DWORD attrlen = SCARD_AUTOALLOCATE;
        LPBYTE attr = nullptr;

        auto rc =
            SCardGetAttrib(handle, id, reinterpret_cast<LPBYTE>(&attr), &attrlen);
        if (rc != SCARD_S_SUCCESS)
            std::cerr << "SCardGetAttrib failed with " << err2str(rc) << std::endl;

        std::cout << "SCardGetAttrib [" << attrlen << "]: " << (char*)attr << std::endl;
        SCardFreeMemory(context, attr);

        for (DWORD x = 0; x < 256; x++) {
          BYTE attr[1024] = {};
          DWORD attrlen = x;
          auto rc = SCardGetAttrib(handle, id, attr, &attrlen);
          if (rc != SCARD_S_SUCCESS)
            std::cerr << "SCardGetAttrib failed with " << err2str(rc)
                      << std::endl;

          std::cout << "SCardGetAttrib [" << attrlen << "]: " << (char *)attr
                    << std::endl;
        }
    }
    return true;
}

static bool test_set_attrib(SCARDCONTEXT context, SCARDHANDLE handle)
{
	BYTE attr[] = "0123456789";

	auto rc = SCardSetAttrib(handle, SCARD_ATTR_SUPRESS_T1_IFS_REQUEST, attr, ARRAYSIZE(attr));
	if (rc != SCARD_S_SUCCESS)
	{
		std::cerr << "SCardSetAttrib failed with " << err2str(rc) << std::endl;
		return false;
	}
        std::cout << "SCardSetAttrib: " << (char *)attr << std::endl;

        return true;
}

static bool test_reconnect(SCARDHANDLE handle) {
  for (auto sharemode :
       {SCARD_SHARE_EXCLUSIVE, SCARD_SHARE_DIRECT, SCARD_SHARE_SHARED}) {
    for (auto protocol :
         {SCARD_PROTOCOL_UNDEFINED, SCARD_PROTOCOL_T0, SCARD_PROTOCOL_T1,
          SCARD_PROTOCOL_RAW, SCARD_PROTOCOL_OPTIMAL, SCARD_PROTOCOL_Tx}) {
      for (auto init : {SCARD_LEAVE_CARD, SCARD_RESET_CARD, SCARD_UNPOWER_CARD,
                        SCARD_EJECT_CARD}) {
        auto rc = SCardReconnect(handle, sharemode, protocol, init, nullptr);
        if (rc != SCARD_S_SUCCESS) {
          std::cerr << "SCardReconnect failed with " << err2str(rc)
                    << std::endl;
        }
        DWORD active = 0;
        rc = SCardReconnect(handle, sharemode, protocol, init, &active);
        if (rc != SCARD_S_SUCCESS) {
          std::cerr << "SCardReconnect failed with " << err2str(rc)
                    << std::endl;
        }
      }
    }
  }
  return true;
}

static bool test_statuschange(SCARDCONTEXT context) {
  SCARD_READERSTATEA rgReaderStates[1] = {};
  SCARD_READERSTATEW rgWReaderStates[1] = {};
  rgReaderStates[0].szReader = "\\\\?PnP?\\Notification";
  rgWReaderStates[0].szReader = L"\\\\?PnP?\\Notification";
  auto rc = SCardGetStatusChangeA(context, 1, rgReaderStates,
                                  ARRAYSIZE(rgReaderStates));
  if (rc != SCARD_S_SUCCESS) {
    std::cerr << "SCardGetStatusChangeA failed with " << err2str(rc)
              << std::endl;
  }
  rc = SCardGetStatusChangeW(context, 1, rgWReaderStates,
                             ARRAYSIZE(rgWReaderStates));
  if (rc != SCARD_S_SUCCESS) {
    std::cerr << "SCardGetStatusChangeW failed with " << err2str(rc)
              << std::endl;
  }
  return true;
}

static bool test_handle_a(SCARDCONTEXT context, LPCSTR mszReader)
{
    SCARDHANDLE handle;
    DWORD protocol;
    auto status = SCardConnectA(context, mszReader, SCARD_SHARE_SHARED,
                           SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1 |
                               SCARD_PROTOCOL_Tx | SCARD_PROTOCOL_RAW,
                           &handle, &protocol);
    if (status != SCARD_S_SUCCESS)
    {
        std::cerr << "SCardConnectA ["
                  << "] failed with " << err2str(status) << std::endl;
        return false;
    }
    else
    {
      test_control(context, handle);
      test_transmit(context, handle);
      test_state(context, handle);
      test_status_a(context, handle);
      test_status_w(context, handle);
      test_get_attrib(context, handle);
      test_set_attrib(context, handle);
      test_transmitcount(handle);
      test_transaction(handle);
      test_reconnect(handle);
      status = SCardDisconnect(handle, 0);
      if (status) {
        std::cerr << "SCardDisconnect ["
                  << "] failed with " << err2str(status) << std::endl;
        return false;
      }
    }
    return true;
}

static bool test_handle_w(SCARDCONTEXT context, LPCWSTR mszReader)
{
    SCARDHANDLE handle;
    DWORD protocol;
    auto status = SCardConnectW(context, mszReader, SCARD_SHARE_SHARED,
                                SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1 |
                                    SCARD_PROTOCOL_Tx | SCARD_PROTOCOL_RAW,
                                &handle, &protocol);
    if (status != SCARD_S_SUCCESS)
    {
        std::cerr << "SCardConnectW ["
                  << "] failed with " << err2str(status) << std::endl;
        return false;
    } else {
      test_state(context, handle);
      test_control(context, handle);
      test_transmit(context, handle);
      test_status_a(context, handle);
      test_status_w(context, handle);
      test_get_attrib(context, handle);
      test_set_attrib(context, handle);
      test_transmitcount(handle);
      test_transaction(handle);
      test_reconnect(handle);
      status = SCardDisconnect(handle, 0);
      if (status) {
        std::cerr << "SCardDisconnect ["
                  << "] failed with " << err2str(status) << std::endl;
        return false;
      }
    }
    return true;
}

static bool test_cancel(SCARDCONTEXT context) {
  auto status = SCardCancel(context);
  if (status != SCARD_S_SUCCESS) {
    std::cerr << "SCardCancel ["
              << "] failed with " << err2str(status) << std::endl;
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (_strcmpi(argv[1], "-h") == 0) {
      std::cout << "Run " << argv[0]
                << " without arguments to run a series of SCard API calls "
                << std::endl;
      std::cout << "\tThis will test all function calls redirected by RDP "
                   "smartcard redirection"
                << std::endl;
      std::cout << "\tSubmit improvements/bugfixes/... at "
                   "https://github.com/akallabeth/scard-tester"
                << std::endl;
    } else if (_strcmpi(argv[1], "-v") == 0) {
      std::cout << argv[0] << " version: " PROJECT_VERSION << std::endl;
      std::cout << argv[0] << " git:     " PROJECT_GIT << std::endl;
    } else {
      std::cerr << " Invalid command line arguments: " << argv[1] << std::endl;
      return -1;
    }
    return 0;
  }
  std::cout << "SCard API test started" << std::endl;
  try {
    auto scopes = {SCARD_SCOPE_USER, SCARD_SCOPE_SYSTEM};
    for (auto scope : scopes) {
      SCARDCONTEXT context;
      auto rc = SCardEstablishContext(scope, nullptr, nullptr, &context);
      if (rc != SCARD_S_SUCCESS) {
        std::cerr << "SCardEstablishContext [" << scope2str(scope)
                  << "] failed with " << err2str(rc) << std::endl;
      } else {
        std::cerr << "SCardEstablishContext [" << scope2str(scope)
                  << "] success" << std::endl;

        test_valid(context);

        test_cancel(context);
        test_statuschange(context);

        test_list_reader_groups_a(context);
        test_list_reader_groups_w(context);

        test_list_readers_a(context);
        test_list_readers_w(context);

        test_list_cards_a(context);
        test_list_cards_w(context);

        test_introduce_forget_reader_groups_a(context);
        test_introduce_forget_reader_groups_w(context);

        test_introduce_forget_reader_a(context);
        test_introduce_forget_reader_w(context);

        // TODO: Introduce/Remove reader to group
        test_locate_cards_a(context);
        test_locate_cards_w(context);

        test_locate_cards_by_atr_a(context);
        test_locate_cards_by_atr_w(context);

        test_cache_a(context);
        test_cache_w(context);

        test_reader_icon_a(context);
        test_reader_icon_w(context);

        test_devicetype_id_a(context);
        test_devicetype_id_w(context);

        {
          size_t offset = 0;
          LPSTR mszReaders;
          DWORD chReaders = SCARD_AUTOALLOCATE;

          LONG status = SCardListReadersA(context, nullptr,
                                          reinterpret_cast<LPSTR>(&mszReaders),
                                          &chReaders);
          if (status == SCARD_S_SUCCESS) {
            for (offset = 0; offset < chReaders;
                 offset +=
                 strnlen(&mszReaders[offset], chReaders - offset) + 1) {
              test_handle_a(context, &mszReaders[offset]);
            }
          }
          SCardFreeMemory(context, mszReaders);
        }
        {
          size_t offset;
          LPWSTR mszReaders;
          DWORD chReaders = SCARD_AUTOALLOCATE;

          LONG status = SCardListReadersW(context, nullptr,
                                          reinterpret_cast<LPWSTR>(&mszReaders),
                                          &chReaders);
          if (status == SCARD_S_SUCCESS) {
            for (offset = 0; offset < chReaders;
                 offset +=
                 wcsnlen(&mszReaders[offset], chReaders - offset) + 1) {
              test_handle_w(context, &mszReaders[offset]);
            }
          }

          SCardFreeMemory(context, mszReaders);
        }

        rc = SCardReleaseContext(context);
        if (rc != SCARD_S_SUCCESS) {
          std::cerr << "SCardReleaseContext [" << scope2str(scope)
                    << "] failed with " << err2str(rc) << std::endl;
        }
      }
    }

    test_started_event();
  } catch (...) {
    std::cerr << "exception!!!!" << std::endl;
  }

  return 0;
}
