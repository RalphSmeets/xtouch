#ifndef _UI_COMP_FILAMENTCOMPONENT_H
#define _UI_COMP_FILAMENTCOMPONENT_H

#include "../ui.h"

#ifdef __cplusplus
extern "C" {
#endif

// COMPONENT filamentComponent
#define UI_COMP_FILAMENTCOMPONENT_FILAMENTCOMPONENT 0
#define UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENNOZZLE 1
#define UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENNOZZLE_FILAMENTSCREENNOZZLEUP 2
#define UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENNOZZLE_FILAMENTSCREENNOZZLEICON 3
#define UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENNOZZLE_FILAMENTSCREENNOZZLEDOWN 4
#define UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENFILAMENT 5
#define UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENFILAMENT_FILAMENTSCREENUNLOAD 6
#define UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENFILAMENT_FILAMENTSCREENFILAMENTICON 7
#define UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENFILAMENT_FILAMENTSCREENLOAD 8
#define _UI_COMP_FILAMENTCOMPONENT_NUM 9
lv_obj_t *ui_filamentComponent_create(lv_obj_t *comp_parent);
void ui_event_comp_filamentComponent_filamentScreenNozzleUp( lv_event_t * e);
void ui_event_comp_filamentComponent_filamentScreenNozzleDown( lv_event_t * e);
void ui_event_comp_filamentComponent_filamentScreenUnload( lv_event_t * e);
void ui_event_comp_filamentComponent_filamentScreenLoad( lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
