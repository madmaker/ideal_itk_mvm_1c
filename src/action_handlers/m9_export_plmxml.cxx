#include <stdlib.h>
#include <tccore/aom_prop.h>
#include <tccore/aom.h>
#include <epm.h>
#include <tccore/tctype.h>
#include <epm_toolkit_tc_utils.h>
#include <base_utils/ResultCheck.hxx>
#include "../process_error.hxx"
#include "../misc.hxx"
#include "m9_export_plmxml.hxx"
#include "epm_task_template_itk.h"

int m9_export_plmxml(EPM_action_message_t msg) {
	try {
		ResultCheck erc;
		char
		 	*task_uid = NULL,
		 	*form_uid = NULL,
		 	util[] = "%TC_BIN%\\plmxml_export",
		    login[] = "-u=infodba -p=infodba -g=dba",
		    cmd[256] = " ",
		    *flag = NULL,
			*value= NULL,
			*normal_value= NULL,
			Flag[256],
			*transfermode = NULL,
			*export_dir = NULL,
			*rev_rule = NULL,
			*site_uid,
			*form_status;
		tag_t
			*attachments,
			root_task,
			M9_ZayavForm_type_t,
			temp_type_t;
		int
			*attachments_types,
			attachments_count = 0,
			num_of_args,
			rcode = ITK_ok;
		bool
			is_M9_ZayavForm_type;

		num_of_args = TC_number_of_arguments(msg.arguments);
		if (num_of_args==0) {
		    //ShowTCMessage(1,"No arguments!",0,NULL);
			return(ITK_ok);
		}

		erc = TCTYPE_find_type("M9_ZayavForm", NULL, &M9_ZayavForm_type_t);

		for (int numctr=0;numctr<num_of_args && rcode==ITK_ok;numctr++) {
			rcode= ITK_ask_argument_named_value(TC_next_argument(msg.arguments), &flag, &value);
			if (rcode== ITK_ok) {
			    rcode= EPM_substitute_keyword(value,&normal_value);
			    if (normal_value != NULL) {
		            StrCpy(Flag,256,flag);
		            StrUpr(Flag);
		            if (rcode == ITK_ok) {
		                if (strcmp("TRANSFERMODE", Flag)==0) {
		                    if (!STR_EMPTY(normal_value)) {
		                    	transfermode = (char *) MEM_alloc(sizeof(char)*(strlen(normal_value)+1));
		                        strcpy(transfermode,normal_value);
		                    }
		                } else if(strcmp("EXPORT_DIR", Flag)==0){
		                	if (!STR_EMPTY(normal_value)) {
		                		export_dir = (char *) MEM_alloc(sizeof(char)*(strlen(normal_value)+1));
		                		strcpy(export_dir,normal_value);
		                	}
		                } else if(strcmp("REV_RULE", Flag)==0){
		                	if (!STR_EMPTY(normal_value)) {
		                		rev_rule = (char *) MEM_alloc(sizeof(char)*(strlen(normal_value)+1));
		                		strcpy(rev_rule,normal_value);
		                	}
		                }
		            }
		            if (normal_value != NULL) {
		            	MEM_free(normal_value);
		                normal_value = NULL;
		            }
			    }
			    if (flag != NULL) {
			    	MEM_free(flag);
			        flag = NULL;
			    }
			    if (value != NULL) {
			    	MEM_free(value);
			        value = NULL;
			    }
			} else {
				printf("Error: rcode1=%i", rcode);
			}
		}

		if(transfermode==NULL){
			transfermode = (char *) MEM_alloc(sizeof(char)*(strlen("ConfiguredDataExportDefault")+1));
			strcpy(transfermode, "ConfiguredDataExportDefault");
		}
		if(export_dir==NULL){
			export_dir = (char *) MEM_alloc(sizeof(char)*(strlen("C:/Temp")+1));
			strcpy(export_dir, "C:/Temp");
		}
		if(rev_rule==NULL){
			rev_rule = (char *) MEM_alloc(sizeof(char)*(strlen("Latest Working")+1));
			strcpy(rev_rule, "Latest Working");
		}

		ITK__convert_tag_to_uid(msg.task, &task_uid);

		erc = EPM_ask_root_task(msg.task, &root_task);
		erc = EPM_ask_all_attachments(root_task, &attachments_count, &attachments, &attachments_types);
		if (attachments_count > 0) {
			for(int i = 0; i < attachments_count; i++){
				if(attachments_types[i] == EPM_target_attachment){
					erc = TCTYPE_ask_object_type(attachments[i], &temp_type_t);
					erc = TCTYPE_is_type_of(temp_type_t, M9_ZayavForm_type_t, &is_M9_ZayavForm_type);
					if(is_M9_ZayavForm_type){
						ITK__convert_tag_to_uid(attachments[i], &form_uid);
						erc = AOM_ask_value_string(attachments[i], "m9_ReleaseStatus", &form_status);
						tag_t owning_site = NULL;
						erc = AOM_ask_value_tag(attachments[i], "owning_site", &owning_site);
						if(owning_site!=NULL){
							ITK__convert_tag_to_uid(owning_site, &site_uid);
						} else {
							site_uid = (char *) MEM_alloc(sizeof(char)*(strlen("AAAAAAAAAAAAAA")+1));
							strcpy(site_uid, "AAAAAAAAAAAAAA");
						}
						//sprintf(cmd, "%s %s -xml_file=C:/Temp/%s-%s.xml -uid=", util, login, form_uid, task_uid);
						sprintf(cmd, "%s %s -xml_file=\"%s/%s-%s%s-%s.xml\" -transfermode=\"%s\" -rev_rule=\"%s\" -uid=", util, login, export_dir, form_uid, task_uid, site_uid, form_status, transfermode, rev_rule);
						strcat(cmd, form_uid);
						//printf("Result command: \n%s", cmd);
						system(cmd);
						break;
					}
				}
			}
		} else {
			ShowTCMessage(1,"No targets!",0,NULL);
		}

		if (transfermode) MEM_free(transfermode);
		if (export_dir) MEM_free(export_dir);
		if (rev_rule) MEM_free(rev_rule);
		if (form_uid) MEM_free(form_uid);
		if (form_status) MEM_free(form_status);
		if (task_uid) MEM_free(task_uid);
		if (site_uid) MEM_free(site_uid);
		MEM_free(attachments);
		MEM_free(attachments_types);
	} catch (...) {
		return sisw::process_error(true, true, false);
	}
	return ITK_ok;
}
