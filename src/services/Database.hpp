#pragma once
#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include <services/IDatabase.hpp>
#include <iostream>
#include <memory>

namespace mochi::services {

    class TestService { 
    public:
        TestService() {
            std::cout << "Created test service!" << std::endl;
        }
    };

    class Database : public IDatabase {
    public:
        Database(std::shared_ptr<TestService> ptr) {
            std::cout << "Created database!" << std::endl;
        }

        void connect() override {
            std::cout << "Database::connect" << std::endl;
        }
    };
}

#endif // !__DATABASE_HPP__