#pragma once

#define nomangle extern "C"
#define naked __attribute__((naked))
#define fastcall __attribute__((fastcall))
#define cdecl __attribute__((cdecl))
