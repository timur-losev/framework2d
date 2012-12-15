#include "EdPrec.h"
#include "SigSlot2Test.h"
#include "Signaling.h"

#if 0

void Switch::AttachOnClicked(const SignalClicked::SlotType& slot, Common::HasSlots* target)
{
    Clicked.Connect(slot, target);
}

void Switch::AttachOnMod1(const SignalMod1::SlotType& slot, Common::HasSlots* target)
{
    Mod1.Connect(slot, target);
}

void Switch::Click()
{
    Clicked();
}

struct Light: public Common::HasSlots
{
    void ToggleState();
    void ToggleState2();
    void ToggleState3(int i, float f, const std::string& str);
};


void Light::ToggleState()
{
    std::cout << "Light::ToggleState() " << this << std::endl;
}

void Light::ToggleState2()
{
    std::cout << "Light::ToggleState2() " << this << std::endl;
}

void Light::ToggleState3(int i, float f, const std::string& str)
{
    std::cout << "Light::ToggleState2() " << this << " " << i << " " << f << " " << str <<std::endl;
}

/*template<typename T>
struct function_traits;

template<typename R, typename ...Args>
struct function_traits<std::function<R(Args...)>>
{
    static const size_t nargs = sizeof...(Args);

    typedef R result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };
};*/

int Sigslot2Test::main()
{
    using namespace std::placeholders;

    Switch sw;
    Light lg;

    sw.AttachOnClicked(std::bind(&Light::ToggleState, &lg), &lg);
    sw.AttachOnClicked(std::bind(&Light::ToggleState2, &lg), &lg);

    {
        Light lg2;
        sw.AttachOnClicked(std::bind(&Light::ToggleState, &lg2), &lg2);
    }

    sw.Click();

    sw.AttachOnMod1(std::bind(&Light::ToggleState3, &lg, _1, _2, _3), &lg);

    sw.Mod1(10, 14.0, "blablabla");

    system("pause");

    std::function<void (int, float, const std::string&)> f;

    return 0;
}

#endif


struct SignalHolder: public Common::Signaling
{
    enum E_SIGNALS
    {
        ES_TEST1,
        ES_TEST2,
        ES_TEST3,

        ES_MAX
    };

    virtual const char* DebugName() const
    {
        return "SignalHolder";
    }
};

using namespace std::placeholders;

template<class Signature>
void Foo(const Signature& sign)
{
    Signature sss(sign);
}

template<class Signature>
void Blabla(const Signature& sign)
{
    Foo<Signature>(sign);
}

struct SignalController
{
    SignalHolder sh;

    void AttachSignals()
    {
        //Babla(std::bind(&SignalController::OnTest1, this));
        sh.AttachOn2(SignalHolder::ES_TEST1, std::bind(&SignalController::OnTest1, this));
        /*sh.AttachOn2(SignalHolder::ES_TEST1, std::bind(&SignalController::OnTest1_1, this));
        sh.AttachOn2(SignalHolder::ES_TEST2, std::bind(&SignalController::OnTest2, this, _1));
        sh.AttachOn2(SignalHolder::ES_TEST3, std::bind(&SignalController::OnTest3, this, _1, _2, _3));*/
    }

    void OnTest1()
    {
        std::cout << __FUNCTION__ << std::endl;
    }

    void OnTest1_1()
    {
        std::cout << __FUNCTION__ << std::endl;
    }

    void OnTest2(int i)
    {
        std::cout << __FUNCTION__ << " " << i <<std::endl;
    }

    void OnTest3(int i, float t, const std::string& str)
    {
        std::cout << __FUNCTION__ << " " << i << " " << t << " " << str << std::endl;
    }
};

int Sigslot2Test::main()
{

    SignalController sc;
    sc.AttachSignals();

    sc.sh.CallBack2(SignalHolder::ES_TEST1);
    //sc.sh.CallBack2(SignalHolder::ES_TEST2, 1456);
    //sc.sh.CallBack2(SignalHolder::ES_TEST3, 4455, 1435.f, "blablabla");

    return 0;
}