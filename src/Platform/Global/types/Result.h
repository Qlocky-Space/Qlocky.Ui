#ifndef SRC_PLATFORM_GLOBAL_TYPES_RESULT_H
#define SRC_PLATFORM_GLOBAL_TYPES_RESULT_H

#include <stdexcept>
#include <string>
#include <utility>
#include <variant>

/**
 * Wrapper for success value.
 */
template<typename T>
struct Ok {
    T value;
};

/**
 * Wrapper for error value.
 */
template<typename E>
struct Err {
    E error;
};

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

    using OkType = Ok<T>;
    using ErrType = Err<E>;

    // Implicit constructor from T
    Result(T const& value) :
        Result {Ok<T> {value}} {
    }
    Result(T&& value) :
        Result {Ok<T> {std::forward<T>(value)}} {
    }

    /**
     * Create a success result.
     * @param value Success value.
     * @return Result containing the value.
     */
    static Result success(T&& value) {
        return Result {Ok<T> {std::forward<T>(value)}};
    }

    /**
     * Create a success result.
     * @param value Success value.
     * @return Result containing the value.
     */
    static Result success(T const& value) {
        return Result {Ok<T> {value}};
    }

    /**
     * Create an error result.
     * @param error Error value.
     * @return Result containing the error.
     */
    static Result error(E&& error) {
        return Result {Err<E> {std::forward<E>(error)}};
    }

    /**
     * Create an error result.
     * @param error Error value.
     * @return Result containing the error.
     */
    static Result error(E const& error) {
        return Result {Err<E> {error}};
    }

    /**
     * Check if result is success.
     * @return True if success.
     */
    bool isSuccess() const {
        return std::holds_alternative<Ok<T>>(m_result);
    }

    /**
     * Check if result is error.
     * @return True if error.
     */
    bool isError() const {
        return std::holds_alternative<Err<E>>(m_result);
    }

    /**
     * Get the success value.
     * @return Success value.
     * @throws std::logic_error if not success.
     */
    T const& value() const {
        if (!isSuccess()) {
            throw std::logic_error {"Tried to access value on an error result."};
        }
        return std::get<Ok<T>>(m_result).value;
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
        return std::get<Err<E>>(m_result).error;
    }

    /**
     * Get the raw variant.
     * @return Variant holding Ok or Err.
     */
    std::variant<Ok<T>, Err<E>> const& raw() const {
        return m_result;
    }

private:

    explicit Result(Ok<T>&& ok) :
        m_result {std::move(ok)} {
    }
    explicit Result(Err<E>&& err) :
        m_result {std::move(err)} {
    }

    std::variant<Ok<T>, Err<E>> m_result;
};

using ResultVoid = Result<bool, std::string>;

#endif // SRC_PLATFORM_GLOBAL_TYPES_RESULT_H