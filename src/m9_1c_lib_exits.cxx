#include <iostream>
#include <string>
#include <base_utils/ResultCheck.hxx>
#include <tc/tc.h>
#include <tccore/custom.h>
#include "process_error.hxx"
#include "m9_1c_lib_exits.hxx"
#include "action_handlers/m9_action_handlers.hxx"
#include "properties/m9_properties.hxx"

//cppcheck-suppress unusedFunction
extern "C" __declspec (dllexport) int m9_1c_lib_idealplm_register_callbacks() {
	try {
		printf("\n---=Loading custom library=---\n");
		ResultCheck erc;
		erc = CUSTOM_register_exit("m9_1c_lib_idealplm", "USER_gs_shell_init_module",
				m9_1c_lib_register_action_handlers);

		erc = CUSTOM_register_exit("m9_1c_lib_idealplm", "USER_register_properties",
				m9_1c_lib_register_properties);

	} catch (...) {
		return sisw::process_error(true, true, false);
	}
	return ITK_ok;
}
