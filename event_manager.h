// event_manager.h
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

// Define the function pointer type (event handler)
typedef void (*EventHandler_t)(int);

// Struct to store the event handlers for an event
typedef struct {
    EventHandler_t  *handlers;  // Pointer to dynamically allocated array of function pointers
    int count;               // Number of handlers registered for this event        
} Event;

// Event handler functions
typedef struct EventNode {
    int event_id;               // Event identifier
    EventHandler_t *handlers;     // Array of handlers for the event
    int count;                  // Number of handlers
    struct EventNode *prev;     // Pointer to the previous event node
    struct EventNode *next;     // Pointer to the next event node
} EventNode;

//EventNode *event_head, *event_tail;

void register_event_handler(int event_id, EventHandler_t handler);
void remove_module_from_event(int event_id, EventHandler_t handler_to_remove);
void trigger_event(int event_id);
void free_event_handlers(int event_id);  // Declaration for freeing memory

#endif // EVENT_MANAGER_H
