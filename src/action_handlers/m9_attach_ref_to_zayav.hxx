#ifndef M9_ATTACH_REF_TO_ZAYAV_HXX_
#define M9_ATTACH_REF_TO_ZAYAV_HXX_

#include <tc/tc.h>
#include <epm.h>

/**
 * Handler связки любого объекта из reference с заявкой из target при помощи отношения M9_ZayavRel
 */

int m9_attach_ref_to_zayav(EPM_action_message_t);

#endif
