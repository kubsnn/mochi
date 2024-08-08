#pragma once
#ifndef __IDATABASE_HPP__
#define __IDATABASE_HPP__

namespace mochi::services {

    class database_base {
    public:
        virtual void connect() = 0;
        virtual ~database_base() = default;
    };

}

#endif // !__IDATABASE_HPP__