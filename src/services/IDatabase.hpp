#pragma once
#ifndef __IDATABASE_HPP__
#define __IDATABASE_HPP__

namespace mochi::services {

    class IDatabase {
    public:
        virtual void connect() = 0;
        virtual ~IDatabase() = default;
    };

}

#endif // !__IDATABASE_HPP__