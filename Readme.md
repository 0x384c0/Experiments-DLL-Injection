## x64dbg hotkeys
* alt+a attach
* alt+f9  run until return
* f8 step over
* shift+f5 dassasm selected

## DLL Injection steps
* find entry point to func
* set breakpoint
* when func called
* run until return
* step over to find place, where func was called
* [findout which calling convention function uses](https://docs.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=vs-2017)
* copy
    RVA to FUNC_NO_PARAMS_RELATIVE_ADDRESS or 
    absolute address to FUNC_NO_PARAMS_ABSOLUTE_ADDRESS
    and use it for defining function

