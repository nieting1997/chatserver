#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"

class UserModel{
    public:
        // 增加方法
        bool insert(User &user);
        // 查询方法
        User query(int id);
        // 更新用户状态信息
        bool updateState(User user);
        // 重置用户的状态信息
        void resetState();
};

#endif