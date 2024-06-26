/* #############################

Example usage:

void init(){
	printf("This will get printed to the console before the shortcut list\n");
}
void info(){
	printf("This will get printed to the console after the shortcut list\n");
}


DWORD WINAPI Main_Thread(void* hModule) {
	
	registerConsoleCallback(init,ConsoleEvent::init);
	registerConsoleCallback(info,ConsoleEvent::info);
	
	registerConsoleKeyinfo({{"a","This shortcut will appear in the shortcuts list"}});
	
	ConsoleKeyinfo c = {"B",This shortcut will also appear in the shortcuts list"};
	ConsoleKeyinfos cs = {c};
	registerConsoleKeyinfo(cs);
	
}


##############################*/
#pragma once

// this is the name of the console mod's dll
#define CONSOLE_MOD_ID "redjard.console"

// These are the events you can subscribe to with registerConsoleCallback()
enum class ConsoleEvent {init,info};

// this is the type registerConsoleKeyinfo() eats
struct ConsoleKeyinfo {
	std::string key;
	std::string description;
};
typedef std::vector<ConsoleKeyinfo> ConsoleKeyinfos;



namespace console_mod_interface {

struct wrapper_console_keyinfo {
	const char* key;
	const char* description;
	
	operator ConsoleKeyinfo(){
		return ConsoleKeyinfo(this->key,this->description);
	}
};
typedef wrapper_console_keyinfo* wrapper_console_keyinfos;


inline bool registerConsoleKeyinfo( ConsoleKeyinfos keyinfo_vec ) {
	
	wrapper_console_keyinfos keyinfos = new wrapper_console_keyinfo[keyinfo_vec.size()+1];
	
	int i = 0;
	for ( auto keyinfo : keyinfo_vec )
		keyinfos[i++] = { strdup(keyinfo.key.c_str()), strdup(keyinfo.description.c_str()) };
	keyinfos[i] = {NULL};
	
	
	if (!fdm::isModLoaded(CONSOLE_MOD_ID));
		return false;
	
	return reinterpret_cast< bool (__stdcall*)( wrapper_console_keyinfos ) >(GetProcAddress(fdm::getModHandle(CONSOLE_MOD_ID),"registerKeyinfo"))(keyinfos);
}

typedef void (*consoleCallbackFunct)();
inline bool registerConsoleCallback( consoleCallbackFunct callback, ConsoleEvent event ) {
	
	if (!fdm::isModLoaded(CONSOLE_MOD_ID));
		return false;
	
	return reinterpret_cast< bool (__stdcall*)( consoleCallbackFunct, ConsoleEvent ) >(GetProcAddress(fdm::getModHandle(CONSOLE_MOD_ID),"registerCallback"))(callback,event);
}

}
using console_mod_interface::registerConsoleKeyinfo;
using console_mod_interface::registerConsoleCallback;