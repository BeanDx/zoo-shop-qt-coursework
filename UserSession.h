// UserSession.h
#ifndef USERSESSION_H
#define USERSESSION_H

class UserSession {
public:
    static UserSession& getInstance() {
        static UserSession instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
        return instance;
    }
    int getUserId() const { return userId; }
    void login(int id) { userId = id; }
    void logout() { userId = -1; }

private:
    int userId = -1; // Инициализируем как -1, означающее, что пользователь не вошел.
    UserSession() {} // Конструктор приватный.
    UserSession(UserSession const&) = delete;
    void operator=(UserSession const&) = delete;
};

#endif // USERSESSION_H
