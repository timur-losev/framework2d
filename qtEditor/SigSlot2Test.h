#pragma once

#include <Sigslot2.h>

/*struct Switch
{
    typedef Common::Signal<void> SignalClicked;
    typedef Common::Signal<int, float, const std::string&> SignalMod1;

    SignalClicked Clicked;
    SignalMod1    Mod1;

    void AttachOnClicked(const SignalClicked::SlotType& slot, Common::HasSlots* target);
    void AttachOnMod1(const SignalMod1::SlotType& slot, Common::HasSlots* target);
    void Click();
};*/

struct Sigslot2Test
{
    static int main();
};