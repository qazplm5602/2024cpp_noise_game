#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>

template<typename ReturnType, typename... Args>
class Delegate {
public:
    //Delegate();
    /*~Delegate()
    {
        m_callables = nullptr;
    }*/

    // callable�� ()�� �ٿ� ȣ���� �� �ִ� ��� ��.

    // std::function�� �̿��ؼ� ���� ��.
    // std::function�� �Ϲ�ȭ �� �Լ� �����Ͷ�� �� �� ����
    // std::function�� ����Լ��� �ޱ� ����. -> this�� ���� �� ��.


    // Push_back�� ������� �ִ� ��ü�� ������
    // Emplace_back�� �μ��� �޾Ƽ� emplace_back�Լ����� ��ü�� ������.
    // �� ���糪 �̵��� ���� ����. �������̴� �Ƹ� x or �̹���
    // ���� �� ����.

    // �޸� ���� �� ���� ������ ���� ��� �Լ��� ��� shared_ptr�� weak_ptr�� �����.
    // shared_ptr�� �������� �ξ�� �����Ͱ� �ϳ��� ��ü�� ����ų �� ����.
    // shared_ptr���� ��ü�� ���� ���� ī��Ʈ�� 0�� �ȴٸ� �ش� ��ü�� �Ҹ���.
    // �ش� �ڵ忡�� ������Ʈ�� shared_ptr�� �ް� ����. ������ �� ����.

    // weak_ptr�� ���� �������ε� weak_ptr�� �̿��ؼ� shared_ptr�� ��ȿ���� Ȯ���� �� ����.
    // weak_ptr�� shared_ptr�� ������ weak_ptr.lock()�� ���� �ش� shared_ptr�� ��ȿ���� Ȯ����.
    // (������ null ��ȿ�ϸ� shared_ptr�� ���� ��.
    // �� �ڵ��� ��� ���ε� �� ��� �Լ��� ���� �ν��Ͻ��� �����ϴ��� �Ǵ���.
    // ������ ������Ʈ�� ��� �Լ��� �����ϴ� ���� �����ϱ� ����.
    // shared_ptr�� weak_ptr�� �ܼ� ������Ʈ�� ����ֳ��� ���� ������� �˻��ϱ� ���Ͽ� �̿��.

    // ���� ����: ���� ������ ��� ���� ������.
    // ���� ������ Forward�� ����� ����.
    // forward�� ���� ���� ī�װ��� �����Ϸ� ��. -> ���ʿ��� ���糪 �̵��� ����.
    // callable���� ī�װ��� �����Ϸ��� ��.
    // ����� ���ٰ� ���� ��.

    // �ٵ� ��� ��� �Լ��� ���ε� �� ���� ������ �𸣰���. (���� ���� ��)

    /// <summary>
    /// Callable�Լ� ���ε�
    /// Method Bind
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="func"></param>
    template<typename T>
    void Add(T&& func) {
        m_callables.emplace_back(std::forward<T>(func));
    }

    /// <summary>
    /// ����Լ� ���ε�
    /// Member Method Bind
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <typeparam name="Func"></typeparam>
    /// <param name="obj">Put Instance that owns member method</param>
    /// <param name="func">Put Member std::function with &</param>
    template<typename T, typename Func>
    void Add(std::shared_ptr<T> obj, Func&& func) {
        std::weak_ptr<T> weakObj = obj;
        m_callables.emplace_back([weakObj, func](Args... args) {
            if (auto sharedObj = weakObj.lock()) {
                (sharedObj.get()->*func)(std::forward<Args>(args)...);
            }
            else {
                // ��ü�� �Ҹ�Ǿ����Ƿ� ȣ������ ����
            }
        });
    }

    /// <summary>
    /// ���۷����͸� �̿��Ͽ� ()�� �ϸ� ���ε�� �޼��尡 Invoke��.
    /// </summary>
    /// <param name="...args"></param>
    void operator()(Args... args) {
        for (auto& callable : m_callables) {
            callable(std::forward<Args>(args)...);
        }
    }

    /// <summary>
    /// �ʿ��ϴٸ� ���ε� �� �Լ��� ������ �� ����.
    /// </summary>
    /// <param name="func"></param>
    void Remove(const std::function<ReturnType(Args...)>& func) {
        // �� �ڵ�� c# linq�� ����ϰ� �۵���. ���� ���ǿ� �����ϸ� �� �ڵ带 ������.
        // ���⼱ �����Ϸ��� �Լ��� target_type�� ���� �� �Լ���� ���ؼ� ������ ������.
        // target_type�� std::function�� �Լ��̰� std::function��ü�� ���� ������ ������. �̰� ���ϴ� ����.
        m_callables.erase(std::remove_if(m_callables.begin(), m_callables.end(),
            [&](const std::function<ReturnType(Args...)>& f) {
                return f.target_type() == func.target_type();
            }), m_callables.end());
    }

private:
    // Binded Method Vector
    vector<std::function<ReturnType(Args...)>> m_callables;
};