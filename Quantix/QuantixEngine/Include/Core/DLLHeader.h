#ifndef __DLLHEADER_H__
#define __DLLHEADER_H__

#ifdef QUANTIX_EXPORTS
#define QUANTIX_API __declspec(dllexport)
#else
#define QUANTIX_API __declspec(dllimport)
#endif

#endif // !__DLLHEADER_H__
