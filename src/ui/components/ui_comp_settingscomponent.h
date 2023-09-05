#ifndef _UI_COMP_SETTINGSCOMPONENT_H
#define _UI_COMP_SETTINGSCOMPONENT_H

#include "../ui.h"

#ifdef __cplusplus
extern "C"
{
#endif

// COMPONENT settingsComponent
#define UI_COMP_SETTINGSCOMPONENT_SETTINGSCOMPONENT 0
#define UI_COMP_SETTINGSCOMPONENT_INFO 1
#define UI_COMP_SETTINGSCOMPONENT_INFO_INFOLABEL 2
#define UI_COMP_SETTINGSCOMPONENT_UNPAIRBUTTON 3
#define UI_COMP_SETTINGSCOMPONENT_RESETDEVICEBUTTON 4
#define UI_COMP_SETTINGSCOMPONENT_RESETSETTINGSBUTTON 5
#define _UI_COMP_SETTINGSCOMPONENT_NUM 6
    lv_obj_t *ui_settingsComponent_create(lv_obj_t *comp_parent);
    void ui_event_comp_settingsComponent_auxFanInput(lv_event_t *e);
    void ui_event_comp_settingsComponent_chamberInput(lv_event_t *e);
    void ui_event_comp_settingsComponent_resetTouchButton(lv_event_t *e);
    void ui_event_comp_settingsComponent_resetSettingsButton(lv_event_t *e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
