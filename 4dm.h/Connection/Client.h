#pragma once

#include "steam/steamnetworkingtypes.h"
#include "steam/isteamnetworkingsockets.h"
#include <type_traits>
#include <set>
#include "../4dm.h"

namespace fdm::Connection
{
	class Client
	{
	public:
		enum Status
		{
			OFFLINE = 0x0,
			STARTING = 0x1,
			FAILED_TO_START = 0x2,
			ONLINE = 0x3,
			CLOSED = 0x4,
			CLOSED_ERROR = 0x5
		};
		Status status;
		std::atomic<bool> resolvingHost;
		PAD(3);
		msvc_string address;
		std::thread resolveHostThread;
		unsigned int connectionHandle;
		PAD(4);
		ISteamNetworkingSockets* Interface;

		void update()
		{
			return reinterpret_cast<void(__thiscall*)(Client * self)>(getFuncAddr((int)Func::Connection_Nested::Client::update))(this);
		}
		void resolveHost(msvc_string& host)
		{
			return reinterpret_cast<void(__thiscall*)(Client * self, msvc_string& host)>(getFuncAddr((int)Func::Connection_Nested::Client::resolveHost))(this, host);
		}
		void cleanup()
		{
			return reinterpret_cast<void(__thiscall*)(Client * self)>(getFuncAddr((int)Func::Connection_Nested::Client::cleanup))(this);
		}
		inline static void connectionStatusChangedCallback(SteamNetConnectionStatusChangedCallback_t* info)
		{
			return reinterpret_cast<void(__fastcall*)(SteamNetConnectionStatusChangedCallback_t * info)>(getFuncAddr((int)Func::Connection_Nested::Client::connectionStatusChangedCallback))(info);
		}
	};
}
