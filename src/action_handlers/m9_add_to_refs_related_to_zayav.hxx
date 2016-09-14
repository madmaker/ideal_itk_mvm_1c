#ifndef M9_ADD_TO_REFS_RELATED_TO_ZAYAV_HXX_
#define M9_ADD_TO_REFS_RELATED_TO_ZAYAV_HXX_

#include <tc/tc.h>
#include <epm.h>

/**
 * Handler добавления в reference объекта, связанного при помощи отношения M9_ZayavRel с заявкой из target
 */

int m9_add_to_refs_related_to_zayav(EPM_action_message_t);

#endif
