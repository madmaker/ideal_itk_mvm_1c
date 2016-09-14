#include <grm.h>
#include <epm.h>
#include <epm_toolkit_tc_utils.h>
#include <base_utils/ResultCheck.hxx>
#include "../process_error.hxx"
#include "m9_attach_ref_to_zayav.hxx"

int m9_attach_ref_to_zayav(EPM_action_message_t msg) {
	try {
		tag_t
			*attachments,
			root_task,
			zayav_t,
			zayavRel_t,
			M9_ZayavForm_type_t,
			temp_type_t,
			user_data = NULL_TAG,
			rel_tag = NULL_TAG;
		int
			*attachments_types,
			attachments_count = 0;
		bool
			is_M9_ZayavForm_type = false;

		ResultCheck erc;

		erc = GRM_find_relation_type("M9_ZayavRel", &zayavRel_t);
		erc = TCTYPE_find_type("M9_ZayavForm", NULL, &M9_ZayavForm_type_t);

		erc = EPM_ask_root_task(msg.task, &root_task);
		erc = EPM_ask_all_attachments(root_task, &attachments_count, &attachments, &attachments_types);
		for(int i = 0; i < attachments_count; i++){
			if(attachments_types[i]==EPM_target_attachment){
				erc = TCTYPE_ask_object_type(attachments[i], &temp_type_t);
				erc = TCTYPE_is_type_of(temp_type_t, M9_ZayavForm_type_t, &is_M9_ZayavForm_type);
				if(is_M9_ZayavForm_type){
					zayav_t = attachments[i];
					break;
				}
			}
		}

		if(zayav_t==NULL) return ITK_ok;

		for(int i = 0; i < attachments_count; i++){
			if(attachments_types[i]==EPM_target_attachment){
				erc = TCTYPE_ask_object_type(attachments[i], &temp_type_t);
				erc = TCTYPE_is_type_of(temp_type_t, M9_ZayavForm_type_t, &is_M9_ZayavForm_type);
				if(!is_M9_ZayavForm_type){
					erc = GRM_create_relation(attachments[i], zayav_t, zayavRel_t, user_data, &rel_tag);
					erc = GRM_save_relation(rel_tag);
				}
			}
		}

		MEM_free(attachments);
		MEM_free(attachments_types);

	} catch (...){
		return sisw::process_error(true, true, false);
	}
	return ITK_ok;
}
