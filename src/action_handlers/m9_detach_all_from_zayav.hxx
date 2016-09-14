#ifndef M9_DETACH_ALL_FROM_ZAYAV_HXX_
#define M9_DETACH_ALL_FROM_ZAYAV_HXX_

#include <tc/tc.h>
#include <epm.h>

/**
 * Handler отвязки от заявки из target от любых объектов, с которыми есть отношение M9_ZayavRel
 */

int m9_detach_all_from_zayav(EPM_action_message_t);

#endif
