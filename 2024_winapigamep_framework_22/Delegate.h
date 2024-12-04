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

    // callable은 ()를 붙여 호출할 수 있는 모든 것.

    // std::function을 이용해서 구현 됨.
    // std::function은 일반화 된 함수 포인터라고 볼 수 있음
    // std::function는 멤버함수를 받기 힘듬. -> this를 알지 못 함.


    // Push_back은 만들어져 있는 객체를 넣지만
    // Emplace_back은 인수를 받아서 emplace_back함수에서 객체를 생성함.
    // 값 복사나 이동을 막기 위함. 성능차이는 아마 x or 미미함
    // 터질 일 방지.

    // 메모리 누수 및 오류 방지를 위해 멤버 함수의 경우 shared_ptr과 weak_ptr을 사용함.
    // shared_ptr은 여러개의 셰어드 포인터가 하나의 객체를 가르킬 수 있음.
    // shared_ptr들의 객체에 대한 참조 카운트가 0이 된다면 해당 객체는 소멸함.
    // 해당 코드에선 오브젝트를 shared_ptr로 받고 있음. 이유는 곧 나옴.

    // weak_ptr은 약한 포인터인데 weak_ptr을 이용해서 shared_ptr이 유효한지 확인할 수 있음.
    // weak_ptr로 shared_ptr을 받으면 weak_ptr.lock()을 통해 해당 shared_ptr가 유효한지 확인함.
    // (없으면 null 유효하면 shared_ptr이 반한 됨.
    // 이 코드의 경우 바인드 된 멤버 함수를 가진 인스턴스가 존재하는지 판단함.
    // 삭제된 오브젝트의 멤버 함수를 실행하는 일을 방지하기 위함.
    // shared_ptr과 weak_ptr은 단순 오브젝트가 살아있나를 쉬운 방법으로 검사하기 위하여 이용됨.

    // 만능 참조: 좌측 우측값 모두 참조 가능함.
    // 만능 참조와 Forward를 사용한 이유.
    // forward는 원래 값의 카테고리를 전달하려 씀. -> 불필요한 복사나 이동을 방지.
    // callable들의 카테고리를 유지하려고 씀.
    // 참고로 람다가 우측 값.

    // 근데 사실 멤버 함수를 바인드 할 일이 많은진 모르겠음. (별로 없을 듯)

    /// <summary>
    /// Callable함수 바인드
    /// Method Bind
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="func"></param>
    template<typename T>
    void Add(T&& func) {
        m_callables.emplace_back(std::forward<T>(func));
    }

    /// <summary>
    /// 멤버함수 바인드
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
                // 객체가 소멸되었으므로 호출하지 않음
            }
        });
    }

    /// <summary>
    /// 오퍼레이터를 이용하여 ()를 하면 바인드된 메서드가 Invoke됨.
    /// </summary>
    /// <param name="...args"></param>
    void operator()(Args... args) {
        for (auto& callable : m_callables) {
            callable(std::forward<Args>(args)...);
        }
    }

    /// <summary>
    /// 필요하다면 바인드 된 함수를 해제할 수 있음.
    /// </summary>
    /// <param name="func"></param>
    void Remove(const std::function<ReturnType(Args...)>& func) {
        // 이 코드는 c# linq와 비슷하게 작동함. 만약 조건에 부합하면 그 코드를 삭제함.
        // 여기선 삭제하려는 함수의 target_type를 벡터 안 함수들과 비교해서 같으면 삭제함.
        // target_type는 std::function의 함수이고 std::function개체의 형식 정보를 가져옴. 이걸 비교하는 거임.
        m_callables.erase(std::remove_if(m_callables.begin(), m_callables.end(),
            [&](const std::function<ReturnType(Args...)>& f) {
                return f.target_type() == func.target_type();
            }), m_callables.end());
    }

private:
    // Binded Method Vector
    vector<std::function<ReturnType(Args...)>> m_callables;
};