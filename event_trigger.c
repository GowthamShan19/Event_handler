#include <stdio.h>
#include "event_trigger.h"
#include "event_manager.h"

void event_trigger(int event_id)
{
    trigger_event(event_id);
}
// Trigger an event and call all the registered handlers (modules)

