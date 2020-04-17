#ifndef _RTTRENABLED_H_
#define _RTTRENABLED_H_

#include <rttr/library.h>
#include <rttr/registration.h>
#include <rttr/registration_friend.h>

#define CLASS_REGISTRATION(...) \
RTTR_ENABLE(__VA_ARGS__)		\
RTTR_REGISTRATION_FRIEND

#endif // !_RTTRENABLED_H_
