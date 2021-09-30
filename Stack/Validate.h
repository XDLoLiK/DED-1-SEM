/**
 * @file
 */

#ifndef VALIDATE_H
#define VALIDATE_H

#define validationFail !"VALIDATION FAILED, CHECK THE LOG FILE"

#define VALIDATE(obj, checkFunc, dumpFunc) {                \
    if (! checkFunc (obj)) {                                \
        dumpFunc (obj, #obj, stdout);                       \
        assert(validationFail);                             \
    }                                                       \
}


#endif // VALIDATE_H
