#ifndef SUBJECT_IFC_H
#define SUBJECT_IFC_H

/**
 * Interface for Subject in Observer pattern.
 * This interface defines methods to attach and detach observers.
 * @tparam T Type of the observer interface.
 */
template<typename T>
class SubjectIfc {
public:

    virtual ~SubjectIfc() = default;

    /**
     * Attach a listener to receive events.
     * @param listener Listener to attach.
     */
    virtual void attach(T* listener) = 0;

    /**
     * Detach a listener from receiving events.
     * @param listener Listener to detach.
     */
    virtual void detach(T* listener) = 0;
};
#endif