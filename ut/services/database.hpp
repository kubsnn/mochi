#pragma once
#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include "../services/database_base.hpp"
#include <iostream>
#include <memory>

namespace mochi::services {

    class test_service {
    public:
        test_service() {
            std::cout << "Created test service!" << std::endl;
        }
    };

    class database : public database_base {
    public:
        explicit database(std::shared_ptr<test_service> ptr) {
            std::cout << "Created database!" << std::endl;
        }

        void connect() override {
            std::cout << "database::connect" << std::endl;
        }
    };
}

#endif // !__DATABASE_HPP__