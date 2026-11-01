#include <iostream>

template<typename T>
class SharedPtr
{
private:
    T* ptr;      // 管理的资源指针
    int* ref_cnt;// 引用计数指针，堆上分配
public:
    // 1. 普通构造
	explicit SharedPtr(T* p = nullptr) : ptr(p), ref_cnt(nullptr)//还得加上ref_cnt(nullptr)  
    {
        /*ref_cnt = new int(1);
        if (p == nullptr)
        {
            *ref_cnt = 0;
		}*///这么写后面p3 = p1; // 赋值//p3release,原来的cnt不是成-1了，没释放原来的cnt，后来指向p1的cnt，p1的cnt+1，p3的cnt+1？？？？？？内存泄漏p3cnt
        if (p != nullptr) {
            ref_cnt = new int(1);
        }

       
    }

    // 2. 拷贝构造：同一份资源，计数+1
    SharedPtr(const SharedPtr& other)
    {
        ptr = other.ptr;
        ref_cnt = other.ref_cnt;
        if (ref_cnt != nullptr)
        {
            (*ref_cnt)++;
        }
    }

    // 3. 赋值重载（深拷贝思路，shared是共享）
    SharedPtr& operator=(const SharedPtr& other)
    {
        // 防止自赋值：自己赋值给自己
        if (this == &other)
            return *this;

        // 先释放我自己旧的资源
        release();

        // 接管新资源
        ptr = other.ptr;
        ref_cnt = other.ref_cnt;
        if (ref_cnt != nullptr)
        {
            (*ref_cnt)++;
        }
        return *this;
    }

    // 4. 析构：计数减一，到0就释放
    ~SharedPtr()
    {
        release();
    }

    // 辅助：释放逻辑抽出来
    void release()
    {
        if (ref_cnt != nullptr)
        {
            (*ref_cnt)--;
            if (*ref_cnt == 0)
            {
                delete ptr;      // 释放托管对象
                delete ref_cnt;  // 释放计数
                ptr = nullptr;
                ref_cnt = nullptr;
            }
        }
    }

    // 重载 * 和 -> 方便使用
    T& operator*() const
    {
        return *ptr;
    }
    T* operator->() const
    {
        return ptr;
    }

    // 获取当前引用计数，测试用
    int use_count() const
    {
        return ref_cnt ? *ref_cnt : 0;
    }
};

// 测试代码
struct Test
{
    int val;
    Test(int v) : val(v)
    {
        std::cout << "Test 构造: " << val << "\n";
    }
    ~Test()
    {
        std::cout << "Test 析构: " << val << "\n";
    }
};

int main()
{
    SharedPtr<Test> p1(new Test(100));
    std::cout << "p1 count = " << p1.use_count() << "\n";//1

    SharedPtr<Test> p2 = p1; // 拷贝构造
    std::cout << "p1 count = " << p1.use_count() << "\n";//2
    std::cout << "p2 count = " << p2.use_count() << "\n";

    SharedPtr<Test> p3;
	p3 = p1; // 赋值//p3release,原来的cnt不是成-1了，没释放原来的cnt，后来指向p1的cnt，p1的cnt+1，p3的cnt+1？？？？？？
    std::cout << "p1 count = " << p1.use_count() << "\n";//3

	std::cout << p1->val << "\n";//100

    return 0;
}
