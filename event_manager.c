// event_manager.c
#include <stdio.h>
#include <stdlib.h>
#include "event_manager.h"

// Initialize the events array (array of pointers to Event structs)

EventNode *event_head = NULL;
EventNode *event_tail = NULL;

// Register an event handler for a given event
void register_event_handler(int event_id, EventHandler_t handler)
{
    EventNode *current = event_head;

    // Search for the event in the doubly linked list
    while (current != NULL && current->event_id != event_id)
    {
        current = current->next;
    }

    // If the event doesn't exist, create a new node for it
    if (current == NULL)
    {
        EventNode *new_event = malloc(sizeof(EventNode));
        if (new_event == NULL)
        {
            printf("Memory allocation failed for event node\n");
            exit(1);
        }

        // Initialize the new event node
        new_event->event_id = event_id;
        new_event->handlers = malloc(sizeof(EventHandler_t)); // Initially space for 1 handler
        if (new_event->handlers == NULL)
        {
            printf("Memory allocation failed for event handlers\n");
            exit(1);
        }
        new_event->count = 0;
        new_event->prev = event_tail;
        new_event->next = NULL;

        // If the event list is empty, initialize both head and tail
        if (event_head == NULL)
        {
            event_head = new_event;
            event_tail = new_event;
        }
        else
        {
            event_tail->next = new_event; // Add the new node at the end
            event_tail = new_event;       // Update the tail pointer
        }

        current = new_event; // Point to the newly created event
    }

    // Check if we need to reallocate space for additional handlers
    if(current->count != 0)
    {
        current->handlers = realloc(current->handlers, sizeof(EventHandler_t) * (current->count + 1));
    }
    if (current->handlers == NULL)
    {
        printf("Memory reallocation failed for event handlers\n");
        exit(1);
    }

    // Add the new handler to the event's handler list
    current->handlers[current->count++] = handler;
}

// Function to remove a specific handler (module) from an event
void remove_module_from_event(int event_id, EventHandler_t handler_to_remove)
{
    EventNode *current_event = event_head;

    // Step 1: Find the event by event_id
    while (current_event != NULL && current_event->event_id != event_id)
    {
        current_event = current_event->next;
    }

    // If the event is found
    if (current_event != NULL)
    {
        int found = 0; // Flag to check if the handler is found

        // Step 2: Search for the handler in the event's handler list
        for (int i = 0; i < current_event->count; i++)
        {
            if (current_event->handlers[i] == handler_to_remove)
            {
                // Step 3: Bypass the handler in the list
                for (int j = i; j < current_event->count - 1; j++)
                {
                    // Shift the handlers left to overwrite the handler_to_remove
                    current_event->handlers[j] = current_event->handlers[j + 1];
                }

                // Reduce the count of handlers for the event
                current_event->count--;

                // Step 4: Reallocate memory for the reduced handler list
                current_event->handlers = realloc(current_event->handlers, sizeof(EventHandler_t) * current_event->count);
                if (current_event->handlers == NULL && current_event->count > 0)
                {
                    printf("Memory reallocation failed for event handlers\n");
                    exit(1);
                }

                printf("Handler removed from event %d.\n", event_id);
                found = 1;
                break;
            }
        }

        // If the handler is not found
        if (!found)
        {
            printf("Handler not found for event %d.\n", event_id);
        }
    }
    else
    {
        // If the event is not found
        printf("Event %d not found.\n", event_id);
    }
}

void trigger_event(int event_id)
{
    EventNode *current = event_head;

    // Search for the event in the list
    while (current != NULL && current->event_id != event_id) {
        current = current->next;
    }

    // If the event is found, trigger all its handlers
    if (current != NULL) {
        printf("Triggering event %d:\n", event_id);
        for (int i = 0; i < current->count; i++) {
            current->handlers[i](event_id);  // Call the handler
        }
    } else {
        printf("No Modules interested in event %d\n", event_id);
    }
}

// Free allocated memory for event handlers
void free_event_handlers(int event_id)
{
    EventNode *current = event_head;

    // Search for the event in the list
    while (current != NULL && current->event_id != event_id)
    {
        current = current->next;
    }

    // If the event is found, free its memory
    if (current != NULL)
    {
        free(current->handlers); // Free the handler array
        if (current->prev != NULL)
        {
            current->prev->next = current->next; // Bypass the current event node
        }
        else
        {
            event_head = current->next; // If it's the head, update the head pointer
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev; // Bypass the current event node
        }
        else
        {
            event_tail = current->prev; // If it's the tail, update the tail pointer
        }
        free(current); // Free the event node
    }
}

void free_all_events(void)
{
    EventNode *current = event_head;

    while (current != NULL)
    {
        EventNode *temp = current;
        current = current->next;

        free(temp->handlers); // Free the handlers
        free(temp);           // Free the event node
    }

    event_head = event_tail = NULL; // Set both head and tail to NULL
}
