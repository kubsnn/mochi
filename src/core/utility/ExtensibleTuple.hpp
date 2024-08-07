#pragma once
#ifndef APP_CORE_UTILITY_EXTENSIBLE_TUPLE_HPP_
#define APP_CORE_UTILITY_EXTENSIBLE_TUPLE_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <typeindex>
#include <stdexcept>
#include <type_traits>
#include <core/utility/Reflections.hpp>

namespace mochi::core::utility {

    class ElementNotFoundException : public std::runtime_error {
    public:
        inline ElementNotFoundException()
            : std::runtime_error("Element is not stored in injector.") {}
    };

    class TupleElementBase {
    public:
        virtual ~TupleElementBase() = default;
    };

    template <typename T>
    class TupleElement : public TupleElementBase {
    public:
        T value_;

        constexpr explicit TupleElement(const T& val) : value_(val) {}
    };

    template <typename T>
    class TransientTupleElement : public TupleElementBase {
    public:
        constexpr explicit TransientTupleElement() = default;
    };

    template <typename T>
    class ScopedTupleElement : public TupleElementBase {
    public:
        constexpr explicit ScopedTupleElement() = default;
    };

    // Runtime extensible tuple class
    class ExtensibleTuple {
    public:
        ExtensibleTuple() = default;

        ExtensibleTuple(const ExtensibleTuple& other) = delete;

        ExtensibleTuple(ExtensibleTuple&& other) noexcept {
            elements_ = std::move(other.elements_);
            typeIndexMap_ = std::move(other.typeIndexMap_);
        }

        template <typename T>
        inline void addSingleton(const T& value) {
            auto element = std::make_unique<TupleElement<T>>(value);
            elements_.push_back(std::move(element));
            typeIndexMap_[typeid(T)] = elements_.back().get();
        }

        template <typename T>
        inline void addTransient() {
            auto element = std::make_unique<TransientTupleElement<T>>();
            elements_.push_back(std::move(element));
            typeIndexMap_[typeid(T)] = elements_.back().get();
        }

        template <typename T>
        inline void addScoped() {
            auto element = std::make_unique<ScopedTupleElement<T>>();
            elements_.push_back(std::move(element));
            typeIndexMap_[typeid(T)] = elements_.back().get();
        }

        template <typename T>
        inline void addSingleton(T&& value) {
            auto element = std::make_unique<TupleElement<T>>(std::forward<T>(value));
            elements_.push_back(std::move(element));
            typeIndexMap_[typeid(T)] = elements_.back().get();
        }

        template <typename T>
        [[nodiscard]] inline std::shared_ptr<T> get() const {
            return getElement<T>();
        }

        template <typename T>
        [[nodiscard]] inline T resolveObject() const {
            using TupleType = reflections::as_tuple<T>;
            return resolveObjectHelper<T>(std::make_index_sequence<std::tuple_size_v<TupleType>>{});
        }

        template <class T, std::size_t... Is>
        [[nodiscard]] inline T resolveObjectHelper(std::index_sequence<Is...>) const {
            return T(get<typename std::tuple_element_t<Is, reflections::as_tuple<T>>::element_type>()...);
        }

        template <typename T>
        [[nodiscard]] inline std::shared_ptr<T> get(ExtensibleTuple& scope) const {
            return getElement<T>(scope);
        }

        template <typename T>
        [[nodiscard]] inline T resolveObject(ExtensibleTuple& scope) const {
            using TupleType = reflections::as_tuple<T>;
            return resolveObjectHelper<T>(scope, std::make_index_sequence<std::tuple_size_v<TupleType>>{});
        }

        template <class T, std::size_t... Is>
        [[nodiscard]] inline T resolveObjectHelper(ExtensibleTuple& scope, std::index_sequence<Is...>) const {
            return T(get<typename std::tuple_element_t<Is, reflections::as_tuple<T>>::element_type>(scope)...);
        }

        [[nodiscard]] inline size_t size() const {
            return typeIndexMap_.size();
        }
        
    private:
        template <typename T>
        inline std::shared_ptr<T> getElement() const {
            auto singleton_it = typeIndexMap_.find(typeid(std::shared_ptr<T>));

            if (singleton_it != typeIndexMap_.end()) {
                if (auto element = dynamic_cast<TupleElement<std::shared_ptr<T>>*>(singleton_it->second)) {
                    return element->value_;
                }
            }

            auto it = typeIndexMap_.find(typeid(T));

            if (it != typeIndexMap_.end()) {
                if (auto element = dynamic_cast<TransientTupleElement<T>*>(it->second)) {
                    return std::make_shared<T>(resolveObject<T>());
                }
            }

            throw ElementNotFoundException();
        }

        template <typename T>
        inline std::shared_ptr<T> getElement(ExtensibleTuple& scope) const {
            
            auto singleton_it = typeIndexMap_.find(typeid(std::shared_ptr<T>));

            if (singleton_it != typeIndexMap_.end()) {
                if (auto element = dynamic_cast<TupleElement<std::shared_ptr<T>>*>(singleton_it->second)) {
                    return element->value_;
                }
            }
            
            auto it = typeIndexMap_.find(typeid(T));

            if (it == typeIndexMap_.end()) throw ElementNotFoundException();

            if (dynamic_cast<TransientTupleElement<T>*>(it->second)) {
                return std::make_shared<T>(resolveObject<T>(scope));
            }

            auto scope_it = scope.typeIndexMap_.find(typeid(std::shared_ptr<T>));

            if (scope_it != scope.typeIndexMap_.end()) {
                return static_cast<TupleElement<std::shared_ptr<T>>*>(scope_it->second)->value_;
            }

            scope.addSingleton(std::make_shared<T>(resolveObject<T>()));
            return scope.get<T>();
        }

        std::vector<std::unique_ptr<TupleElementBase>> elements_;
        std::map<std::type_index, TupleElementBase*> typeIndexMap_;
    };


} // namespace app::core::utility

#endif // !__APP_CORE_UTILITY_EXTENSIBLE_TUPLE_HPP__
