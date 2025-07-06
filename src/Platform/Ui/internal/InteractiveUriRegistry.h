#ifndef INTERACTIVE_URI_REGISTRY_H
#define INTERACTIVE_URI_REGISTRY_H

#include <unordered_map>

#include "Navigation/InteractiveUriRegistryIfc.h"

/**
 * @see InteractiveUriRegistryIfc
 */
class InteractiveUriRegistry : public InteractiveUriRegistryIfc {
public:

    /**
     * @see InteractiveUriRegistryIfc::registerUri
     */
    void registerUri(Uri const& uri, InteractiveMeta const& meta) final;

    /**
     * @see InteractiveUriRegistryIfc::meta
     */
    InteractiveMeta const& meta(Uri const& uri) final;

private:

    std::unordered_map<Uri, InteractiveMeta> m_map {};
};

#endif