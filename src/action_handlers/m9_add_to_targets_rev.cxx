#include <grm.h>
#include <epm.h>
#include <item.h>
#include <epm_toolkit_tc_utils.h>
#include <base_utils/ResultCheck.hxx>
#include "../process_error.hxx"
#include "../misc.hxx"
#include "m9_add_to_targets_rev.hxx"

int m9_add_to_targets_rev(EPM_action_message_t msg) {
	try {
		tag_t
			*attachments,
			root_task,
			M9_ZayavForm_type_t,
			temp_type_t,
			item_to_add = NULLTAG,
			item_rev_to_add = NULLTAG;
		int
			*attachments_types,
			attachments_count = 0;
		bool
			is_M9_ZayavForm_type = false;

		ResultCheck erc;

		erc = EPM_ask_root_task(msg.task, &root_task);
		erc = EPM_ask_all_attachments(root_task, &attachments_count, &attachments, &attachments_types);

		erc = TCTYPE_find_type("M9_ZayavForm", NULL, &M9_ZayavForm_type_t);

		for(int i = 0; i < attachments_count; i++){
			if(attachments_types[i]==EPM_target_attachment){
				erc = TCTYPE_ask_object_type(attachments[i], &temp_type_t);
				erc = TCTYPE_is_type_of(temp_type_t, M9_ZayavForm_type_t, &is_M9_ZayavForm_type);
				if(!is_M9_ZayavForm_type){
					item_to_add = attachments[i];
					break;
				}
			}
		}

		if(item_to_add==NULLTAG) return ITK_ok;

		erc = ITEM_ask_latest_rev (item_to_add, &item_rev_to_add);

		int* attachments_types_to_add = (int*) MEM_alloc(sizeof(int)*1);
		tag_t* attachments_to_add = (tag_t*) MEM_alloc(sizeof(tag_t)*1);
		attachments_to_add[0] = item_rev_to_add;
		attachments_types_to_add[0] = EPM_target_attachment;
		erc = EPM_add_attachments(root_task, 1, attachments_to_add, attachments_types_to_add);

		MEM_free(attachments);
		MEM_free(attachments_types);
		MEM_free(attachments_to_add);
		MEM_free(attachments_types_to_add);


	} catch (...){
			return sisw::process_error(true, true, false);
	}
	return ITK_ok;
}
