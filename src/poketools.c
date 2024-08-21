#include <pokeagb/pokeagb.h>

#define TOOL_COUNT 1
extern u8 main(void);

const pchar menu_text[] = {0xCD , 0xDD , 0xD8 , 0xD9 , 0x00 , 0xCB , 0xE9 , 0xD9 , 0xE7 , 0xE8 , 0xE7, 0xFF};
const pchar sm_poketools_text[] = {0xCE, 0xC9, 0xC9, 0xC6, 0xCD};
struct TextColor menu_text_black = {0, 2, 3};
struct Textbox tbox = {0, 19, 1, 10, TOOL_COUNT << 1, 0xF, 0x130};

void close_startmenu() {
	safari_stepscount_close();
	sm_close_description();
	sm_close_menu();
}

void tool_selection(u8 task_id) {
    #define priv0 tasks[task_id].priv[0]
    switch (priv0) {
        case 0:
            if (script_env_2_is_enabled())
                return;
            priv0++;
        break;
        case 1:
            script_env_enable();
            u8 boxid = rboxid_init(&tbox);
            rboxid_clear_pixels(boxid, 0x11);
            outline_box(boxid, 1, 0x214, 0xE);
            rboxid_print(boxid, 1, 8, 2, &menu_text_black, 0, menu_text);
            choice_setup_simple(boxid, 2, 0, 1, 16, TOOL_COUNT, 0);
            rboxid_update(boxid, 3);
            rboxid_tilemap_update(boxid);
            tasks[task_id].priv[1] = boxid;
            priv0++;
            break;
        case 2:
        {
            s8 choice = rbox_choice_update();
            if (choice == 0) {// sideQuests
                main();
                task_del(task_id);
            } else if (choice == -1) {
                // b pressed, exit
                rboxid_clean(tasks[task_id].priv[1], 1);
                rboxid_free(tasks[task_id].priv[1]);
                script_env_disable();
                task_del(task_id);
            }
            return;
        }
    };

}


u8 sm_poketools() {
    close_startmenu();
    task_add(tool_selection, 0);
    return 1;
}
