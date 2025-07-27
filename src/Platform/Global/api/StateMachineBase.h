#ifndef STATE_MACHINE_BASE_H
#define STATE_MACHINE_BASE_H

/**
 * Base class for state machines.
 * This class provides a framework for implementing state machines with a defined state transition mechanism.
 * It allows for defining states, transitions, and actions on entering, running, and leaving states
 *
 * @example Usage:
 *      enum class MyStates {
 *          INITIAL,
 *
 *          STATE1 = INITIAL,
 *          STATE2,
 *          STATE3
 *      };
 *
 *      class MyStateMachine : public StateMachineBase<MyStates> {}
 */
template<class State>
class StateMachineBase {
public:

    virtual ~StateMachineBase() = default;

    /**
     * Get the current state of the state machine.
     * This method returns the current state of the state machine.
     */
    State currentState() const {
        return m_currentState;
    }

protected:

    /**
     * Run the state machine.
     */
    void runStateMachine() {
        bool stateChanged {true};

        while (stateChanged) {
            stateChanged = false;

            onTransition(m_currentState);

            if (m_currentState != m_nextState) {
                onLeaveState(m_currentState);
                stateChanged = true;

                m_currentState = m_nextState;
                onEnterState(m_currentState);
            }

            if (!stateChanged) {
                // if state has not changed, run the current state
                onRunState(m_currentState);
            }
        }

        clearFlags();
    }

    /**
     * Handle state transitions.
     * This method is called when the state machine transitions to a new state.
     * It can be overridden to perform actions on state transitions.
     * @param state The new state the machine is transitioning to.
     */
    virtual void onTransition(State const state) = 0;

    /**
     * Handle entering a state.
     * This method is called when the state machine enters a new state.
     * It can be overridden to perform actions when entering a state.
     * @param state The state being entered.
     */
    virtual void onEnterState(State const state) {
    }

    /**
     * Handle running a state.
     * This method is called when the state machine is running in a specific state.
     * It can be overridden to perform actions while in a state.
     * @param state The current state the machine is in.
     * @note This method is called repeatedly while the state machine is in the current state.
     */
    virtual void onRunState(State const state) {
    }

    /**
     * Handle leaving a state.
     * This method is called when the state machine is leaving a state.
     * It can be overridden to perform actions when leaving a state.
     * @param state The state being left.
     */
    virtual void onLeaveState(State const state) {
    }

    /**
     * Clear any flags or state variables.
     * This method can be overridden to reset any flags or state variables
     * after a state transition.
     * It is called at the end of the state machine run loop.
     * @note This method is called after the state machine has finished processing all states.
     * It is useful for resetting flags or state variables that are used to control the flow of the state machine.
     * @note By default, this method does nothing.
     */
    virtual void clearFlags() {
    }

    /**
     * Transition to the next state if the condition is met.
     * @param condition Condition to check for transition.
     * @param nextState The next state to transition to.
     *
     * @return True if the transition was successful, false otherwise.
     */
    bool transitionByCondition(bool condition, State nextState) {
        if (condition) {
            setNextState(nextState);
            return true;
        }
        return false;
    }

    /**
     * Set the next state for the state machine.
     * This method sets the next state to transition to.
     * @param nextState The next state to set.
     */
    void setNextState(State const nextState) {
        m_nextState = nextState;
    }

private:

    State m_currentState {};
    State m_nextState {};
};

#endif