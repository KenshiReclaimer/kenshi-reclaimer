#pragma once


namespace Kenshi
{
    class ZoneManagerInterfaceT
    {
    public:

        virtual ~ZoneManagerInterfaceT();

        virtual void vfn1();
        virtual void vfn2();
        virtual void vfn3();
        virtual void vfn4();
    };


    class ZoneManager : public ZoneManagerInterfaceT
    {

    };
}