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

#define VALIDATION_FAIL ! "VALIDATION FAILED, CHECK THE LOG FILE"

#define VALIDATE(obj, checkFunc, dumpFunc) {                \
    Location_t location = __LOCATION__;                     \
                                                            \
    if (!checkFunc(obj)) {                                  \
        dumpFunc(obj, #obj, stdout, location);              \
        assert(VALIDATION_FAIL);                            \
    }                                                       \
}                                                           \
                                                            \
do {                                                        \
                                                            \
} while(0)


#define VALIDATE_NO_DUMP(obj, checkFunc) {                  \
    Location_t location = __LOCATION__;                     \
                                                            \
    if (!checkFunc(obj))                                    \
        assert(VALIDATION_FAIL);                            \                                                       \
}                                                           \
                                                            \
do {                                                        \
                                                            \
} while(0)

//}------------------------------------------------------------------------------------------------

#endif // VALIDATE_H
