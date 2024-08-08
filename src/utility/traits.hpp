#pragma once
#ifndef MOCHI_UTILITY_TRAITS_HPP
#define MOCHI_UTILITY_TRAITS_HPP

#include <type_traits>

namespace mochi::utility {

    template <typename T>
    struct Compilable {
        template <typename U>
        static auto test(U* p) -> decltype(std::declval<U>()(std::declval<T>()), std::true_type{});

        template <typename U>
        static auto test(...) -> std::false_type;

        static constexpr bool value = decltype(test<T>(nullptr))::value;
    };

    template <typename T>
    struct AlwaysFalse : std::false_type {};

    template <typename Callable, typename TRet, typename TArg, typename... TArgs>
    constexpr TArg ParamExtractorHelper(TRet (Callable::*)(TArg, TArgs...));

    template <typename Callable, typename TRet, typename TArg, typename... TArgs>
    constexpr TArg ParamExtractorHelper(TRet (Callable::*)(TArg, TArgs...) const);

    template <typename Callable, typename TRet>
    constexpr void ParamExtractorHelper(TRet (Callable::*)());

    template <typename Callable, typename TRet>
    constexpr void ParamExtractorHelper(TRet (Callable::*)() const);

    template <typename Lambda>
    struct LambdaTypeExtractor {
        using type = decltype(ParamExtractorHelper(&Lambda::operator()));
    };
};

#endif // !MOCHI_UTILITY_TRAITS_HPP