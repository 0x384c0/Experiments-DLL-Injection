#include "Memory.h"
#include <stdio.h>


constexpr uintptr_t
FUNC_NO_PARAMS_RELATIVE_ADDRESS = 0x1140,
//FUNC_NO_PARAMS_ABSOLUTE_ADDRESS = 0x00007FF73CA81140;
FUNC_STR_PARAM_RELATIVE_ADDRESS = 0x1160,
TEST_CLASS_INSTANCE_RELATIVE_ADDRESS = 0x4620,
FUNC_CLASS_PARAM_RELATIVE_ADDRESS = 0x1180,
FUNC_THIS_CLASS_PRINT_RELATIVE_ADDRESS = 0x1110;

typedef void(__cdecl * TestFunctionNoParams)();
typedef void(__cdecl * TestFunctionParamString)(char * string);
typedef void(__cdecl * TestFunctionParamClass)(uintptr_t pointer);
typedef void(__cdecl * TestClass_printSelf)(uintptr_t pointer);


DWORD WINAPI MainThread(LPVOID param){
	printf("DLL loaded\n");
	uintptr_t modBase = (uintptr_t)GetModuleHandle(NULL);
	
	auto testFunctionNoParams = (TestFunctionNoParams)(modBase + FUNC_NO_PARAMS_RELATIVE_ADDRESS);
	//auto testFunctionNoParams = (TestFunctionNoParams)(FUNC_NO_PARAMS_ABSOLUTE_ADDRESS);
	auto testFunctionParamString = (TestFunctionParamString)(modBase + FUNC_STR_PARAM_RELATIVE_ADDRESS);
	auto testFunctionParamClass = (TestFunctionParamClass)(modBase + FUNC_CLASS_PARAM_RELATIVE_ADDRESS);
	auto testClass_printSelf = (TestClass_printSelf)(modBase + FUNC_THIS_CLASS_PRINT_RELATIVE_ADDRESS);

	while (!GetAsyncKeyState(VK_END)) {
	    if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			printf("\nVK_NUMPAD1 pressed\n");
			testFunctionNoParams();
		}
		if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
			printf("\nVK_NUMPAD2 pressed\n");
			testFunctionParamString("HELLUUURRR");
		}
		if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
			printf("\nVK_NUMPAD3 pressed\n");
			testFunctionParamClass(modBase + TEST_CLASS_INSTANCE_RELATIVE_ADDRESS);
		}
		if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
			printf("\nVK_NUMPAD4 pressed\n");
			testClass_printSelf(modBase + TEST_CLASS_INSTANCE_RELATIVE_ADDRESS);
		}
	}
	FreeLibraryAndExitThread((HMODULE)param, 0);
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved){
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MainThread, hModule, 0, 0);
		break;
	default:
		break;
	}
	return TRUE;
}