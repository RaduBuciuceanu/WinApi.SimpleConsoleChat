#pragma once

#ifdef _WIN32

#define IMPORT_SYMBOL __declspec(dllimport)
#define EXPORT_SYMBOL __declspec(dllexport)

#elif __GNUC__ >= 4

#define IMPORT_SYMBOL __attribute__((visibility("default")))
#define EXPORT_SYMBOL __attribute__((visibility("default")))

#else

#define IMPORT_SYMBOL
#define EXPORT_SYMBOL

#endif

#ifdef WASCC_NETWORKING_IO
#pragma comment(lib, "Ws2_32.lib")
#define WASCC_NETWORKING_IO EXPORT_SYMBOL
#else
#define WASCC_NETWORKING_IO IMPORT_SYMBOL
#endif
