#include "EdPrec.h"
#include "SigSlot2Test.h"

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