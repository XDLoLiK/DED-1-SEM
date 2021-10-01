/**
 * @file
 */

#ifndef VALIDATE_H
#define VALIDATE_H

//{------------------------------------------------------------------------------------------------
/**
 * Macros can be used to validate any data
 * if data check and data dump functions are define
 */

#define validationFail !"VALIDATION FAILED, CHECK THE LOG FILE"

#define VALIDATE(obj, checkFunc, dumpFunc) {                \
    Location_t location = __LOCATION__;                     \
                                                            \
    if (! checkFunc (obj)) {                                \
        dumpFunc (obj, #obj, stdout, location);             \
        assert(validationFail);                             \
    }                                                       \
}
//}------------------------------------------------------------------------------------------------

#endif // VALIDATE_H
