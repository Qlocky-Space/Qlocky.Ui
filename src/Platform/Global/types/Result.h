#ifndef SRC_PLATFORM_GLOBAL_TYPES_RESULT_H
#define SRC_PLATFORM_GLOBAL_TYPES_RESULT_H

#include <stdexcept>
#include <string>
#include <utility>
#include <variant>

/**
 * A type-safe Result<T, E> implementation with disambiguated success/error states,
 * even when T == E, using tagged variant wrappers.
 *
 * @tparam T Success value type.
 * @tparam E Error value type.
 */
template<typename T, typename E = std::string>
class Result {
public:

    // Implicit constructor from T
    Result(T value) :
        Result {Ok {std::move(value)}} {
    }

    /**
     * Create a success result.
     * @param value Success value.
     * @return Result containing the value.
     */
    static Result success(T value) {
        return Result {Ok {std::move(value)}};
    }

    /**
     * Create an error result.
     * @param error Error value.
     * @return Result containing the error.
     */
    static Result error(E&& error) {
        return Result {Err {std::forward<E>(error)}};
    }

    /**
     * Create an error result.
     * @param error Error value.
     * @return Result containing the error.
     */
    static Result error(E const& error) {
        return Result {Err {error}};
    }

    /**
     * Check if result is success.
     * @return True if success.
     */
    bool isSuccess() const {
        return std::holds_alternative<Ok>(m_result);
    }

    /**
     * Check if result is error.
     * @return True if error.
     */
    bool isError() const {
        return std::holds_alternative<Err>(m_result);
    }

    /**
     * Get the success value.
     * @return Success value.
     * @throws std::logic_error if not success.
     */
    T value() const {
        if (!isSuccess()) {
            throw std::logic_error {"Tried to access value on an error result."};
        }
        return std::get<Ok>(m_result).value;
    }

    /**
     * Get the success value or a default value if error.
     * @param defaultValue Default value to return if error.
     * @return Success value or default value.
     */
    T valueOr(T defaultValue) const {
        if (!isSuccess()) {
            return defaultValue;
        }
        return std::get<Ok>(m_result).value;
    }

    /**
     * Get the error value.
     * @return Error value.
     * @throws std::logic_error if not error.
     */
    E const& error() const {
        if (!isError()) {
            throw std::logic_error {"Tried to access error on a success result."};
        }
        return std::get<Err>(m_result).error;
    }

private:

    struct Ok {
        T value;
    };

    struct Err {
        E error;
    };

    explicit Result(Ok&& ok) :
        m_result {std::move(ok)} {
    }
    explicit Result(Err&& err) :
        m_result {std::move(err)} {
    }

    std::variant<Ok, Err> m_result;
};

/**
 * Alias for Result with void success type.
 */
using ResultVoid = Result<bool, std::string>;

#endif // SRC_PLATFORM_GLOBAL_TYPES_RESULT_H