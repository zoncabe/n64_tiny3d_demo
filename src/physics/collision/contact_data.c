
#include "../../../include/physics/collision/contact_data.h"


void contactData_init(ContactData* contact)
{
    contact->point = (Vector3){0, 0, 0};
    contact->normal = (Vector3){0, 0, 0};
    contact->penetration = 0.0f;
}
