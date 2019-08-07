# Installation Instructions

### Option 1. **Download the binary** relevant to your platform from 
(https://github.com/irfanHaslanded/PasswordManager/tree/master/downloads/)

### Option 2. **Build from source code**


#### 1. **Download dependencies**
```
   a. openssl
   b. gtest (if you want to run the tests)
   c. cmake
   d. gcc
```
#### 2. **from the root directory of the source code**
```
   0. cd PasswordManager/
   a. mkdir build; cd build; # build directory
   b. cmake ../src; # to create the make files
   c. make # to generate the application binaries
   d. make test # to run the tests
```
