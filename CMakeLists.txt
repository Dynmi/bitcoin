cmake_minimum_required(VERSION 3.10)
project(HelloBitcoin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

# Add executable
add_executable(HelloBitcoin 
    main.cpp
    Block.cpp
    Transaction.cpp
    Wallet.cpp
    Blockchain.cpp
)

# Link OpenSSL
target_link_libraries(HelloBitcoin PRIVATE OpenSSL::SSL OpenSSL::Crypto) 