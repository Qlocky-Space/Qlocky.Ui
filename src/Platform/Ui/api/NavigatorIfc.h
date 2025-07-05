#ifndef UI_NAVIGATOR_IFC_H
#define UI_NAVIGATOR_IFC_H

#include "Page.h"

/**
 * Interface for navigation functionality.
 */
class NavigatorIfc {
public:

    /**
     * Navigates to the default page.
     */
    virtual void navigateToDefault() = 0;

    /**
     * Navigates to the specified page.
     * @param page The page to navigate to.
     */
    virtual void navigateTo(Page const& page) = 0;

    /**
     * Navigates back to the previous page.
     */
    virtual void back() = 0;

    virtual ~NavigatorIfc() = default;
};

#endif