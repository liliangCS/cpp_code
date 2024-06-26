class Singleton {
private:
    // 私有构造函数，防止外部实例化
    Singleton() {}

public:
    // 删除拷贝构造函数和赋值操作符，防止拷贝实例
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
};
