#include <tccore/aom_prop.h>

#include <base_utils/ResultCheck.hxx>
#include "../misc.hxx"
#include "../process_error.hxx"
#include "m9_get_FullNameTC.hxx"

#include <ug_va_copy.h>

#ifndef MAX_RESULT_LENGTH
#define MAX_RESULT_LENGTH 256
#endif

int m9_get_FullNameTC(METHOD_message_t* message, va_list args){
	try{
		va_list vargs;
		va_copy(vargs, args);
		tag_t prop_tag = va_arg(vargs, tag_t);
		char **rvalue = va_arg(vargs, char**);
		va_end(vargs);

		ResultCheck erc;
		char* result = (char*) MEM_alloc(MAX_RESULT_LENGTH+1); //Don't forget to free it!
		*result = '\0';

		char* m9_ShortName = NULL;
		char* m9_Manufacturer = NULL;
		char* m9_MarkSymbol = NULL;
		char* m9_NormDoc = NULL;
		char* m9_TechCharacter = NULL;
		char* m9_Drawing = NULL;
		char* m9_MarkMaterial = NULL;
		char* m9_NormDocMaterial = NULL;
		char* m9_CatalogNO = NULL;

		erc = AOM_ask_value_string(message->object_tag, "m9_ShortName", &m9_ShortName);
		erc = AOM_ask_value_string(message->object_tag, "m9_Manufacturer", &m9_Manufacturer);
		erc = AOM_ask_value_string(message->object_tag, "m9_MarkSymbol", &m9_MarkSymbol);
		erc = AOM_ask_value_string(message->object_tag, "m9_NormDoc", &m9_NormDoc);
		erc = AOM_ask_value_string(message->object_tag, "m9_TechCharacter", &m9_TechCharacter);
		erc = AOM_ask_value_string(message->object_tag, "m9_Drawing", &m9_Drawing);
		erc = AOM_ask_value_string(message->object_tag, "m9_MarkMaterial", &m9_MarkMaterial);
		erc = AOM_ask_value_string(message->object_tag, "m9_NormDocMaterial", &m9_NormDocMaterial);
		erc = AOM_ask_value_string(message->object_tag, "m9_CatalogNO", &m9_CatalogNO);

		appendToResult(result, "", m9_ShortName, MAX_RESULT_LENGTH);
		appendToResult(result, " ", m9_MarkSymbol, MAX_RESULT_LENGTH);
		appendToResult(result, " ", m9_TechCharacter, MAX_RESULT_LENGTH);
		appendToResult(result, " ", m9_NormDoc, MAX_RESULT_LENGTH);
		appendToResult(result, " /", m9_MarkMaterial, MAX_RESULT_LENGTH);
		appendToResult(result, " ", m9_NormDocMaterial, MAX_RESULT_LENGTH);
		appendToResult(result, " черт.", m9_Drawing, MAX_RESULT_LENGTH);
		appendToResult(result, " ", m9_CatalogNO, MAX_RESULT_LENGTH);
		appendToResult(result, " ", m9_Manufacturer, MAX_RESULT_LENGTH);

		*rvalue = (char*) MEM_alloc(strlen(result) + 1);
		strcpy(*rvalue, result);
		MEM_free(result);
		if(m9_ShortName) MEM_free(m9_ShortName);
		if(m9_Manufacturer) MEM_free(m9_Manufacturer);
		if(m9_MarkSymbol) MEM_free(m9_MarkSymbol);
		if(m9_NormDoc) MEM_free(m9_NormDoc);
		if(m9_TechCharacter) MEM_free(m9_TechCharacter);
		if(m9_Drawing) MEM_free(m9_Drawing);
		if(m9_MarkMaterial) MEM_free(m9_MarkMaterial);
		if(m9_NormDocMaterial) MEM_free(m9_NormDocMaterial);
		if(m9_CatalogNO) MEM_free(m9_CatalogNO);

	} catch (...) {
		return sisw::process_error(true, true, false);
	}
	return ITK_ok;
}
