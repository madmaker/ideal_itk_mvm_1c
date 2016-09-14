#include <iostream>
#include <string>
#include <base_utils/ResultCheck.hxx>
#include <tc/tc.h>
#include <property/prop_msg.h>
#include <tccore/custom.h>
#include <tccore/method.h>
#include "../process_error.hxx"
#include "m9_action_handlers.hxx"
#include "m9_export_plmxml.hxx"
#include "m9_attach_ref_to_zayav.hxx"
#include "m9_detach_all_from_zayav.hxx"
#include "m9_add_to_refs_related_to_zayav.hxx"
#include "m9_add_to_targets_rev.hxx"

/**
 *
 */
int m9_1c_lib_register_action_handlers(int * decision, va_list args) {
	try {
		printf("\n");
		printf("REGISTRERING ACTION HANDLERS...");
		printf("\n");

		int ifail= ITK_ok;
		ResultCheck erc;
		*decision = ALL_CUSTOMIZATIONS;

		ifail = EPM_register_action_handler("M9_export_plmxml", "", m9_export_plmxml);
		ifail = EPM_register_action_handler("M9_attach_ref_to_zayav", "", m9_attach_ref_to_zayav);
		ifail = EPM_register_action_handler("M9_detach_all_from_zayav", "", m9_detach_all_from_zayav);
		ifail = EPM_register_action_handler("M9_add_to_refs_related_to_zayav", "", m9_add_to_refs_related_to_zayav);
		ifail = EPM_register_action_handler("M9_add_to_targets_rev", "", m9_add_to_targets_rev);

	} catch (...) {
		return sisw::process_error(true, true, false);
	}
	return ITK_ok;
}
