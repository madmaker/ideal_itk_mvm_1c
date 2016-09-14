#include <iostream>
#include <string>
#include <base_utils/ResultCheck.hxx>
#include <tc/tc.h>
#include <property/prop_msg.h>
#include <tccore/custom.h>
#include <tccore/method.h>
#include "../process_error.hxx"
#include "m9_properties.hxx"
#include "m9_get_FullName1C.hxx"
#include "m9_get_FullNameTC.hxx"

/**
 *
 */
int m9_1c_lib_register_properties(int * decision, va_list args) {
	try {
		printf("\n");
		printf("REGISTRERING PROPERTIES...");
		printf("\n");

		ResultCheck erc;

		*decision = ALL_CUSTOMIZATIONS;
		METHOD_id_t meth = { 0 };

		erc = METHOD_register_prop_method("M9_ZayavForm", "m9_FullName1C",
				PROP_ask_value_string_msg, m9_get_FullName1C, NULL, &meth);

		erc = METHOD_register_prop_method("M9_ZayavForm", "m9_FullNameTC",
				PROP_ask_value_string_msg, m9_get_FullNameTC, NULL, &meth);


	} catch (...) {
		return sisw::process_error(true, true, false);
	}
	return ITK_ok;
}
