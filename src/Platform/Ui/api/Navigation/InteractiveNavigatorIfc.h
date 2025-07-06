#ifndef UI_NAVIGATOR_IFC_H
#define UI_NAVIGATOR_IFC_H

#include "types/UriQuery.h"

/**
 * Interface for navigation functionality.
 */
class InteractiveNavigatorIfc {
public:

    /**
     * Navigates to the default page.
     */
    virtual void navigateToDefault() = 0;

    /**
     * Navigates to the specified uri.
     * @param uri The uri to navigate to.
     */
    virtual void navigateTo(UriQuery const& uri) = 0;

    /**
     * Navigates back to the previous page.
     */
    virtual void back() = 0;

    virtual ~InteractiveNavigatorIfc() = default;
};

#endif