#include "gift_config.h"

#ifndef _GIFT_KEY_SCHEDULE_H
#define _GIFT_KEY_SCHEDULE_H

static const u8 rCon[48] = {
    0x01U, 0x03U, 0x07U, 0x0FU, 0x1FU, 0x3EU, 0x3DU, 0x3BU, 
    0x37U, 0x2FU, 0x1EU, 0x3CU, 0x39U, 0x33U, 0x27U, 0x0EU, 
    0x1DU, 0x3AU, 0x35U, 0x2BU, 0x16U, 0x2CU, 0x18U, 0x30U, 
    0x21U, 0x02U, 0x05U, 0x0BU, 0x17U, 0x2EU, 0x1CU, 0x38U, 
    0x31U, 0x23U, 0x06U, 0x0DU, 0x1BU, 0x36U, 0x2DU, 0x1AU, 
    0x34U, 0x29U, 0x12U, 0x24U, 0x08U, 0x11U, 0x22U, 0x04U
};

#endif /* _GIFT_KEY_SCHEDULE_H */