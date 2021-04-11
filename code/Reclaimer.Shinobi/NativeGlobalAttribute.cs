using System;

namespace Reclaimer.Shinobi
{

    [AttributeUsage(AttributeTargets.Property | AttributeTargets.Class)]
    public class NativeGlobalAttribute : NativeAddressAttribute
    {
    }
}
