#ifndef ALARM_SERVICE_IFC_H
#define ALARM_SERVICE_IFC_H

/**
 * This service handles alarms, including setting, managing, and manipulating alarms.
 * It also provides access to the current time.
 */
class AlarmServiceIfc {
public:

    /**
     * This method sets up any necessary resources or configurations
     * before the service can be used.
     */
    virtual void initialize() = 0;

    virtual ~AlarmServiceIfc() = default;
};

#endif