// main.c
#include <stdio.h>
#include "event_manager.h"
#include "event_trigger.h"
#include "module.h"

int main() {
    
    int event_id;

    // Register event handlers (functions/modules) for specific events
    register_event_handler(1, module1);
    register_event_handler(1, module2);
    register_event_handler(2, module4);
    register_event_handler(1, module2);
    register_event_handler(3, module3);
    register_event_handler(2, module1);
    register_event_handler(2, module3);
    register_event_handler(11, module3);
    register_event_handler(3, module4);

    remove_module_from_event(3, module4);

    do{

    printf("Which event you want to trigger? (0 - 10) \n");
    if(event_id >10 && event_id <0){
        printf("event %d Not Found!", event_id);
    }
    scanf("%d", &event_id);
    // Trigger events

    event(event_id);  // Will call module1, module2, and module4
    } while(event_id > 0);
    // Free allocated memory for event handlers after use
    for (int i = 0; i < 3; i++) {
        free_event_handlers(i);
    }

    return 0;
}
