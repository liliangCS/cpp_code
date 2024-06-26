class Singleton {
private:
    static Singleton* instance;

    // 私有构造函数，防止外部实例化
    Singleton() {}

public:
    // 删除拷贝构造函数和赋值操作符，防止拷贝实例
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        return instance;
    }
};

// 在类外初始化静态成员变量
Singleton* Singleton::instance = new Singleton();
